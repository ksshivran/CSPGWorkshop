#!/usr/bin/env python3

from scapy.all import rdpcap, wrpcap, Ether, sendp
import sys
import time


def replace_bytes(pkt_raw: bytes, offset: int, data: bytes) -> bytes:
    if offset < 0:
        raise ValueError("offset must be >= 0")

    pkt_len = len(pkt_raw)
    data_len = len(data)

    if offset + data_len > pkt_len:
        raise IndexError(
            f"Offset+write beyond packet length: "
            f"{offset} + {data_len} > {pkt_len}"
        )

    b = bytearray(pkt_raw)
    b[offset:offset + data_len] = data
    return bytes(b)


def main():
    if len(sys.argv) != 7:
        print(
            "Usage:\n"
            "  sudo ./masquerade_reply "
            "<iface> <in.pcap> <out.pcap> <offset> <8000> <interval_ms>\n\n"
        )
        sys.exit(1)

    iface = sys.argv[1]
    in_pcap = sys.argv[2]
    out_pcap = sys.argv[3]
    offset = int(sys.argv[4])
    interval_s = float(sys.argv[6]) / 1000.0

    hex_str = sys.argv[5]

    try:
        mbytes = bytes.fromhex(hex_str)
    except ValueError:
        raise ValueError("mbytes must contain only hex digits (0-9, a-f)")

    pkts = rdpcap(in_pcap)
    out_pkts = []

    print(f"Interface      : {iface}")

    for i, pkt in enumerate(pkts):
        raw = bytes(pkt)

        try:
            raw1 = replace_bytes(raw, offset, mbytes)
            eth = Ether(raw1)
            out_pkts.append(eth)

            sendp(eth, iface=iface, verbose=False)
            time.sleep(interval_s)

        except Exception as e:
            print(f"[!] Skipped packet {i}: {e}")
            out_pkts.append(pkt)

    wrpcap(out_pcap, out_pkts)
    print(f"[+] Saved {len(out_pkts)} packets to {out_pcap}")


if __name__ == "__main__":
    main()
