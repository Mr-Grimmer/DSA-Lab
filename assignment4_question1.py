#!/usr/bin/env python3
# capture_flows.py
# Capture 15 minutes of IP traffic and store flow stats to flows.json
# Run as root: sudo python3 capture_flows.py

import json
import time
from scapy.all import sniff, IP, TCP, UDP, Raw
from collections import defaultdict

OUTFILE = "flows.json"
DURATION = 900  # seconds (15 minutes)

flows = {}  # key -> {"packets":int,"bytes":int,"start":float,"end":float}

def key_from_pkt(pkt):
    if not pkt.haslayer(IP):
        return None
    proto = None
    sport = None
    dport = None
    if pkt.haslayer(TCP):
        proto = "TCP"
        sport = int(pkt[TCP].sport)
        dport = int(pkt[TCP].dport)
    elif pkt.haslayer(UDP):
        proto = "UDP"
        sport = int(pkt[UDP].sport)
        dport = int(pkt[UDP].dport)
    else:
        # handle other IP protocols by using 0 ports and numeric proto
        proto = f"IP{int(pkt[IP].proto)}"
        sport = 0
        dport = 0
    src = pkt[IP].src
    dst = pkt[IP].dst
    return (src, sport, dst, dport, proto)

def process_packet(pkt):
    k = key_from_pkt(pkt)
    if k is None:
        return
    pkt_len = len(pkt)
    now = pkt.time
    if k not in flows:
        flows[k] = {"packets": 0, "bytes": 0, "start": now, "end": now}
    f = flows[k]
    f["packets"] += 1
    f["bytes"] += pkt_len
    f["end"] = now

def main():
    print(f"Starting capture for {DURATION} seconds...")
    try:
        sniff(filter="ip", prn=process_packet, store=False, timeout=DURATION)
    except KeyboardInterrupt:
        print("Interrupted by user, finishing capture.")
    # prepare JSON-serializable dict
    out = {}
    for k, v in flows.items():
        key_str = "{}|{}|{}|{}|{}".format(k[0], k[1], k[2], k[3], k[4])
        out[key_str] = v
    with open(OUTFILE, "w") as f:
        json.dump({"capture_time": time.time(), "flows": out}, f)
    print(f"Capture complete. {len(out)} flows saved to {OUTFILE}")

if __name__ == "__main__":
    main()
