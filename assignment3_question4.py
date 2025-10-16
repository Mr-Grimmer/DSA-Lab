#!/usr/bin/env python3
# Minimal PMTUD probe (DF bit) — lab style
# Run as root: sudo python3 pmtu_simple.py

from scapy.all import IP, ICMP, Raw, sr1, conf

conf.verb = 0

target = input("Target IP (e.g. 8.8.8.8): ").strip()
start = input("Start payload bytes (default 1200): ").strip()
step = input("Step bytes (default 50): ").strip()
max_size = input("Max payload bytes (default 2000): ").strip()
timeout = input("Timeout seconds (default 2): ").strip()

start = int(start) if start else 1200
step = int(step) if step else 50
max_size = int(max_size) if max_size else 2000
timeout = float(timeout) if timeout else 2.0

last_success = None
frag_at = None

print("Probing... (press Ctrl+C to stop)")
size = start
while size <= max_size:
    payload = b"A" * size
    pkt = IP(dst=target, flags="DF")/ICMP()/Raw(payload)
    resp = sr1(pkt, timeout=timeout)
    if resp is None:
        # no reply — continue (could be filtered)
        print(f"{size}: no reply")
    else:
        if resp.haslayer(ICMP) and int(resp.getlayer(ICMP).type) == 3 and int(resp.getlayer(ICMP).code) == 4:
            frag_at = size
            print(f"{size}: ICMP fragmentation-needed received")
            break
        else:
            last_success = size
            print(f"{size}: success (no fragmentation)")
    size += step

print("\nResult:")
if last_success is not None:
    print("Largest payload that succeeded:", last_success, "bytes")
else:
    print("No successful payload observed")
if frag_at is not None:
    print("First payload that caused fragmentation-needed:", frag_at, "bytes")
else:
    print("No fragmentation-needed observed up to max size")
