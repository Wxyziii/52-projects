# Log Analyzer 📊

A feature-rich C++ command-line application for parsing, filtering, and analyzing log files with an animated gradient banner and colorful interface.

## Features ✨

- **Load & Parse Logs**: Automatically parse log files with timestamp, level, and message extraction
- **Filter by Level**: View logs filtered by INFO, WARN, or ERROR levels
- **Search Functionality**: Search logs by keyword across messages and levels
- **Statistics Dashboard**: View detailed statistics with percentages for each log level
- **Colorful UI**: ANSI color-coded output for better readability
- **Animated Welcome Banner**: Eye-catching gradient animation on startup

## Log Format 📝

The analyzer expects log files in the following format:
```
YYYY-MM-DD HH:MM:SS [LEVEL] Message content
```

Example:
```
2024-01-12 10:30:45 [INFO] Application started successfully
2024-01-12 10:31:02 [WARN] Memory usage is high
2024-01-12 10:31:15 [ERROR] Failed to connect to database
```

## Usage 🚀

### Building the Application

**Windows (MinGW/g++):**
```sh
g++ -o main.exe main.cpp
```

**Windows (MSVC):**
```sh
cl /EHsc main.cpp /link /OUT:main.exe
```

### Running the Application

```sh
main.exe
```

### Menu Options

1. **Load Log File** - Load a log file for analysis
2. **View All Logs** - Display all log entries
3. **View INFO Logs** - Filter and display only INFO level logs
4. **View WARN Logs** - Filter and display only WARN level logs
5. **View ERROR Logs** - Filter and display only ERROR level logs
6. **Search Logs** - Search for specific keywords in logs
7. **Show Statistics** - Display summary statistics with percentages
8. **Exit** - Close the application

## Project Structure 📁

```
Log file analyzer/
├── main.cpp      # Main source code
├── main.exe      # Compiled executable (Windows)
├── test.log      # Sample log file for testing
└── README.md     # This file
```

## Requirements 📋

- **Compiler**: C++11 or higher (g++, clang++, MSVC)
- **Operating System**: Windows (uses Windows.h for console setup)
- **Dependencies**: Standard C++ library only

## Features in Detail 🔍

### Color-Coded Output
- 🟢 **INFO** - Green
- 🟡 **WARN** - Yellow
- 🔴 **ERROR** - Red
- 🔵 **Timestamps** - Cyan

### Statistics
- Total log entries count
- Breakdown by log level
- Percentage distribution

## Example Session 💻

```
1. Load Log File
   Enter: test.log
   ✓ Loaded 150 log entries.

2. Show Statistics
   Total Entries: 150
   INFO: 120 (80.0%)
   WARN: 20 (13.3%)
   ERROR: 10 (6.7%)

3. Search Logs
   Enter: database
   (Shows all logs containing "database")
```

## License 📄

This project is open source and available under the MIT License.

## Author ✍️

Created as part of the 52 Projects challenge.
