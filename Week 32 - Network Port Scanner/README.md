# Week 32: Network Port Scanner

## Project Overview
Create a network scanning tool to discover open ports and services on target hosts.

## Learning Objectives
- Socket programming
- TCP/UDP protocol
- Network scanning techniques
- Concurrency for speed
- Service detection
- Packet crafting

## Features to Implement
- [ ] TCP connect scan
- [ ] SYN scan (stealth)
- [ ] UDP scan
- [ ] Port range specification
- [ ] Service version detection
- [ ] OS fingerprinting
- [ ] Concurrent scanning
- [ ] Scan rate limiting
- [ ] Output formats (text, JSON, XML)
- [ ] Common port presets

## Usage Example
```sh
# Scan common ports
./portscan 192.168.1.1

# Scan specific port range
./portscan 192.168.1.1 -p 1-1000

# Scan multiple hosts
./portscan 192.168.1.0/24 -p 80,443,8080

# Service detection
./portscan 192.168.1.1 --services

# Fast scan (parallel)
./portscan 192.168.1.1 -p 1-65535 --threads 100

# Output to file
./portscan 192.168.1.1 -o results.json
```

## Output Example
```
Scanning host: 192.168.1.100
Port range: 1-1000

[+] Port 22/tcp    OPEN    SSH (OpenSSH 8.2)
[+] Port 80/tcp    OPEN    HTTP (nginx 1.18.0)
[+] Port 443/tcp   OPEN    HTTPS
[-] Port 21/tcp    CLOSED
[-] Port 23/tcp    CLOSED
[+] Port 3306/tcp  OPEN    MySQL (5.7.32)

Summary:
  Total ports: 1000
  Open: 4
  Closed: 996
  Filtered: 0
  
Scan completed in 12.4s
```

## Scan Techniques
```cpp
// TCP Connect Scan
bool tcpConnectScan(const std::string& host, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr = createAddress(host, port);
    return connect(sock, &addr, sizeof(addr)) == 0;
}

// SYN Scan (requires raw socket)
bool synScan(const std::string& host, int port) {
    // Send SYN packet
    // Wait for SYN-ACK (open) or RST (closed)
    // Send RST to close connection
}
```

## Key Concepts
- TCP three-way handshake
- Socket options and timeouts
- Raw sockets (for SYN scan)
- ICMP for host discovery
- Banner grabbing
- Rate limiting and throttling
- Thread pool for concurrency

## Extensions
- Add Nmap-style scripting
- Implement ACK scan
- Add FIN/NULL/Xmas scans
- Create vulnerability detection
- Add traceroute functionality
- Implement MAC address detection
- Create network mapping
- Add IDS evasion techniques
