# Week 21: File System Watcher

## Project Overview
Build a tool that monitors file system changes and triggers actions based on events.

## Learning Objectives
- File system event APIs
- Event-driven programming
- Callback/observer pattern
- Filter and pattern matching
- Directory recursion
- Performance optimization

## Features to Implement
- [ ] Monitor file creation, modification, deletion
- [ ] Watch directory recursively
- [ ] File/directory rename detection
- [ ] Pattern-based filtering (*.txt)
- [ ] Event callbacks/handlers
- [ ] Debouncing rapid events
- [ ] Multiple watch paths
- [ ] Event logging
- [ ] Real-time notifications
- [ ] Execute commands on events

## Usage Example
```cpp
FileWatcher watcher;

// Add watch path
watcher.addWatch("/path/to/monitor", true); // recursive

// Register callbacks
watcher.onCreated([](const std::string& path) {
    std::cout << "Created: " << path << std::endl;
});

watcher.onModified([](const std::string& path) {
    std::cout << "Modified: " << path << std::endl;
});

// Start watching
watcher.start();
```

## CLI Usage
```sh
# Watch directory
./filewatcher /path/to/dir --recursive

# With filter
./filewatcher /src --pattern "*.cpp,*.h"

# Execute command on change
./filewatcher /src --exec "make && ./test"

# Log to file
./filewatcher /data --log changes.log
```

## Output Example
```
[2026-01-14 10:23:45] CREATED: /docs/newfile.txt
[2026-01-14 10:23:47] MODIFIED: /docs/README.md
[2026-01-14 10:24:01] DELETED: /docs/old.txt
[2026-01-14 10:24:15] RENAMED: /docs/draft.txt → /docs/final.txt
```

## Key Concepts
- Windows: ReadDirectoryChangesW, FindFirstChangeNotification
- Linux: inotify API
- macOS: FSEvents, kqueue
- Event debouncing
- Recursive directory scanning
- Pattern matching (glob, regex)

## Extensions
- Add ignore patterns (.gitignore style)
- Implement rate limiting
- Create sync-on-change feature
- Add cloud backup trigger
- Implement smart recompilation
- Create file conflict detection
- Add change history
- Implement rollback capability
