#!/usr/bin/env bash
set -e

IFACE="eth1"
OUT_PCAP="goose_capture.pcap"

echo "[*] Capturing GOOSE traffic on $IFACE"
echo "[*] Press Ctrl+C to stop"

sudo tcpdump -i "$IFACE" -nn -e ether proto 0x88b8 -w "$OUT_PCAP"
