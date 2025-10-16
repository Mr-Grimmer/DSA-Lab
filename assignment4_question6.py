from scapy.all import sniff, IP, TCP, UDP
from collections import defaultdict

flow_stats = defaultdict(lambda: {"packets": 0, "bytes": 0})

def packet_callback(pkt):
    if IP in pkt:
        proto = pkt[IP].proto
        if TCP in pkt:
            sport, dport = pkt[TCP].sport, pkt[TCP].dport
        elif UDP in pkt:
            sport, dport = pkt[UDP].sport, pkt[UDP].dport
        else:
            return
        
        key = (pkt[IP].src, sport, pkt[IP].dst, dport, proto)
        flow_stats[key]["packets"] += 1
        flow_stats[key]["bytes"] += len(pkt)

sniff(filter="ip", prn=packet_callback, timeout=60)

print("\n--- Rank Flows by Packets ---")
for flow, data in sorted(flow_stats.items(), key=lambda x: x[1]["packets"], reverse=True)[:10]:
    print(f"{flow}: {data['packets']} packets")

print("\n--- Rank Flows by Bytes ---")
for flow, data in sorted(flow_stats.items(), key=lambda x: x[1]["bytes"], reverse=True)[:10]:
    print(f"{flow}: {data['bytes']} bytes")
