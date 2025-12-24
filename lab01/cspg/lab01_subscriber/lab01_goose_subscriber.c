/*
 * lab01_goose_subscriber.c
 *
 *  This is modified standalone GOOSE subscriber
 *
 * Has to be started as root in Linux.
 */

#include "goose_receiver.h"
#include "goose_subscriber.h"
#include "hal_thread.h"
#include "linked_list.h"
#include "mms_value.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

static int running = 1;

static void
sigint_handler(int signalId)
{
    running = 0;
}

static void
gooseListener(GooseSubscriber subscriber, void* parameter)
{
    printf("GOOSE event:\n");
    printf("  stNum: %u sqNum: %u\n", GooseSubscriber_getStNum(subscriber),
            GooseSubscriber_getSqNum(subscriber));
    printf("  timeToLive: %u\n", GooseSubscriber_getTimeAllowedToLive(subscriber));

    uint64_t timestamp = GooseSubscriber_getTimestamp(subscriber);

    printf("  timestamp: %u.%u\n", (uint32_t) (timestamp / 1000), (uint32_t) (timestamp % 1000));
    MmsValue* values = GooseSubscriber_getDataSetValues(subscriber);

       /* [0] XCBR.Pos.stVal */
    MmsValue* stVal = MmsValue_getElement(values, 0);

    /* Decode 2-bit BIT STRING */
    bool bit0 = MmsValue_getBitStringBit(stVal, 0); // MSB (0x80)
    bool bit1 = MmsValue_getBitStringBit(stVal, 1); // 0x40

    uint8_t pos;
    if (!bit0 && !bit1) pos = 0;        // Intermediate
    else if (!bit0 && bit1) pos = 1;    // OFF
    else if (bit0 && !bit1) pos = 2;    // ON
    else pos = 3;                       // BAD

    printf("  XCBR.Pos.stVal = 0x%02X (",
        (bit0 ? 0x80 : 0x00) | (bit1 ? 0x40 : 0x00));

    switch (pos) {
    case 0: printf("INTERMEDIATE"); break;
    case 1: printf("OFF"); break;
    case 2: printf("ON"); break;
    case 3: printf("BAD"); break;
    }
    printf(")\n");

    /* [1] XCBR.Pos.q */
    MmsValue* q = MmsValue_getElement(values, 1);
    bool invalid = MmsValue_getBitStringBit(q, 0);

    printf("  XCBR.Pos.q = %s\n",
        invalid ? "INVALID" : "GOOD");

    /* [2] XCBR.Pos.t */
    MmsValue* t = MmsValue_getElement(values, 2);
    uint64_t t_ms = MmsValue_getUtcTimeInMs(t);

    printf("  XCBR.Pos.t = %u.%03u\n",
        (uint32_t)(t_ms / 1000),
        (uint32_t)(t_ms % 1000));
}

int
main(int argc, char** argv)
{
    GooseReceiver receiver = GooseReceiver_create();

    if (argc > 1) {
        printf("Set interface id: %s\n", argv[1]);
        GooseReceiver_setInterfaceId(receiver, argv[1]);
    }
    else {
        printf("Using interface eth0\n");
        GooseReceiver_setInterfaceId(receiver, "eth0");
    }

    GooseSubscriber subscriber = GooseSubscriber_create("simpleIOGenericIO/XCBR1$GO$gcbPos", NULL);

    uint8_t dstMac[6] = {0x01,0x0c,0xcd,0x01,0x00,0x01};
    GooseSubscriber_setDstMac(subscriber, dstMac);
    GooseSubscriber_setAppId(subscriber, 1000);

    GooseSubscriber_setListener(subscriber, gooseListener, NULL);

    GooseReceiver_addSubscriber(receiver, subscriber);

    GooseReceiver_start(receiver);

    if (GooseReceiver_isRunning(receiver)) {
        signal(SIGINT, sigint_handler);

        while (running) {
            Thread_sleep(100);
        }
    }
    else {
        printf("Failed to start GOOSE subscriber. Reason can be that the Ethernet interface doesn't exist or root permission are required.\n");
    }

    GooseReceiver_stop(receiver);

    GooseReceiver_destroy(receiver);

    return 0;
}
