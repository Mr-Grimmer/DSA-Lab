#!/usr/bin/env python3
# flow_report.py
# Read flows.json (from capture_flows.py) and print:
# - Top 10 flows by bytes and packets
# - Flow durations (first/last pkt)
# - Top talkers (IPs ranked by bytes & packets sent)
# - Rankings of flows by bytes & packets
# Run as root or normal user: python3 flow_report.py

import json
import os
from collections import defaultdict
import sys

INFILE = "flows.json"

def load_flows(path=INFILE):
    if not os.path.exists(path):
        print("File not found:", path)
        sys.exit(1)
    with open(path) as f:
        data = json.load(f)
    raw = data.get("flows", {})
    flows = []
    for k, v in raw.items():
        # key format: src|sport|dst|dport|proto
        parts = k.split("|")
        if len(parts) != 5:
            continue
        src, sport, dst, dport, proto = parts
        flow = {
            "src": src,
            "sport": int(sport),
            "dst": dst,
            "dport": int(dport),
            "proto": proto,
            "packets": int(v.get("packets", 0)),
            "bytes": int(v.get("bytes", 0)),
            "start": float(v.get("start", 0.0)),
            "end": float(v.get("end", 0.0))
        }
        flows.append(flow)
    return flows

def print_top_flows(flows, by="bytes", topn=10):
    key = "bytes" if by=="bytes" else "packets"
    sorted_flows = sorted(flows, key=lambda x: x[key], reverse=True)[:topn]
    print(f"\nTop {topn} flows by {key.upper()}:")
    for f in sorted_flows:
        duration = f["end"] - f["start"]
        print(f"{f['proto']} {f['src']}:{f['sport']} -> {f['dst']}:{f['dport']} | {key}={f[key]} | pkts={f['packets']} | dur={duration:.2f}s")

def print_flow_durations(flows):
    print("\nFlows with duration (first_ts -> last_ts and duration sec):")
    for f in flows:
        dur = f["end"] - f["start"]
        print(f"{f['proto']} {f['src']}:{f['sport']} -> {f['dst']}:{f['dport']} | start={f['start']:.3f} end={f['end']:.3f} dur={dur:.2f}")

def top_talkers(flows, topn=10):
    ip_stats = defaultdict(lambda: {"bytes":0, "packets":0})
    # Count bytes/packets sent by source IP (outgoing in flow)
    for f in flows:
        ip_stats[f["src"]]["bytes"] += f["bytes"]
        ip_stats[f["src"]]["packets"] += f["packets"]
    by_bytes = sorted(ip_stats.items(), key=lambda x: x[1]["bytes"], reverse=True)[:topn]
    by_packets = sorted(ip_stats.items(), key=lambda x: x[1]["packets"], reverse=True)[:topn]
    print(f"\nTop {topn} IPs by BYTES sent:")
    for ip, st in by_bytes:
        print(f"{ip} -> bytes={st['bytes']} pkts={st['packets']}")
    print(f"\nTop {topn} IPs by PACKETS sent:")
    for ip, st in by_packets:
        print(f"{ip} -> pkts={st['packets']} bytes={st['bytes']}")

def rank_flows(flows, topn=10):
    print("\nRank flows by BYTES (top {})".format(topn))
    for i,f in enumerate(sorted(flows, key=lambda x: x["bytes"], reverse=True)[:topn], 1):
        print(f"{i}. {f['src']}:{f['sport']} -> {f['dst']}:{f['dport']} | bytes={f['bytes']} pkts={f['packets']}")
    print("\nRank flows by PACKETS (top {})".format(topn))
    for i,f in enumerate(sorted(flows, key=lambda x: x["packets"], reverse=True)[:topn], 1):
        print(f"{i}. {f['src']}:{f['sport']} -> {f['dst']}:{f['dport']} | pkts={f['packets']} bytes={f['bytes']}")

def main():
    flows = load_flows()
    if not flows:
        print("No flows found in file.")
        return
    # 2) Top 10 largest flows (bytes / packets)
    print_top_flows(flows, by="bytes", topn=10)
    print_top_flows(flows, by="packets", topn=10)

    # 3) Flow durations
    print("\n--- Flow durations (showing all flows) ---")
    print_flow_durations(flows)

    # 4) Top talkers (most active IPs)
    top_talkers(flows, topn=10)

    # 5 & 6) Rank IPs and flows
    print("\n--- Flow rankings ---")
    rank_flows(flows, topn=10)

if __name__ == "__main__":
    main()
