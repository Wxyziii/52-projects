# Week 18: System Info Tool

## Project Overview
Create a cross-platform utility that gathers and displays comprehensive system information.

## Learning Objectives
- System API usage (Windows/Linux)
- Hardware information retrieval
- Cross-platform compatibility
- String formatting and display
- Registry/system file access
- Performance metrics collection

## Features to Implement
- [ ] Operating system details
- [ ] CPU information (model, cores, speed)
- [ ] Memory information (total, available, used)
- [ ] Disk drive information
- [ ] GPU details
- [ ] Network adapter info
- [ ] BIOS/UEFI information
- [ ] Uptime and boot time
- [ ] System architecture
- [ ] Export to JSON/XML/HTML

## Usage Example
```sh
# Display all info
./sysinfo

# Specific category
./sysinfo --cpu
./sysinfo --memory

# Export
./sysinfo --export report.json
```

## Output Example
```
╔════════════════════════════════════════════╗
║          SYSTEM INFORMATION                ║
╠════════════════════════════════════════════╣
║ OS: Windows 11 Pro (Build 22621)          ║
║ CPU: Intel Core i7-12700K @ 3.6GHz        ║
║ Cores: 12 (8P + 4E) | Threads: 20         ║
║ RAM: 32 GB DDR5 @ 4800MHz                 ║
║ Used: 18.5 GB (57.8%)                     ║
║ GPU: NVIDIA RTX 4070 (12GB)               ║
║ Disk: 1TB NVMe SSD (512GB free)           ║
║ Uptime: 3 days, 14:32:18                  ║
╚════════════════════════════════════════════╝
```

## Key Concepts
- Windows: WMI, Registry, GetSystemInfo
- Linux: /proc, /sys, lscpu, dmidecode
- Cross-platform abstraction
- CPUID instruction
- Hardware enumeration
- Unit conversion (GB, GHz, etc.)

## Extensions
- Add temperature sensors
- Show battery information (laptops)
- Display motherboard details
- Add fan speed monitoring
- Create benchmark mode
- Show installed software list
- Add driver information
- Implement health checks
