# Week 17: Process Monitor

## Project Overview
Build a system process monitor that tracks CPU usage, memory consumption, and other metrics for running processes.

## Learning Objectives
- Process enumeration APIs
- System resource monitoring
- Cross-platform process handling
- Performance counter access
- Real-time data collection
- UI/terminal updating

## Features to Implement
- [ ] List all running processes
- [ ] Display process ID (PID)
- [ ] Show process name and path
- [ ] CPU usage percentage per process
- [ ] Memory usage (RAM) per process
- [ ] Thread count display
- [ ] Sort by various metrics
- [ ] Process filtering/search
- [ ] Kill process functionality
- [ ] Refresh rate configuration
- [ ] Export to CSV/JSON

## Usage Example
```sh
# Start monitor
./procmon

# With specific refresh rate
./procmon --refresh 1000  # 1 second

# Filter by name
./procmon --filter chrome

# Export data
./procmon --export output.csv
```

## Display Example
```
╔══════════════════════════════════════════════════════╗
║ Process Monitor - Refresh: 2s                       ║
╠══════════════════════════════════════════════════════╣
║ PID   │ Name           │ CPU%  │ Memory  │ Threads  ║
╠══════════════════════════════════════════════════════╣
║ 1234  │ chrome.exe     │ 12.3% │ 845 MB  │ 42       ║
║ 5678  │ code.exe       │  8.7% │ 512 MB  │ 28       ║
║ 9012  │ system         │  2.1% │ 128 MB  │ 156      ║
║ 3456  │ explorer.exe   │  1.5% │ 98 MB   │ 12       ║
╚══════════════════════════════════════════════════════╝
[K]ill [S]ort [F]ilter [Q]uit
```

## Key Concepts
- Windows: WMI, Performance Counters, Process32
- Linux: /proc filesystem parsing
- CPU time calculation
- Memory types (working set, private, virtual)
- Process tree relationships
- Privilege elevation

## Extensions
- Add process tree visualization
- Implement historical graphs
- Add network usage per process
- Show disk I/O statistics
- Create alerting system
- Add process affinity control
- Implement mini-dump creation
- Support remote machine monitoring
