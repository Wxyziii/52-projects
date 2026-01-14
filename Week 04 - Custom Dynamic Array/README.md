# Week 4: Custom Dynamic Array

## Project Overview
Re-implement a vector (dynamic array) from scratch to understand memory management, reallocation, and template programming in C++.

## Learning Objectives
- Manual memory allocation and deallocation
- Capacity vs. size management
- Amortized O(1) append operations
- Move semantics and copy constructors
- Template programming

## Features to Implement
- [ ] Dynamic memory allocation
- [ ] Automatic resizing (doubling strategy)
- [ ] Push back, pop back operations
- [ ] Random access operator[]
- [ ] Iterator support
- [ ] Copy constructor and assignment operator
- [ ] Move constructor and assignment operator
- [ ] Reserve and capacity methods
- [ ] Clear and empty methods

## Key Concepts
- RAII (Resource Acquisition Is Initialization)
- Rule of Five (destructor, copy/move constructors, copy/move assignment)
- Memory reallocation strategies
- Exception safety

## Extensions
- Implement insert/erase at arbitrary positions
- Add emplace_back for in-place construction
- Implement custom allocator support
- Add shrink_to_fit functionality
