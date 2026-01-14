# Week 14: Benchmarking Framework

## Project Overview
Create a comprehensive benchmarking and profiling framework for measuring code performance.

## Learning Objectives
- High-resolution timing
- Statistical analysis
- Profiling techniques
- Memory usage tracking
- Performance comparison
- Result visualization

## Features to Implement
- [ ] High-precision timers
- [ ] Multiple benchmark iterations
- [ ] Statistical analysis (mean, median, std dev)
- [ ] Warmup runs
- [ ] Memory usage profiling
- [ ] CPU cache performance metrics
- [ ] Comparative benchmarking
- [ ] JSON/CSV export
- [ ] HTML report generation
- [ ] Outlier detection

## API Example
```cpp
Benchmark bench("My Algorithm");

// Simple timing
bench.measure("QuickSort", []() {
    quickSort(data);
});

// With iterations
bench.measureN("BinarySearch", 1000, [&]() {
    return binarySearch(data, target);
});

// Generate report
bench.report();
```

## Output Example
```
╔══════════════════════════════════════════════╗
║         Benchmark Results                    ║
╠══════════════════════════════════════════════╣
║ QuickSort                                    ║
║   Mean:      1.234 ms                        ║
║   Median:    1.198 ms                        ║
║   Std Dev:   0.087 ms                        ║
║   Min:       1.156 ms                        ║
║   Max:       1.456 ms                        ║
║   Samples:   100                             ║
╚══════════════════════════════════════════════╝
```

## Key Concepts
- std::chrono for timing
- Statistical measurements
- Cache warming
- Outlier handling
- Performance counter APIs
- Assembly timing (RDTSC)

## Extensions
- Add flame graph generation
- Implement CPU profiling
- Add memory leak detection
- Create comparison mode
- Support parameterized benchmarks
- Add regression detection
- Implement continuous benchmarking
- Add hardware counter integration
