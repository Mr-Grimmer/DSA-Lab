from scapy.all import sniff, IP, TCP, UDP
from collections import defaultdict
import time

flows = defaultdict(lambda: {"first_seen": None, "last_seen": None})

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
        now = time.time()

        if flows[key]["first_seen"] is None:
            flows[key]["first_seen"] = now
        flows[key]["last_seen"] = now

# Capture traffic for some time (can set to 900 for 15 mins)
sniff(filter="ip", prn=packet_callback, timeout=60)

print("\n--- Flow Duration ---")
for key, val in flows.items():
    duration = val["last_seen"] - val["first_seen"] if val["first_seen"] else 0
    print(f"Flow {key} lasted {duration:.2f} seconds")
