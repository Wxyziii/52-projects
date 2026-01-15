# Log Analyzer 📊

A powerful C++ command-line application for parsing, filtering, analyzing, and exporting log files with an animated gradient banner, colorful interface, and professional statistics visualization.

## Features ✨

- **Load & Parse Logs**: Automatically parse log files with multiple format support
- **Filter by Level**: View logs filtered by INFO, WARN, or ERROR levels
- **Search Functionality**: Case-insensitive search across messages and levels with history tracking
- **Statistics Dashboard**: Visual bar charts with percentages and time range information
- **Export Functionality**: Export filtered logs with timestamps and statistics
- **Time Range Filtering**: View logs within specific date/time ranges
- **Search History**: Track and review previous searches
- **Colorful UI**: ANSI color-coded output for better readability
- **Animated Welcome Banner**: Eye-catching gradient animation on startup
- **Security**: Path validation to prevent directory traversal attacks

## Supported Log Formats 📝

The analyzer supports multiple log formats:

### Format 1 (Primary):
```
YYYY-MM-DD HH:MM:SS [LEVEL] Message content
```
Example:
```
2024-01-12 10:30:45 [INFO] Application started successfully
2024-01-12 10:31:02 [WARN] Memory usage is high
2024-01-12 10:31:15 [ERROR] Failed to connect to database
```

### Format 2 (Alternative):
```
[YYYY-MM-DD HH:MM:SS] LEVEL: Message content
```
Example:
```
[2024-01-12 10:30:45] INFO: Application started successfully
```

### Format 3 (US Date Format):
```
MM/DD/YYYY HH:MM:SS - LEVEL - Message content
```
Example:
```
01/12/2024 10:30:45 - INFO - Application started successfully
```

## Usage 🚀

### Building the Application

**Windows (MinGW/g++):**
```sh
g++ -std=c++17 -o main.exe main.cpp
```

**Windows (MSVC):**
```sh
cl /EHsc /std:c++17 main.cpp /link /OUT:main.exe
```

**Linux/macOS:**
```sh
g++ -std=c++17 -o main main.cpp
./main
```

### Running the Application

```sh
main.exe
```

### Menu Options

1. **Load Log File** - Load a log file for analysis (supports multiple formats)
2. **View All Logs** - Display all log entries with color-coded levels
3. **View INFO Logs** - Filter and display only INFO level logs
4. **View WARN Logs** - Filter and display only WARN level logs
5. **View ERROR Logs** - Filter and display only ERROR level logs
6. **Search Logs** - Case-insensitive keyword search in messages and levels
7. **Show Statistics** - Display visual bar charts with percentages and time ranges
8. **View Search History** - Review all previous search queries
9. **Export Filtered Logs** - Export logs by level with timestamps and statistics
10. **View Logs by Time Range** - Filter logs between specific dates/times
11. **Exit** - Close the application

## Project Structure 📁

```
Week 03 - Log File Analyzer/
├── main.cpp                    # Main source code
├── main.exe                    # Compiled executable (Windows)
├── README.md                   # This file
├── DOCUMENTATION.md            # Detailed technical documentation
├── Sonnet Code Review.md       # Comprehensive code review and improvements
├── Log/                        # Default directory for log files
│   └── (log files go here)
└── Docs/                       # Additional documentation
```

## Requirements 📋

- **Compiler**: C++17 or higher (g++, clang++, MSVC)
- **Operating System**: Windows (uses Windows.h for console setup), Linux/macOS compatible
- **Dependencies**: 
  - Standard C++ library
  - `<filesystem>` (C++17)
  - `<regex>` for pattern matching
  - `<chrono>` for timestamps

## Features in Detail 🔍

### Color-Coded Output
- 🟢 **INFO** - Green
- 🟡 **WARN** - Yellow
- 🔴 **ERROR** - Red
- 🔵 **Timestamps** - Cyan
- 🔵 **Headers** - Bright Cyan
- ⚡ **Gradient Banner** - 20-color animated gradient

### Advanced Statistics
- Total log entries count
- Visual bar charts (up to 50 characters wide)
- Percentage distribution for each log level
- Time range information (first and last entry)
- Support for custom/unknown log levels

### Export Features
- Timestamped filenames (YYYYMMDD_HHMMSS format)
- Comprehensive headers with export metadata
- Filter-specific exports (ALL, INFO, WARN, ERROR)
- Automatic file creation in current directory

### Security Features
- Path validation to prevent directory traversal
- Input sanitization
- Error handling for malformed log entries
- File existence checking

## Example Session 💻

