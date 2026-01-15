/*
 * ═══════════════════════════════════════════════════════════════════════════
 * LOG FILE ANALYZER
 * ═══════════════════════════════════════════════════════════════════════════
 * 
 * A comprehensive log file parsing, filtering, and analysis tool with:
 * - Multiple log format support (3 different timestamp patterns)
 * - Color-coded output with animated gradient banner
 * - Advanced filtering by log level and time range
 * - Case-insensitive search with history tracking
 * - Export functionality with timestamped filenames
 * - Visual statistics with bar charts
 * 
 * Author: Marcel Bialk
 * Date: January 15, 2026
 * C++ Standard: C++17
 * 
 * ═══════════════════════════════════════════════════════════════════════════
 */

// ═══════════════════════════════════════════════════════════════════════════
// INCLUDES
// ═══════════════════════════════════════════════════════════════════════════

#include <windows.h>        // Windows console API for ANSI color support

#include <iostream>         // Input/output streams
#include <fstream>          // File streams
#include <string>           // String operations
#include <vector>           // Dynamic arrays
#include <regex>            // Regular expressions for log parsing
#include <unordered_map>    // Hash maps for statistics
#include <algorithm>        // STL algorithms (find, transform, etc.)
#include <limits>           // Numeric limits
#include <chrono>           // Time operations for timestamps
#include <thread>           // Thread sleep for animations
#include <sstream>          // String streams
#include <iomanip>          // I/O manipulators (setw, setprecision)
#include <filesystem>       // File system operations (C++17)

// ═══════════════════════════════════════════════════════════════════════════
// NAMESPACE DECLARATIONS
// ═══════════════════════════════════════════════════════════════════════════

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;
using std::ostringstream;
using std::regex;
using std::smatch;
using std::unordered_map;
using std::getline;
using std::flush;
using std::fixed;
using std::setprecision;
using std::numeric_limits;
using std::streamsize;
using std::regex_match;
using std::transform;
using std::tolower;

// ═══════════════════════════════════════════════════════════════════════════
// ANSI COLOR CODE DEFINITIONS
// ═══════════════════════════════════════════════════════════════════════════

#define RESET          "\033[0m"           // Reset all attributes
#define RED            "\033[38;5;131m"    // Muted red for ERROR
#define GREEN          "\033[38;5;108m"    // Muted green for INFO
#define YELLOW         "\033[38;5;179m"    // Muted yellow for WARN
#define BLUE           "\033[38;5;67m"     // Muted blue
#define MAGENTA        "\033[38;5;132m"    // Muted magenta
#define CYAN           "\033[38;5;73m"     // Muted cyan for timestamps
#define BRIGHT_RED     "\033[38;5;167m"    // Bright red
#define BRIGHT_GREEN   "\033[38;5;114m"    // Bright green
#define BRIGHT_YELLOW  "\033[38;5;185m"    // Bright yellow
#define BRIGHT_BLUE    "\033[38;5;74m"     // Bright blue
#define BRIGHT_MAGENTA "\033[38;5;139m"    // Bright magenta
#define BRIGHT_CYAN    "\033[38;5;80m"     // Bright cyan for headers

// ═══════════════════════════════════════════════════════════════════════════
// CONSTANTS
// ═══════════════════════════════════════════════════════════════════════════

constexpr int BANNER_ANIMATION_FRAMES = 40;  // Number of animation frames
constexpr int BANNER_FRAME_DELAY_MS = 80;    // Milliseconds per frame

// ═══════════════════════════════════════════════════════════════════════════
// DATA STRUCTURES
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Represents a single log entry with timestamp, level, and message
 */
struct LogEntry {
    string timestamp;  // Format: YYYY-MM-DD HH:MM:SS
    string level;      // INFO, WARN, ERROR, etc.
    string message;    // Log message content
};

// ═══════════════════════════════════════════════════════════════════════════
// GLOBAL VARIABLES
// ═══════════════════════════════════════════════════════════════════════════

vector<LogEntry> logs;              // Stores all loaded log entries
vector<string> searchHistory;       // Tracks user search queries

// ───────────────────────────────────────────────────────────────────────────
// Regular Expression Patterns for Log Parsing
// ───────────────────────────────────────────────────────────────────────────

// Format 1: YYYY-MM-DD HH:MM:SS [LEVEL] Message
static const regex LOG_REGEX(R"((\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}) \[(\w+)\] (.*))");

// Format 2: [YYYY-MM-DD HH:MM:SS] LEVEL: Message
static const regex LOG_REGEX_ALT1(R"(\[(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})\] (\w+): (.*))");

// Format 3: MM/DD/YYYY HH:MM:SS - LEVEL - Message
static const regex LOG_REGEX_ALT2(R"((\d{2}/\d{2}/\d{4} \d{2}:\d{2}:\d{2}) - (\w+) - (.*))");

// ═══════════════════════════════════════════════════════════════════════════
// FUNCTION DECLARATIONS
// ═══════════════════════════════════════════════════════════════════════════

