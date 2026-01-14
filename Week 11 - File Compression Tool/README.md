# Week 11: File Compression Tool

## Project Overview
Build a file compression and decompression tool using Huffman coding algorithm.

## Learning Objectives
- Huffman coding algorithm
- Binary tree construction
- Bit manipulation
- Frequency analysis
- File I/O operations
- Binary file handling

## Features to Implement
- [ ] File compression using Huffman coding
- [ ] File decompression
- [ ] Frequency table generation
- [ ] Huffman tree construction
- [ ] Bit-level file writing
- [ ] Compression ratio calculation
- [ ] Progress indicator
- [ ] Multiple file support
- [ ] Archive creation (.huff format)
- [ ] Integrity verification

## Usage Example
```sh
# Compress a file
./compress input.txt -o output.huff

# Decompress a file
./compress -d output.huff -o restored.txt

# Show statistics
./compress --stats input.txt
```

## Output Example
```
Compressing: input.txt (1,245 KB)
Building frequency table...
Constructing Huffman tree...
Encoding data...
✓ Compressed to output.huff (623 KB)
Compression ratio: 50.04%
Time: 1.23s
```

## Key Concepts
- Huffman coding algorithm
- Priority queue for tree building
- Prefix-free codes
- Binary tree traversal
- Bit packing and unpacking
- Entropy calculation

## Extensions
- Implement LZW compression
- Add run-length encoding (RLE)
- Support multiple compression algorithms
- Create multi-threaded compression
- Add encryption layer
- Implement adaptive Huffman coding
- Support streaming compression