```
╔═══════════════════════════════════════════════════════════╗
║                   LOG ANALYZER MENU                       ║
╠═══════════════════════════════════════════════════════════╣
║  1. Load Log File            7. Show Statistics           ║
║  2. View All Logs            8. View Search History       ║
║  3. View INFO Logs           9. Export Filtered Logs      ║
║  4. View WARN Logs          10. View Logs by Time Range   ║
║  5. View ERROR Logs         11. Exit                      ║
║  6. Search Logs                                           ║
╚═══════════════════════════════════════════════════════════╝

Select an option (1-11): 1

  Enter log file name: test.log
  ✓ Loaded 150 log entries.

Select an option (1-11): 7

  ════════════════════════════════════════════════════════════
  LOG STATISTICS
  ════════════════════════════════════════════════════════════

  Total Entries: 150

  INFO     ████████████████████████████████████████████ 120 (80.0%)
  WARN     ███████ 20 (13.3%)
  ERROR    ███ 10 (6.7%)

  ─────────────────────────────────────────────────────────────
  First Entry: 2024-01-12 10:30:45
  Last Entry:  2024-01-12 18:45:23

Select an option (1-11): 6

  Enter search keyword: database
  
  ════════════════════════════════════════════════════════════
  SEARCH RESULTS FOR: "database" (case-insensitive)
  ════════════════════════════════════════════════════════════

  2024-01-12 10:31:15 [ERROR] Failed to connect to database
  2024-01-12 10:35:22 [WARN] Database connection slow
  2024-01-12 14:22:10 [INFO] Database backup completed

  ─────────────────────────────────────────────────────────────
  Found: 3 matching entries

Select an option (1-11): 10

  Enter start time (YYYY-MM-DD HH:MM:SS): 2024-01-12 10:00:00
  Enter end time (YYYY-MM-DD HH:MM:SS): 2024-01-12 12:00:00

  ════════════════════════════════════════════════════════════
  LOGS FROM 2024-01-12 10:00:00 TO 2024-01-12 12:00:00
  ════════════════════════════════════════════════════════════

  (Shows filtered logs within time range)

Select an option (1-11): 9

  EXPORT OPTIONS
  1. Export All Logs
  2. Export INFO Logs
  3. Export WARN Logs
  4. Export ERROR Logs
  5. Cancel

  Select option (1-5): 4

  Enter export filename (without extension): critical_errors
  ✓ Exported 10 entries to critical_errors_20260115_121036.txt
```

## Error Handling 🛡️

The application includes robust error handling for:
- Invalid file paths or non-existent files
- Malformed log entries (skipped with warning)
- Empty search keywords
- Invalid time format inputs
- Empty log files
- File creation failures during export

## Performance Notes ⚡

- **Memory Optimization**: Pre-allocates vector capacity for better performance
- **Buffer Output**: Uses `ostringstream` for efficient string building
- **Regex Compilation**: Static regex patterns compiled once at startup
- **File Size Warning**: Alerts for files larger than 10MB

## Known Limitations ⚠️

- Entire log file loaded into memory (not suitable for multi-GB files)
- Windows-specific console setup (ANSI support)
- Maximum 50-character bar chart width in statistics
- Time range filtering requires exact format match

## Future Enhancements 🚧

Potential improvements (see `Sonnet Code Review.md` for details):
- [ ] Pagination for viewing large log files
- [ ] Search result export feature
- [ ] Enhanced export with embedded statistics
- [ ] Configuration file for customization
- [ ] Regex-based search option
- [ ] Multi-threaded log parsing

## Troubleshooting 🔧

**Problem**: Colors not displaying correctly  
**Solution**: Ensure your terminal supports ANSI escape codes. On Windows 10+, this should work by default.

**Problem**: Cannot load log file  
**Solution**: Check file path is correct and file is in an allowed directory (current directory or `Log/` subdirectory).

**Problem**: Malformed entries skipped  
**Solution**: Verify your log format matches one of the supported formats. Check the "Supported Log Formats" section.

**Problem**: Time range filter returns no results  
**Solution**: Ensure time format is exactly `YYYY-MM-DD HH:MM:SS` and matches your log timestamp format.

## Documentation 📚

- **README.md** - This file (quick start guide)
- **DOCUMENTATION.md** - Comprehensive technical documentation
- **Sonnet Code Review.md** - Detailed code review with improvements and bug fixes

## License 📄

This project is open source and available under the MIT License.

## Author ✍️

Created as part of the 52 Projects challenge - Week 03.

---

**Last Updated**: January 15, 2026  
**Version**: 2.0  
**C++ Standard**: C++17