// ───────────────────────────────────────────────────────────────────────────
// Console & Display Functions
// ───────────────────────────────────────────────────────────────────────────
void setupConsole();                                           // Initialize console for ANSI colors
string getGradientColor(int lineIndex, int colIndex, int frame); // Generate gradient colors
void displayWelcomeBanner();                                   // Show animated banner
void displayMenu();                                            // Display main menu

// ───────────────────────────────────────────────────────────────────────────
// Core Log Management Functions
// ───────────────────────────────────────────────────────────────────────────
void loadLogFile();                                            // Load and parse log file
void viewLogs(const string& filter = "");                      // Display logs with optional filter
void searchLogs();                                             // Search logs by keyword
void showStatistics();                                         // Display visual statistics
void viewSearchHistory();                                      // Show search history
void viewLogsByTimeRange();                                    // Filter logs by date/time range

// ───────────────────────────────────────────────────────────────────────────
// Export Functions
// ───────────────────────────────────────────────────────────────────────────
void exportLogs(const vector<LogEntry>& entries, const string& description); // Export logs to file
void exportMenu();                                             // Display export menu
vector<LogEntry> getFilteredLogs(const string& filter);        // Get logs by level filter

// ───────────────────────────────────────────────────────────────────────────
// Utility Functions
// ───────────────────────────────────────────────────────────────────────────
bool logsEmpty();                                              // Check if logs vector is empty
string getLevelColor(const string& level);                     // Get ANSI color for log level
string toLowerStr(const string& str);                          // Convert string to lowercase
bool caseInsensitiveSearch(const string& text, const string& keyword); // Case-insensitive search
bool parseLogLine(const string& line, LogEntry& entry);        // Parse log line to LogEntry
bool isValidLogPath(const string& filename);                   // Validate file path security

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: CONSOLE SETUP
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Configure Windows console to support UTF-8 and ANSI escape sequences
 * Required for displaying colors and special characters correctly
 */
