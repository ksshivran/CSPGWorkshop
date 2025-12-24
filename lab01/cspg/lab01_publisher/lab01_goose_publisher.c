/*
 * lab01_goose_publisher.c
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "mms_value.h"
#include "goose_publisher.h"
#include "hal_thread.h"

/* has to be executed as root! */
int
main(int argc, char **argv)
{
    char *interface;
    char *privateKey;
    if (argc > 1)
    {
        interface = argv[1];
    }
    else
    {
        interface = "enp0s3";
    }
    printf("Using interface %s\n", interface);

    LinkedList dataSetValues = LinkedList_create();


/* -------- XCBR.Pos.stVal -------- */
/* 2 bits → Padding = 6 → 1000 0000 */
    MmsValue* stVal = MmsValue_newBitString(2);

/* ON position → 10 */
    MmsValue_setBitStringBit(stVal, 0, true);   // MSB
    MmsValue_setBitStringBit(stVal, 1, false);

    LinkedList_add(dataSetValues, stVal);

/* -------- XCBR.Pos.q (Quality, 13 bits) ----- */
    MmsValue* q = MmsValue_newBitString(13);

/* Good, valid quality */
    for (int i = 0; i < 13; i++)
         MmsValue_setBitStringBit(q, i, false);

    LinkedList_add(dataSetValues, q);

/* -------- XCBR.Pos.t (Timestamp UTC) -------- */
    MmsValue* t = MmsValue_newUtcTimeByMsTime(Hal_getTimeInMs());
    LinkedList_add(dataSetValues, t);

    CommParameters gooseCommParameters;

    gooseCommParameters.appId = 1000;
    gooseCommParameters.dstAddress[0] = 0x01;
    gooseCommParameters.dstAddress[1] = 0x0c;
    gooseCommParameters.dstAddress[2] = 0xcd;
    gooseCommParameters.dstAddress[3] = 0x01;
    gooseCommParameters.dstAddress[4] = 0x00;
    gooseCommParameters.dstAddress[5] = 0x01;
    gooseCommParameters.vlanId = 0;
    gooseCommParameters.vlanPriority = 4;

    /*
     * Create a new GOOSE publisher instance. As the second parameter the interface
     * name can be provided (e.g. "eth0" on a Linux system). If the second parameter
     * is NULL the interface name as defined with CONFIG_ETHERNET_INTERFACE_ID in
     * stack_config.h is used.
     */
    GoosePublisher publisher = GoosePublisher_create(&gooseCommParameters, interface);

    if (publisher) {
        GoosePublisher_setGoCbRef(publisher, "simpleIOGenericIO/XCBR1$GO$gcbPos");
        GoosePublisher_setConfRev(publisher, 1);
        GoosePublisher_setDataSetRef(publisher, "simpleIOGenericIO/XCBR1$DS_Pos");
        GoosePublisher_setTimeAllowedToLive(publisher, 500);

        if (GoosePublisher_publish(publisher, dataSetValues) == -1) {
             printf("Error sending message!\n");
         }

        GoosePublisher_destroy(publisher);
    }
    else {
        printf("Failed to create GOOSE publisher. Reason can be that the Ethernet interface doesn't exist or root permission are required.\n");
    }

    LinkedList_destroyDeep(dataSetValues, (LinkedListValueDeleteFunction) MmsValue_delete);

    return 0;
}
