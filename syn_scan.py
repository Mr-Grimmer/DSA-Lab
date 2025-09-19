#!/usr/bin/env python3
import sys
import time
from scapy.all import IP, TCP, sr1, send, conf, get_if_list

conf.verb = 0
conf.use_pcap = True

def syn_scan(dst_ip, port_start=0, port_end=1023, timeout=1, iface=None):
    open_ports = []
    sport = 40000
    ip = IP(dst=dst_ip)

    print(f"[+] Starting SYN scan on {dst_ip} ports {port_start}-{port_end}")
    start_time = time.time()

    for port in range(port_start, port_end + 1):
        syn = TCP(sport=sport, dport=port, flags='S', seq=1000 + port)
        if iface:
            resp = sr1(ip/syn, timeout=timeout, iface=iface)
        else:
            resp = sr1(ip/syn, timeout=timeout)

        if resp is None:
            continue

        if resp.haslayer(TCP):
            flags = resp[TCP].flags
            if flags & 0x12 == 0x12:
                print(f"[+] Port {port} is OPEN (SYN+ACK received).")
                open_ports.append(port)
                rst = TCP(sport=sport, dport=port, flags='R', seq=syn.seq, ack=resp[TCP].seq + 1)
                if iface:
                    send(ip/rst, iface=iface)
                else:
                    send(ip/rst)
    total_time = time.time() - start_time
    print(f"[+] Scan complete in {total_time:.2f}s. Open ports: {open_ports}")
    return open_ports

if __name__ == "__main__":
    if len(sys.argv) not in (2,3):
        print("Usage: python syn_scanner_windows.py <target_ip> [iface]")
        sys.exit(1)
    target = sys.argv[1]
    iface = sys.argv[2] if len(sys.argv) == 3 else None
    if iface:
        print("Available interfaces:", get_if_list())
    syn_scan(target, iface=iface)