void setupConsole() {
    SetConsoleOutputCP(CP_UTF8);  // Set output code page to UTF-8
    SetConsoleCP(CP_UTF8);        // Set input code page to UTF-8
    
    // Enable ANSI escape sequence processing (Windows 10+)
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: GRADIENT COLOR GENERATOR
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Generate gradient colors for animated banner
 * 
 * @param lineIndex  Vertical position in banner
 * @param colIndex   Horizontal position in banner
 * @param frame      Current animation frame number
 * @return           ANSI color code string
 */
string getGradientColor(int lineIndex, int colIndex, int frame) {
    // 20 predefined colors creating smooth gradient transition
    const string colors[] = {
        "\033[38;5;131m", "\033[38;5;137m", "\033[38;5;173m", "\033[38;5;179m",
        "\033[38;5;185m", "\033[38;5;186m", "\033[38;5;150m", "\033[38;5;114m",
        "\033[38;5;108m", "\033[38;5;72m",  "\033[38;5;73m",  "\033[38;5;80m",
        "\033[38;5;74m",  "\033[38;5;67m",  "\033[38;5;61m",  "\033[38;5;97m",
        "\033[38;5;103m", "\033[38;5;139m", "\033[38;5;132m", "\033[38;5;168m"
    };
    
    // Calculate color index based on position and animation frame
    int colorIndex = (lineIndex + colIndex + frame) % 20;
    return colors[colorIndex];
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: ANIMATED WELCOME BANNER
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Display animated welcome banner with gradient color effects
 * Animates through 40 frames, cycling colors across the ASCII art banner
 */
void displayWelcomeBanner() {
    // Animate through all frames
    for (int frame = 0; frame < BANNER_ANIMATION_FRAMES; ++frame) {
        cout << "\033[H\033[2J";  // ANSI: Clear screen and move cursor to home
        cout << "\n";
        
        // Draw banner border and ASCII art with dynamic gradient colors
        cout << "  " << getGradientColor(0, 0, frame) << "╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << "\n";
        cout << "  " << getGradientColor(0, 0, frame) << "║" << RESET << "                                                                                                           " << getGradientColor(0, 80, frame) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(1, 0, frame) << "║" << RESET << "      " << getGradientColor(1, 4, frame) << "██╗      ██████╗  ██████╗      █████╗ ███╗   ██╗ █████╗ ██╗  ██╗   ██╗███████╗███████╗██████╗ " << RESET << " " << getGradientColor(1, 80, frame) << "      ║" << RESET << "\n";
        cout << "  " << getGradientColor(2, 0, frame) << "║" << RESET << "      " << getGradientColor(2, 4, frame) << "██║     ██╔═══██╗██╔════╝     ██╔══██╗████╗  ██║██╔══██╗██║  ╚██╗ ██╔╝╚══███╔╝██╔════╝██╔══██╗" << RESET << " " << getGradientColor(2, 80, frame) << "      ║" << RESET << "\n";
        cout << "  " << getGradientColor(3, 0, frame) << "║" << RESET << "      " << getGradientColor(3, 4, frame) << "██║     ██║   ██║██║  ███╗    ███████║██╔██╗ ██║███████║██║   ╚████╔╝   ███╔╝ █████╗  ██████╔╝" << RESET << " " << getGradientColor(3, 80, frame) << "      ║" << RESET << "\n";
        cout << "  " << getGradientColor(4, 0, frame) << "║" << RESET << "      " << getGradientColor(4, 4, frame) << "██║     ██║   ██║██║   ██║    ██╔══██║██║╚██╗██║██╔══██║██║    ╚██╔╝   ███╔╝  ██╔══╝  ██╔══██╗" << RESET << " " << getGradientColor(4, 80, frame) << "      ║" << RESET << "\n";
        cout << "  " << getGradientColor(5, 0, frame) << "║" << RESET << "      " << getGradientColor(5, 4, frame) << "███████╗╚██████╔╝╚██████╔╝    ██║  ██║██║ ╚████║██║  ██║███████╗██║   ███████╗███████╗██║  ██║" << RESET << " " << getGradientColor(5, 80, frame) << "      ║" << RESET << "\n";
        cout << "  " << getGradientColor(6, 0, frame) << "║" << RESET << "      " << getGradientColor(6, 4, frame) << "╚══════╝ ╚═════╝  ╚═════╝     ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚═╝   ╚══════╝╚══════╝╚═╝  ╚═╝" << RESET << " " << getGradientColor(6, 80, frame) << "      ║" << RESET << "\n";
        cout << "  " << getGradientColor(7, 0, frame) << "║" << RESET << "                                                                                                           " << getGradientColor(7, 80, frame) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(8, 0, frame) << "║" << RESET << "                                            " << getGradientColor(8, 25, frame) << "Parse • Filter • Analyze" << RESET << "                                       " << getGradientColor(8, 80, frame) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(9, 0, frame) << "║" << RESET << "                                                                                                           " << getGradientColor(9, 80, frame) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(10, 0, frame) << "╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << "\n";
        
        cout << flush;  // Force output buffer to display immediately
        std::this_thread::sleep_for(std::chrono::milliseconds(BANNER_FRAME_DELAY_MS));
    }
    
    // Hold final frame for dramatic effect
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: MENU DISPLAY
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Display main application menu with color-coded options
 * Menu is organized in two columns for better space usage
 */
void displayMenu() {
    cout << "\n";
    cout << "  " << CYAN << "╔══════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "                    " << BRIGHT_CYAN << "LOG ANALYZER MENU" << RESET << "                 " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "╠══════════════════════════════════════════════════════╣" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << GREEN  << "1."  << RESET << " Load Log File            " << BLUE           << "7."  << RESET << " Show Statistics      " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << GREEN  << "2."  << RESET << " View All Logs            " << MAGENTA        << "8."  << RESET << " View Search History  " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << BLUE   << "3."  << RESET << " View INFO Logs           " << BRIGHT_MAGENTA << "9."  << RESET << " Export Filtered Logs " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << YELLOW << "4."  << RESET << " View WARN Logs           " << BRIGHT_BLUE    << "10." << RESET << " View Logs by Time    " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << RED    << "5."  << RESET << " View ERROR Logs          " << BRIGHT_RED     << "11." << RESET << " Search & Export      " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << BLUE   << "6."  << RESET << " Search Logs              " << BRIGHT_GREEN   << "12." << RESET << " Exit                 " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "                                                      " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "╚══════════════════════════════════════════════════════╝" << RESET << "\n";
    cout << "\n  " << BRIGHT_CYAN << "Select an option (1-12): " << RESET;
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: UTILITY FUNCTIONS
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Check if logs vector is empty and display error message
 * 
 * @return true if logs are empty, false otherwise
 */
bool logsEmpty() {
    if (logs.empty()) {
        cout << RED << "\n  ⚠ No logs loaded. Please load a log file first.\n" << RESET;
        return true;
    }
    return false;
}

/**
 * Get ANSI color code for a log level
 * 
 * @param level Log level string (INFO, WARN, ERROR)
 * @return      ANSI color code string
 */
string getLevelColor(const string& level) {
    if (level == "INFO") return GREEN;
    if (level == "WARN") return YELLOW;
    if (level == "ERROR") return RED;
    return RESET;  // Default color for unknown levels
}

/**
 * Convert a string to lowercase
 * Uses lambda with std::transform for character-by-character conversion
 * 
 * @param str Input string
 * @return    Lowercase version of input string
 */
string toLowerStr(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

/**
 * Perform case-insensitive substring search
 * 
 * @param text    Text to search in
 * @param keyword Keyword to search for
 * @return        true if keyword found (case-insensitive), false otherwise
 */
/**
 * Perform case-insensitive substring search
 * 
 * @param text    Text to search in
 * @param keyword Keyword to search for
 * @return        true if keyword found (case-insensitive), false otherwise
 */
bool caseInsensitiveSearch(const string& text, const string& keyword) {
    string lowerText = toLowerStr(text);
    string lowerKeyword = toLowerStr(keyword);
    return lowerText.find(lowerKeyword) != string::npos;
}

/**
 * Filter logs by level
 * 
 * @param filter Log level to filter by (empty string returns all logs)
 * @return       Vector of filtered log entries
 */
vector<LogEntry> getFilteredLogs(const string& filter) {
    vector<LogEntry> filtered;
    for(const auto& entry : logs) {
        if(filter.empty() || entry.level == filter) {
            filtered.push_back(entry);
        }
    }
    return filtered;
}

/**
 * Validate file path for security
 * Prevents directory traversal attacks by checking:
 * - File is in current directory or Log subdirectory
 * - Path doesn't contain ".." sequences
 * 
 * @param filename File path to validate
 * @return         true if path is safe, false otherwise
 */
bool isValidLogPath(const string& filename) {
    namespace fs = std::filesystem;

    try {
        // Resolve to absolute path
        fs::path filePath = fs::absolute(filename);

        // Allow non-existent paths (will fail later with better error message)
        if(!fs::exists(filePath)) {
            return true;
        }
        
        // Get allowed directories
        fs::path currentPath = fs::current_path();
        fs::path logDir = currentPath / "Log";

        string filePathStr = filePath.string();
        string currentPathStr = currentPath.string();
        string logDirStr = logDir.string();

        // Check if file is in current directory or Log subdirectory
        if(filePathStr.find(currentPathStr) == 0 || filePathStr.find(logDirStr) == 0) {
            return true;
        }

        // Check for directory traversal attempts
        if(filename.find("..") == string::npos && 
           filename.find("\\..") == string::npos && 
           filename.find("/..") == string::npos) {
            return true;
        }
        
        return false;
    } catch (...) {
        // Catch filesystem errors
        return false;
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: LOAD LOG FILE
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Load and parse a log file
 * 
 * Features:
 * - Supports 3 different log formats via regex parsing
 * - Security validation to prevent path traversal
 * - Reports number of loaded and skipped entries
 * - Clears existing logs before loading new file
 */
void loadLogFile() {
    string filename;
    cout << "\n  " << GREEN << "Enter log file name: " << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, filename);

    // Validate empty input
    if (filename.empty()) {
        cerr << RED << "  ✗ No filename provided.\n" << RESET;
        return;
    }

    // Warn about missing .log extension
    if (filename.find(".log") == string::npos) {
        cout << YELLOW << "  ⚠ Warning: File doesn't have .log extension\n" << RESET;
    }

    // Security: Validate file path to prevent directory traversal
    if (!isValidLogPath(filename)) {
        cerr << RED << "  ✗ Invalid or unauthorized file path.\n" << RESET;
        return;
    }

    // Attempt to open file
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << RED << "  ✗ Could not open file: " << filename << RESET << "\n";
        return;
    }

    // Check file size and warn if large
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    if(fileSize > 10 * 1024 * 1024) {  // 10MB threshold
        double sizeMB = fileSize / (1024.0 * 1024.0);
        cout << YELLOW << "  ⚠ Large file detected (" 
             << fixed << setprecision(1) << sizeMB 
             << "MB). Loading may take time...\n" << RESET;
    }

    // Clear existing logs and prepare for new data
    logs.clear();
    logs.shrink_to_fit();
    logs.reserve(1000);  // Pre-allocate for performance
    
    string line;
    smatch match;
    int skipped = 0;

    // Parse each line of the file
    while(getline(file, line)) {
        LogEntry entry;
        if(parseLogLine(line, entry)) {
            logs.push_back(entry);
        } else if(!line.empty()) {
            skipped++;  // Count malformed non-empty lines
        }
    }

    file.close();
    
    // Report results
    cout << GREEN << "  ✓ Loaded " << logs.size() << " log entries.\n" << RESET;
    if (skipped > 0) {
        cout << YELLOW << "  ⚠ Skipped " << skipped << " malformed lines\n" << RESET;
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: VIEW LOGS
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Display logs with optional level filtering
 * Uses ostringstream for efficient buffered output
 * 
 * @param filter Log level to filter by (empty = show all)
 */
void viewLogs(const string& filter) {
    if (logsEmpty()) return;

    // Display header
    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    if (filter.empty()) {
        cout << "  " << BRIGHT_CYAN << "ALL LOGS" << RESET << "\n";
    } else {
        cout << "  " << BRIGHT_CYAN << filter << " LOGS" << RESET << "\n";
    }
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

    int count = 0;
    ostringstream oss;  // Buffer output for better performance
    
    // Iterate through logs and apply filter
    for (const auto& entry : logs) {
        if (filter.empty() || entry.level == filter) {
            string levelColor = getLevelColor(entry.level);

            oss << "  " << CYAN << entry.timestamp << RESET 
                << " [" << levelColor << entry.level << RESET << "] " 
                << entry.message << "\n";
            count++;
        }
    }
    
    // Display buffered output and footer
    cout << oss.str();
    cout << "  " << BRIGHT_CYAN << "─────────────────────────────────────────────────────────────" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "Total: " << count << " entries" << RESET << "\n\n";
}

/**
 * Display logs with pagination (unused placeholder function)
 * 
 * @param filter   Log level filter
 * @param pageSize Number of entries per page
 */
void viewLogsPaginated(const string& filter, int pageSize = 20) {
    if(logsEmpty()) return;

    vector<LogEntry> filtered = getFilteredLogs(filter);
    if(filtered.empty()) {
        cout << RED << "\n  ✗ No logs match the filter.\n" << RESET;
        return;
    }

    size_t totalPages = (filtered.size() + pageSize - 1) / pageSize;
    size_t currentPage = 0;

    // Pagination loop
    while(true) {
        cout << "\033[H\033[2J";  // Clear screen
        
        // Display header with page info
        cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
        if(filter.empty()) {
            cout << "  " << BRIGHT_CYAN << "ALL LOGS (Page " << (currentPage + 1) << "/" << totalPages << ")" << RESET << "\n";
        } else {
            cout << "  " << BRIGHT_CYAN << filter << " LOGS (Page " << (currentPage + 1) << "/" << totalPages << ")" << RESET << "\n";
        }
        cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

        // Calculate page range
        size_t start = currentPage * pageSize;
        size_t end = std::min(start + pageSize, filtered.size());

        // Display logs for current page
        for(size_t i = start; i < end; ++i) {
            const auto& entry = filtered[i];
            string levelColor = getLevelColor(entry.level);
            cout << "  " << CYAN << entry.timestamp << RESET 
                 << " [" << levelColor << entry.level << RESET << "] " 
                 << entry.message << "\n";
        }

        // Display navigation footer
        cout << "\n  " << BRIGHT_CYAN << "─────────────────────────────────────────────────────────────" << RESET << "\n";
        cout << "  " << BRIGHT_CYAN << "Showing " << (start + 1) << "-" << end << " of " << filtered.size() << " entries" << RESET << "\n";
        cout << "  [N]ext  [P]revious  [Q]uit: ";

        // Handle user input
        char input;
        cin >> input;
        input = std::tolower(input);

        if(input == 'n' && currentPage < totalPages - 1) {
            currentPage++;
        } else if(input == 'p' && currentPage > 0) {
            currentPage--;
        } else if(input == 'q') {
            break;
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: SEARCH LOGS
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Search logs for keyword (case-insensitive)
 * Searches both message content and log level
 * Automatically adds search to history
 */
void searchLogs() {
    if (logsEmpty()) return;

    // Get search keyword from user
    string keyword;
    cout << "\n  " << YELLOW << "Enter search keyword: " << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyword);

    // Validate input
    if (keyword.empty()) {
        cerr << RED << "  ✗ No search keyword provided.\n" << RESET;
        return;
    }

    // Track search in history
    searchHistory.push_back(keyword);

    // Display search header
    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "SEARCH RESULTS FOR: \"" << keyword << "\" (case-insensitive)" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

    int matchCount = 0;
    ostringstream oss;
    
    // Search through all log entries
    for (const auto& entry : logs) {
        // Check if keyword appears in message or level
        if (caseInsensitiveSearch(entry.message, keyword) || 
            caseInsensitiveSearch(entry.level, keyword)) {
            
            string levelColor = getLevelColor(entry.level);

            oss << "  " << CYAN << entry.timestamp << RESET 
                << " [" << levelColor << entry.level << RESET << "] " 
                << entry.message << "\n";
            matchCount++;
        }
    }

    // Display results or no-match message
    if (matchCount > 0) {
        cout << oss.str();
        cout << "\n  " << BRIGHT_CYAN << "─────────────────────────────────────────────────────────────" << RESET << "\n";
        cout << "  " << BRIGHT_CYAN << "Found: " << matchCount << " matching entries" << RESET << "\n";
    } else {
        cout << "  " << RED << "✗ No matching logs found.\n" << RESET;
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: SEARCH AND EXPORT
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Search logs and optionally export results
 * Combines search functionality with immediate export option
 * Displays preview of first 10 results before export confirmation
 */
void searchAndExport() {
    if(logsEmpty()) return;

    // Get search keyword
    string keyword;
    cout << "\n  " << YELLOW << "Enter search keyword: " << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyword);

    // Validate input
    if(keyword.empty()) {
        cerr << RED << "  ✗ No search keyword provided.\n" << RESET;
        return;
    }

    // Add to search history
    searchHistory.push_back(keyword);

    // Collect all matching results
    vector<LogEntry> results;
    for(const auto& entry : logs) {
        if(caseInsensitiveSearch(entry.message, keyword) || 
           caseInsensitiveSearch(entry.level, keyword)) {
            results.push_back(entry);
        }
    }

    // Check if any matches found
    if(results.empty()) {
        cout << RED << "\n  ✗ No matching logs found.\n" << RESET;
        return;
    }

    // Display search results header
    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "SEARCH RESULTS FOR: \"" << keyword << "\"" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

    // Show preview (first 10 results)
    int displayCount = std::min(10, (int)results.size());
    for(int i = 0; i < displayCount; ++i) {
        const auto& entry = results[i];
        string levelColor = getLevelColor(entry.level);
        cout << "  " << CYAN << entry.timestamp << RESET 
             << " [" << levelColor << entry.level << RESET << "] " 
             << entry.message << "\n";
    }

    // Show count of additional results
    if(results.size() > 10) {
        cout << "  " << YELLOW << "... and " << (results.size() - 10) 
             << " more matches\n" << RESET;
    }

    // Prompt for export
    cout << "\n  " << GREEN << "✓ Found " << results.size() << " matches.\n" << RESET;
    cout << "  Do you want to export these results? (y/n): ";

    char choice;
    cin >> choice;

    if(choice == 'y' || choice == 'Y') {
        ostringstream desc;
        desc << "Search results for: \"" << keyword << "\"";
        exportLogs(results, desc.str());
    } else {
        cout << YELLOW << "  Export cancelled.\n" << RESET;
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: STATISTICS DISPLAY
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Display comprehensive log statistics with visual bar charts
 * 
 * Features:
 * - Total entry count
 * - Bar charts for each log level (max 50 chars wide)
 * - Percentage calculations
 * - Time range information (first and last entry timestamps)
 * - Support for custom/unknown log levels
 */
void showStatistics() {
    if (logsEmpty()) return;

    // Count occurrences of each log level
    unordered_map<string, int> countMap;
    int maxCount = 0;

    for(const auto& entry : logs) {
        countMap[entry.level]++;
        maxCount = std::max(maxCount, countMap[entry.level]);
    }

    // Display header
    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "LOG STATISTICS" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";
    cout << "  " << BRIGHT_CYAN << "Total Entries: " << logs.size() << RESET << "\n\n";

    // Standard log levels to display first
    vector<string> levels = {"INFO", "WARN", "ERROR"};

    // Display statistics for standard levels
    for(const auto& level : levels) {
        if(countMap.find(level) == countMap.end()) continue;
        
        int count = countMap[level];
        string levelColor = getLevelColor(level);
        double percentage = logs.empty() ? 0.0 : (count * 100.0 / logs.size());

        // Create visual bar chart (proportional to count, max 50 chars)
        int barLength = maxCount > 0 ? (count * 50) / maxCount : 0;
        string bar;
        for(int i = 0; i < barLength; ++i) bar += "█";

        cout << "  " << levelColor << std::left << std::setw(8) << level << RESET 
             << " " << levelColor << bar << RESET 
             << " " << count << " (" << fixed << setprecision(1) << percentage << "%)\n";
    }

    // Display any custom/unknown log levels
    for(const auto& pair : countMap) {
        if (std::find(levels.begin(), levels.end(), pair.first) == levels.end()) {
            double percentage = logs.empty() ? 0.0 : (pair.second * 100.0 / logs.size());
            int barLength = maxCount > 0 ? (pair.second * 50) / maxCount : 0;
            string bar;
            for(int i = 0; i < barLength; ++i) bar += "█";

            cout << "  " << CYAN << std::left << std::setw(8) << pair.first << RESET 
                 << " " << CYAN << bar << RESET 
                 << " " << pair.second << " (" << fixed << setprecision(1) << percentage << "%)\n";
        } 
    }

    // Display time range information
    if (!logs.empty()) {
        cout << "\n  " << BRIGHT_CYAN << "─────────────────────────────────────────────────────────────" << RESET << "\n";
        cout << "  " << CYAN << "First Entry: " << RESET << logs.front().timestamp << "\n";
        cout << "  " << CYAN << "Last Entry:  " << RESET << logs.back().timestamp << "\n";
    }
    
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: VIEW SEARCH HISTORY
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Display all previous search queries
 * Shows numbered list of all searches performed in current session
 */
void viewSearchHistory() {
    if (searchHistory.empty()) {
        cout << YELLOW << "\n  ⚠ No search history available.\n" << RESET;
        return;
    }

    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "SEARCH HISTORY" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

    // Display each search with index number
    for (size_t i = 0; i < searchHistory.size(); ++i) {
        cout << "  " << CYAN << (i + 1) << ". " << RESET << searchHistory[i] << "\n";
    }
    cout << "\n";
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: EXPORT LOGS TO FILE
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Export log entries to a timestamped text file
 * 
 * Features:
 * - Automatically adds timestamp to filename (YYYYMMDD_HHMMSS format)
 * - Includes comprehensive header with metadata
 * - Shows export description and entry count
 * - Creates file in current working directory
 * 
 * @param entries     Vector of log entries to export
 * @param description Description of the filter/search used
 */
void exportLogs(const vector<LogEntry> & entries, const string& description) {
    if(entries.empty()) {
        cout << RED << "\n  ✗ No logs to export.\n" << RESET;
        return;
    }

    // Get filename from user
    string filename;
    cout << "\n  " << GREEN << "Enter export filename (without extension): " << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, filename);

    // Validate filename
    if(filename.empty()) {
        cerr << RED << "  ✗ No filename provided.\n" << RESET;
        return;
    }

    // Generate timestamped filename to avoid overwriting
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    ostringstream oss;
    oss << filename << "_" 
        << std::put_time(std::localtime(&time_t_now), "%Y%m%d_%H%M%S") 
        << ".txt";
    string fullFilename = oss.str();

    // Create output file
    std::ofstream outFile(fullFilename);
    if (!outFile.is_open()) {
        cerr << RED << "  ✗ Could not create export file.\n" << RESET;
        return;
    }

    // Write file header
    outFile << "========================================\n";
    outFile << "LOG ANALYZER EXPORT\n";
    outFile << description << "\n";
    outFile << "Exported: " 
            << std::put_time(std::localtime(&time_t_now), "%Y-%m-%d %H:%M:%S") 
            << "\n";
    outFile << "Total Entries: " << entries.size() << "\n";
    outFile << "========================================\n\n";

    // Calculate statistics for export
    unordered_map<string, int> levelCount;
    for(const auto& entry : entries) {
        levelCount[entry.level]++;
    }

    // Write statistics section
    outFile << "\n--- Statistics ---\n";
    for (const auto& pair : levelCount) {
        double percentage = (pair.second * 100.0) / entries.size();
        outFile << pair.first << ": " << pair.second 
                << " (" << fixed << setprecision(1) << percentage << "%)\n";
    }

    // Write time range if entries exist
    if(!entries.empty()) {
        outFile << "\nTime Range:\n";
        outFile << "  First: " << entries.front().timestamp << "\n";
        outFile << "  Last:  " << entries.back().timestamp << "\n";
    }
    outFile << "========================================\n\n";

    // Write all log entries
    for(const auto& entry : entries) {
        outFile << entry.timestamp << " [" << entry.level << "] " 
                << entry.message << "\n";
    }

    outFile.close();
    
    // Confirm successful export
    cout << GREEN << "  ✓ Exported " << entries.size() 
         << " entries to " << fullFilename << "\n" << RESET;
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: EXPORT MENU
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Display export menu and handle user selection
 * Allows exporting logs filtered by level or all logs
 */
void exportMenu() {
    if(logsEmpty()) return;

    // Display export options
    cout << "\n  " << BRIGHT_CYAN << "EXPORT OPTIONS" << RESET << "\n";
    cout << "  1. Export All Logs\n";
    cout << "  2. Export INFO Logs\n";
    cout << "  3. Export WARN Logs\n";
    cout << "  4. Export ERROR Logs\n";
    cout << "  5. Cancel\n";
    cout << "\n  " << BRIGHT_CYAN << "Select option (1-5): " << RESET;

    int choice;
    cin >> choice;

    // Handle invalid input
    if(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "\n  ✗ Invalid input.\n" << RESET;
        return;
    }

    // Execute export based on user choice
    switch (choice) {
        case 1: exportLogs(logs, "Filter: ALL"); break;
        case 2: exportLogs(getFilteredLogs("INFO"), "Filter: INFO"); break;
        case 3: exportLogs(getFilteredLogs("WARN"), "Filter: WARN"); break;
        case 4: exportLogs(getFilteredLogs("ERROR"), "Filter: ERROR"); break;
        case 5: cout << YELLOW << "  Export cancelled.\n" << RESET; break;
        default: cout << RED << "\n  ✗ Invalid option.\n" << RESET; break;
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: TIME RANGE FUNCTIONS
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Parse a timestamp string into a tm struct
 * Expected format: YYYY-MM-DD HH:MM:SS
 * 
 * @param timestamp String timestamp to parse
 * @param tm_struct Output tm struct to populate
 * @return          true if parsing succeeded, false otherwise
 */
bool parseTimestamp(const string& timestamp, std::tm& tm_struct) {
    istringstream ss(timestamp);
    ss >> std::get_time(&tm_struct, "%Y-%m-%d %H:%M:%S");
    return !ss.fail();
}

/**
 * Check if a timestamp falls within a time range
 * 
 * @param timestamp Timestamp to check (YYYY-MM-DD HH:MM:SS)
 * @param startTime Range start time (YYYY-MM-DD HH:MM:SS)
 * @param endTime   Range end time (YYYY-MM-DD HH:MM:SS)
 * @return          true if timestamp is within range, false otherwise
 */
bool isWithinTimeRange(const string& timestamp, const string& startTime, const string& endTime) {
    std::tm entry_tm = {}, start_tm = {}, end_tm = {};

    // Parse all timestamps
    if(!parseTimestamp(timestamp, entry_tm) || 
       !parseTimestamp(startTime, start_tm) || 
       !parseTimestamp(endTime, end_tm)) {
        return false;
    }

    // Convert to time_t for comparison
    time_t entry_time = std::mktime(&entry_tm);
    time_t start = std::mktime(&start_tm);
    time_t end = std::mktime(&end_tm);
    
    return entry_time >= start && entry_time <= end;
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: VIEW LOGS BY TIME RANGE
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Display logs filtered by time range
 * Prompts user for start and end times, validates format, then displays matching logs
 */
void viewLogsByTimeRange() {
    if(logsEmpty()) return;

    // Get time range from user
    string startTime, endTime;
    cout << "\n  " << YELLOW << "Enter start time (YYYY-MM-DD HH:MM:SS): " << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, startTime);

    cout << "  " << YELLOW << "Enter end time (YYYY-MM-DD HH:MM:SS): " << RESET;
    getline(cin, endTime);

    // Validate start time format
    std::tm test_tm = {};
    if(!parseTimestamp(startTime, test_tm)) {
        cout << RED << "\n  ✗ Invalid start time format. Please use YYYY-MM-DD HH:MM:SS\n" << RESET;
        return;
    }
    
    // Validate end time format
    test_tm = {};
    if(!parseTimestamp(endTime, test_tm)) {
        cout << RED << "\n  ✗ Invalid end time format. Please use YYYY-MM-DD HH:MM:SS\n" << RESET;
        return;
    }

    // Display header with time range
    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "LOGS FROM " << startTime << " TO " << endTime << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

    int count = 0;
    ostringstream oss;
    
    // Filter logs by time range
    for (const auto& entry : logs) {
        if(isWithinTimeRange(entry.timestamp, startTime, endTime)) {
            string levelColor = getLevelColor(entry.level);
            oss << "  " << CYAN << entry.timestamp << RESET 
                << " [" << levelColor << entry.level << RESET << "] " 
                << entry.message << "\n";
            count++;
        }
    }

    // Display results
    if (count > 0) {
        cout << oss.str();
        cout << "  " << BRIGHT_CYAN << "─────────────────────────────────────────────────────────────" << RESET << "\n";
        cout << "  " << BRIGHT_CYAN << "Total: " << count << " entries" << RESET << "\n\n";
    } else {
        cout << "  " << RED << "✗ No logs found in specified time range.\n" << RESET;
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: LOG LINE PARSING
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Parse a single log line using multiple regex patterns
 * Attempts to match against 3 different log formats:
 * 1. YYYY-MM-DD HH:MM:SS [LEVEL] Message
 * 2. [YYYY-MM-DD HH:MM:SS] LEVEL: Message  
 * 3. MM/DD/YYYY HH:MM:SS - LEVEL - Message
 * 
 * @param line  Log line string to parse
 * @param entry LogEntry struct to populate with parsed data
 * @return      true if parsing succeeded, false if no format matched
 */
bool parseLogLine(const string& line, LogEntry& entry) {
    smatch match;

    // Try format 1: YYYY-MM-DD HH:MM:SS [LEVEL] Message
    if(regex_match(line, match, LOG_REGEX)) {
        entry.timestamp = match[1];
        entry.level = match[2];
        entry.message = match[3];
        return true;
    }

    // Try format 2: [YYYY-MM-DD HH:MM:SS] LEVEL: Message
    if(regex_match(line, match, LOG_REGEX_ALT1)) {
        entry.timestamp = match[1];
        entry.level = match[2];
        entry.message = match[3];
        return true;
    }

    // Try format 3: MM/DD/YYYY HH:MM:SS - LEVEL - Message
    if(regex_match(line, match, LOG_REGEX_ALT2)) {
        entry.timestamp = match[1];
        entry.level = match[2];
        entry.message = match[3];
        return true;
    }
    
    // No format matched
    return false;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN FUNCTION
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Application entry point
 * 
 * Workflow:
 * 1. Initialize console for ANSI color support
 * 2. Display animated welcome banner
 * 3. Enter main menu loop:
 *    - Display menu options
 *    - Process user input
 *    - Execute corresponding function
 *    - Loop until user selects exit
 * 
 * @return 0 on successful exit
 */
int main() {
    // Initialize console for UTF-8 and ANSI colors
    setupConsole();
    
    // Show animated welcome banner
    displayWelcomeBanner();

    int choice;

    // Main application loop
    while (true) {
        displayMenu();
        cin >> choice;

        // Handle invalid input (non-numeric)
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "\n  ✗ Invalid input. Please enter a number.\n" << RESET;
            continue;
        }

        // Process menu selection
        switch (choice) {
            case 1: 
                loadLogFile(); 
                break;
                
            case 2: 
                viewLogs(); 
                break;
                
            case 3: 
                viewLogs("INFO"); 
                break;
                
            case 4: 
                viewLogs("WARN"); 
                break;
                
            case 5: 
                viewLogs("ERROR"); 
                break;
                
            case 6: 
                searchLogs(); 
                break;
                
            case 7: 
                showStatistics();
                break;
                
            case 8: 
                viewSearchHistory(); 
                break;
                
            case 9: 
                exportMenu();
                break;
                
            case 10:
                viewLogsByTimeRange();
                break;
                
            case 11:
                searchAndExport();
                break;
                
            case 12:
                cout << "\n  " << GREEN << "✓ Exiting Log Analyzer. Goodbye!\n\n" << RESET; 
                return 0;
                
            default: 
                cout << RED << "\n  ✗ Invalid option. Please select 1-12.\n" << RESET; 
                break;
        }
    }

    return 0;
}