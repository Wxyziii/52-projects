# Week 15: Memory Pool Allocator

## Project Overview
Implement a custom memory pool allocator for efficient allocation of fixed-size objects.

## Learning Objectives
- Custom memory management
- Memory pool patterns
- Object lifetime management
- Alignment requirements
- Fragmentation prevention
- Performance optimization

## Features to Implement
- [ ] Fixed-size block allocation
- [ ] Free list management
- [ ] Chunk-based memory pooling
- [ ] Thread-safe allocation (optional)
- [ ] Memory alignment support
- [ ] Pool statistics tracking
- [ ] Automatic pool growth
- [ ] Defragmentation support
- [ ] Debug mode with bounds checking
- [ ] Memory leak detection

## API Example
```cpp
// Create pool for 32-byte objects
MemoryPool<32> pool(1024); // 1024 blocks

// Allocate
void* ptr = pool.allocate();

// Use the memory
MyObject* obj = new(ptr) MyObject();

// Deallocate
obj->~MyObject();
pool.deallocate(ptr);

// Statistics
pool.printStats();
```

## Implementation Details
```
Pool Layout:
┌─────────────────────────────────────┐
│ Block 1 (32B) │ Block 2 │ Block 3  │
├─────────────────────────────────────┤
│ Free List: 1→3→5→7→...              │
└─────────────────────────────────────┘
```

## Key Concepts
- Memory alignment (alignof, alignas)
- Free list data structures
- Placement new operator
- Memory arena pattern
- Slab allocation
- Buddy allocation system

## Extensions
- Implement multi-size pool allocator
- Add thread-local pools
- Create STL allocator adapter
- Implement object pool with constructors
- Add memory tagging for debugging
- Create hierarchical allocators
- Implement stack allocator
- Add memory profiling tools
