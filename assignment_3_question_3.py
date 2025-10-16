import ipaddress
from scapy.all import IP, ICMP, sr1, conf

conf.verb = 0

network = input("Enter network in CIDR (e.g. 192.168.1.0/24): ").strip()
try:
    net = ipaddress.ip_network(network, strict=False)
except Exception as e:
    print("Invalid network:", e)
    exit(1)

timeout = input("Timeout per host in seconds (default 1): ").strip()
timeout = float(timeout) if timeout else 1.0

print("Scanning... (only hosts that reply will be printed)")
for host in net.hosts():
    h = str(host)
    pkt = IP(dst=h)/ICMP()
    resp = sr1(pkt, timeout=timeout)
    if resp is not None and resp.haslayer(ICMP):
        # ICMP type 0 is echo-reply; treat any ICMP reply as alive
        print(h)
