# Week 8: Text-Based File Explorer

## Project Overview
Build an interactive terminal-based file explorer with navigation, file operations, and preview capabilities.

## Learning Objectives
- File system API usage
- Terminal UI design
- Keyboard input handling
- Directory traversal
- File metadata access

## Features to Implement
- [ ] Directory listing with details
- [ ] Navigate up/down directories
- [ ] File and folder icons/indicators
- [ ] File size formatting
- [ ] Sort by name, size, date
- [ ] Search functionality
- [ ] File preview (text files)
- [ ] Copy, move, delete operations
- [ ] Create new files/folders
- [ ] Permissions display
- [ ] Multiple panel view (optional)

## UI Elements
```
┌─ /home/user/documents ──────────────────────┐
│ Name              Size       Modified        │
├──────────────────────────────────────────────┤
│ 📁 ..                                        │
│ 📁 Projects       4.2 MB     2026-01-10     │
│ 📄 notes.txt      1.5 KB     2026-01-12     │
│ 📄 report.pdf     856 KB     2026-01-13     │
└──────────────────────────────────────────────┘
[N]ew [D]elete [C]opy [Q]uit
```

## Key Concepts
- Cross-platform file operations
- Terminal control sequences
- Event-driven input handling
- Buffered rendering

## Extensions
- Add file search with regex
- Implement bookmarks/favorites
- Add archive viewer (zip, tar)
- File associations for opening
- Dual-pane commander style
- Add syntax highlighting for code preview
