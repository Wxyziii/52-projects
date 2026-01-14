# Week 13: Multi-Threaded File Copier

## Project Overview
Build a high-performance file copy utility that uses multiple threads for parallel I/O operations.

## Learning Objectives
- Parallel I/O operations
- Thread synchronization
- Chunk-based processing
- Progress tracking across threads
- Error handling in concurrent environment
- Performance optimization

## Features to Implement
- [ ] Multi-threaded file copying
- [ ] Chunk-based parallel reading/writing
- [ ] Progress bar with percentage
- [ ] Speed calculation (MB/s)
- [ ] Directory copying (recursive)
- [ ] Preserve file metadata
- [ ] Resume interrupted transfers
- [ ] Verify copied files (checksums)
- [ ] Configurable thread count
- [ ] Error reporting and recovery

## Usage Example
```sh
# Copy single file
./filecopy source.dat destination.dat --threads 4

# Copy directory
./filecopy /source/dir /dest/dir --recursive

# With verification
./filecopy source.iso dest.iso --verify --threads 8
```

## Output Example
```
Copying: large_file.iso (4.7 GB)
[████████████████░░░░] 78% | 3.67 GB / 4.7 GB
Speed: 285 MB/s | ETA: 3s | Threads: 4
✓ Copy completed in 16.48s
Verifying checksum... ✓ Match
```

## Key Concepts
- Thread pool for I/O operations
- Chunk division strategies
- Thread-safe progress tracking
- Memory-mapped files (optional)
- Atomic operations for counters
- Buffer management

## Extensions
- Add network file transfer support
- Implement compression during copy
- Add encryption on-the-fly
- Create differential copy (rsync-like)
- Support copy resumption after crash
- Add bandwidth throttling
- Implement sparse file detection
- Add file deduplication
