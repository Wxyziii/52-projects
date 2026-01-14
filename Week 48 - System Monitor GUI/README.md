# Week 48: System Monitor GUI

## Project Overview
Create a comprehensive system monitoring application similar to Task Manager with real-time graphs and detailed metrics.

## Learning Objectives
- Real-time data visualization
- Multi-threaded data collection
- GUI performance optimization
- System API integration
- Chart/graph rendering
- Resource-efficient monitoring

## Features to Implement
- [ ] Process list with details
- [ ] CPU usage (overall and per-core)
- [ ] Memory usage (RAM, virtual, swap)
- [ ] Disk I/O activity
- [ ] Network usage (upload/download)
- [ ] GPU utilization (optional)
- [ ] Real-time graphs
- [ ] Historical data tracking
- [ ] Process tree view
- [ ] Kill/suspend processes
- [ ] Service management
- [ ] Startup programs management
- [ ] System information panel

## Main Window Layout
```
╔══════════════════════════════════════════════════════╗
║ System Monitor                    [_][□][×]          ║
╠══════════════════════════════════════════════════════╣
║ [Processes] [Performance] [Services] [Startup]       ║
╠══════════════════════════════════════════════════════╣
║                                                      ║
║ CPU Usage: 45% ████████████░░░░░░                   ║
║ ┌────────────────────────────────────────────────┐  ║
║ │ 100%│                    ╱╲                    │  ║
║ │  75%│          ╱╲       ╱  ╲      ╱╲          │  ║
║ │  50%│    ╱╲   ╱  ╲     ╱    ╲    ╱  ╲         │  ║
║ │  25%│   ╱  ╲ ╱    ╲   ╱      ╲  ╱    ╲        │  ║
║ │   0%└────────────────────────────────────────►  │  ║
║ └────────────────────────────────────────────────┘  ║
║                                                      ║
║ Memory: 18.5 GB / 32 GB (57.8%)                     ║
║ ┌────────────────────────────────────────────────┐  ║
║ │ [████████████████████░░░░░░░░░░░░]             │  ║
║ │ In Use: 18.5 GB | Available: 13.5 GB           │  ║
║ └────────────────────────────────────────────────┘  ║
║                                                      ║
║ Disk: 145 MB/s Read | 78 MB/s Write                ║
║ Network: ↓ 2.4 Mbps | ↑ 0.8 Mbps                   ║
║                                                      ║
║ ┌────────────────────────────────────────────────┐  ║
║ │ PID  │ Name          │ CPU% │ Memory │ Threads │  ║
║ ├──────┼───────────────┼──────┼────────┼─────────┤  ║
║ │ 1234 │ chrome.exe    │ 12.3%│ 845 MB │ 42      │  ║
║ │ 5678 │ code.exe      │  8.7%│ 512 MB │ 28      │  ║
║ │ 9012 │ system        │  2.1%│ 128 MB │ 156     │  ║
║ └────────────────────────────────────────────────┘  ║
╠══════════════════════════════════════════════════════╣
║ Processes: 234 | CPU: 45% | Memory: 57.8%           ║
╚══════════════════════════════════════════════════════╝
```

## Implementation
```cpp
class SystemMonitor : public QMainWindow {
    Q_OBJECT
private:
    QTimer* updateTimer_;
    QCustomPlot* cpuGraph_;
    QCustomPlot* memoryGraph_;
    QTableWidget* processTable_;
    
    DataCollector dataCollector_;
    std::vector<double> cpuHistory_;
    std::vector<double> memoryHistory_;
    
public:
    SystemMonitor() {
        setupUI();
        
        // Update every second
        updateTimer_ = new QTimer(this);
        connect(updateTimer_, &QTimer::timeout,
                this, &SystemMonitor::updateData);
        updateTimer_->start(1000);
    }
    
private slots:
    void updateData() {
        // Collect system data
        auto cpuUsage = dataCollector_.getCPUUsage();
        auto memUsage = dataCollector_.getMemoryUsage();
        auto processes = dataCollector_.getProcesses();
        
        // Update graphs
        updateCPUGraph(cpuUsage);
        updateMemoryGraph(memUsage);
        
        // Update process list
        updateProcessTable(processes);
    }
    
    void updateCPUGraph(double usage) {
        cpuHistory_.push_back(usage);
        if (cpuHistory_.size() > 60) {
            cpuHistory_.erase(cpuHistory_.begin());
        }
        
        QVector<double> x, y;
        for (size_t i = 0; i < cpuHistory_.size(); ++i) {
            x.append(i);
            y.append(cpuHistory_[i]);
        }
        
        cpuGraph_->graph(0)->setData(x, y);
        cpuGraph_->replot();
    }
    
    void killProcess(int pid) {
        if (QMessageBox::question(this, "Confirm",
            "Kill process?") == QMessageBox::Yes) {
            dataCollector_.killProcess(pid);
        }
    }
};

class DataCollector {
public:
    double getCPUUsage() {
#ifdef _WIN32
        return getWindowsCPUUsage();
#elif __linux__
        return getLinuxCPUUsage();
#endif
    }
    
    MemoryInfo getMemoryUsage() {
        // Platform-specific memory query
    }
    
    std::vector<ProcessInfo> getProcesses() {
        // Platform-specific process enumeration
    }
    
private:
    double getWindowsCPUUsage() {
        PDH_FMT_COUNTERVALUE value;
        PdhCollectQueryData(cpuQuery_);
        PdhGetFormattedCounterValue(
            cpuCounter_, PDH_FMT_DOUBLE, 
            nullptr, &value);
        return value.doubleValue;
    }
};
```

## Performance Tab
```cpp
class PerformanceTab : public QWidget {
private:
    struct CoreUsage {
        int coreId;
        double usage;
        QCustomPlot* graph;
    };
    
    std::vector<CoreUsage> coreGraphs_;
    
    void setupCoreGraphs() {
        int cores = std::thread::hardware_concurrency();
        
        for (int i = 0; i < cores; ++i) {
            auto* graph = new QCustomPlot();
            graph->addGraph();
            graph->yAxis->setRange(0, 100);
            
            coreGraphs_.push_back({i, 0.0, graph});
            layout_->addWidget(graph);
        }
    }
    
    void updateCoreUsage() {
        auto coreUsages = getPerCoreUsage();
        
        for (size_t i = 0; i < coreUsages.size(); ++i) {
            coreGraphs_[i].usage = coreUsages[i];
            updateGraph(coreGraphs_[i]);
        }
    }
};
```

## Key Concepts
- Windows: PDH (Performance Data Helper), WMI
- Linux: /proc filesystem parsing
- QCustomPlot for graphs
- QTableWidget for process list
- QTimer for periodic updates
- Thread-safe data collection
- Efficient UI updates

## Extensions
- Add temperature monitoring
- Implement battery info (laptops)
- Create custom alerts/triggers
- Add historical data export
- Implement process affinity control
- Create performance profiles
- Add system benchmarking
- Implement remote monitoring
