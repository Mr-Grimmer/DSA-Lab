#!/usr/bin/env python3
import sys
from scapy.all import IP, TCP, sr1, send, conf, get_if_list

conf.verb = 0
conf.use_pcap = True

def manual_handshake(dst_ip, dst_port, timeout=2, iface=None):
    client_isn = 12345
    ip = IP(dst=dst_ip)
    syn = TCP(sport=55555, dport=dst_port, flags='S', seq=client_isn)

    print(f"[+] Sending SYN -> {dst_ip}:{dst_port} (seq={client_isn})")
    if iface:
        synack = sr1(ip/syn, timeout=timeout, iface=iface)
    else:
        synack = sr1(ip/syn, timeout=timeout)

    if synack is None:
        print("[-] No response to SYN (timeout).")
        return False

    if synack.haslayer(TCP) and synack[TCP].flags & 0x12 == 0x12:
        server_isn = synack[TCP].seq
        ack = TCP(sport=syn.sport, dport=dst_port, flags='A', seq=client_isn + 1, ack=server_isn + 1)
        print(f"[+] Received SYN+ACK (server_isn={server_isn}). Sending ACK to complete handshake.")
        if iface:
            send(ip/ack, iface=iface)
        else:
            send(ip/ack)
        print("[+] ACK sent. Handshake completed (from our side).")

        rst = TCP(sport=syn.sport, dport=dst_port, flags='R', seq=client_isn + 1, ack=server_isn + 1)
        if iface:
            send(ip/rst, iface=iface)
        else:
            send(ip/rst)
        print("[+] Sent RST to close the connection immediately (cleanup).")
        return True
    else:
        print("[-] Received unexpected response (not SYN+ACK).")
        synack.show()
        return False

if __name__ == "__main__":
    if len(sys.argv) not in (3,4):
        print("Usage: python handshake_demo_windows.py <target_ip> <target_port> [iface]")
        sys.exit(1)
    target = sys.argv[1]
    port = int(sys.argv[2])
    iface = sys.argv[3] if len(sys.argv) == 4 else None
    if iface:
        print("Available interfaces:", get_if_list())
    manual_handshake(target, port, iface=iface)
