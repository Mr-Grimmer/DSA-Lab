from scapy.all import sniff, IP
from collections import defaultdict

ip_count = defaultdict(lambda: {"packets": 0, "bytes": 0})

def packet_callback(pkt):
    if IP in pkt:
        src = pkt[IP].src
        ip_count[src]["packets"] += 1
        ip_count[src]["bytes"] += len(pkt)

sniff(filter="ip", prn=packet_callback, timeout=60)

print("\n--- Rank IPs by Packets Sent ---")
for ip, data in sorted(ip_count.items(), key=lambda x: x[1]["packets"], reverse=True):
    print(f"{ip}: {data['packets']} packets")

print("\n--- Rank IPs by Bytes Sent ---")
for ip, data in sorted(ip_count.items(), key=lambda x: x[1]["bytes"], reverse=True):
    print(f"{ip}: {data['bytes']} bytes")
