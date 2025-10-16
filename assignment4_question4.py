from scapy.all import sniff, IP
from collections import defaultdict

ip_stats = defaultdict(lambda: {"packets": 0, "bytes": 0})

def packet_callback(pkt):
    if IP in pkt:
        src = pkt[IP].src
        ip_stats[src]["packets"] += 1
        ip_stats[src]["bytes"] += len(pkt)

# Capture packets for a demo period
sniff(filter="ip", prn=packet_callback, timeout=60)

print("\n--- Top Talkers ---")
sorted_ips = sorted(ip_stats.items(), key=lambda x: (x[1]["bytes"], x[1]["packets"]), reverse=True)

for ip, stats in sorted_ips[:10]:
    print(f"{ip}: {stats['packets']} packets, {stats['bytes']} bytes")
