#include <windows.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>
#include <filesystem>

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

// ANSI Color codes
#define RESET          "\033[0m"
#define RED            "\033[38;5;131m"
#define GREEN          "\033[38;5;108m"
#define YELLOW         "\033[38;5;179m"
#define BLUE           "\033[38;5;67m"
#define MAGENTA        "\033[38;5;132m"
#define CYAN           "\033[38;5;73m"
#define BRIGHT_RED     "\033[38;5;167m"
#define BRIGHT_GREEN   "\033[38;5;114m"
#define BRIGHT_YELLOW  "\033[38;5;185m"
#define BRIGHT_BLUE    "\033[38;5;74m"
#define BRIGHT_MAGENTA "\033[38;5;139m"
#define BRIGHT_CYAN    "\033[38;5;80m"

// Animation constants
constexpr int BANNER_ANIMATION_FRAMES = 40;
constexpr int BANNER_FRAME_DELAY_MS = 80;

// Struct for log entries
struct LogEntry {
    string timestamp;
    string level;
    string message;
};

// Global variables
vector<LogEntry> logs;
static const regex LOG_REGEX(R"((\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}) \[(\w+)\] (.*))");
static const regex LOG_REGEX_ALT1(R"(\[(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})\] (\w+): (.*))"); // [timestamp] LEVEL: message
static const regex LOG_REGEX_ALT2(R"((\d{2}/\d{2}/\d{4} \d{2}:\d{2}:\d{2}) - (\w+) - (.*))");  // MM/DD/YYYY format
// Search history for future enhancement
vector<string> searchHistory;

// Function declarations
void setupConsole();
string getGradientColor(int lineIndex, int colIndex, int frame);
void displayWelcomeBanner();
void displayMenu();
void loadLogFile();
void viewLogs(const string& filter = "");
void searchLogs();
void showStatistics();
void viewSearchHistory();
bool logsEmpty();
string getLevelColor(const string& level);
string toLowerStr(const string& str);
bool caseInsensitiveSearch(const string& text, const string& keyword);
void exportLogs(const vector<LogEntry>& entries, const string& description);
vector<LogEntry> getFilteredLogs(const string& filter);
void exportMenu();
void viewLogsByTimeRange();
bool parseLogLine(const string& line, LogEntry& entry);
bool isValidLogPath(const string& filename);

// ======== Console Setup =========
void setupConsole() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

// ======== Gradient Color Generator =========
string getGradientColor(int lineIndex, int colIndex, int frame) {
    const string colors[] = {
        "\033[38;5;131m", "\033[38;5;137m", "\033[38;5;173m", "\033[38;5;179m",
        "\033[38;5;185m", "\033[38;5;186m", "\033[38;5;150m", "\033[38;5;114m",
        "\033[38;5;108m", "\033[38;5;72m",  "\033[38;5;73m",  "\033[38;5;80m",
        "\033[38;5;74m",  "\033[38;5;67m",  "\033[38;5;61m",  "\033[38;5;97m",
        "\033[38;5;103m", "\033[38;5;139m", "\033[38;5;132m", "\033[38;5;168m"
    };
    int colorIndex = (lineIndex + colIndex + frame) % 20;
    return colors[colorIndex];
}

// ======== Welcome Banner =========
void displayWelcomeBanner() {
    for (int frame = 0; frame < BANNER_ANIMATION_FRAMES; ++frame) {
        cout << "\033[H\033[2J"; // Clear screen
        cout << "\n";
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
        
        cout << flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(BANNER_FRAME_DELAY_MS));
    }
    
    // Final frame
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

// ======== Menu Display =========
void displayMenu() {
    cout << "\n";
    cout << "  " << CYAN << "╔══════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "                    " << BRIGHT_CYAN << "LOG ANALYZER MENU" << RESET << "                 " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "╠══════════════════════════════════════════════════════╣" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << GREEN  << "1."  << RESET << " Load Log File            " << BLUE           << "7."  << RESET << " Show Statistics      " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << GREEN  << "2."  << RESET << " View All Logs            " << MAGENTA        << "8."  << RESET << " View Search History  " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << BLUE   << "3."  << RESET << " View INFO Logs           " << BRIGHT_MAGENTA << "9."  << RESET << " Export Filtered Logs " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << YELLOW << "4."  << RESET << " View WARN Logs           " << BRIGHT_BLUE    << "10." << RESET << " View Logs by Time   " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << RED    << "5."  << RESET << " View ERROR Logs          " << BRIGHT_RED     << "11." << RESET << " Search  & Export    " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << BLUE   << "6."  << RESET << " Search Logs              "<< CYAN            << "12"  << RESET << " Exit                 " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "                                                      " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "╚══════════════════════════════════════════════════════╝" << RESET << "\n";
    cout << "\n  " << BRIGHT_CYAN << "Select an option (1-12): " << RESET;
}


// ======== Helper Functions =========
bool logsEmpty() {
    if (logs.empty()) {
        cout << RED << "\n  ⚠ No logs loaded. Please load a log file first.\n" << RESET;
        return true;
    }
    return false;
}

string getLevelColor(const string& level) {
    if (level == "INFO") return GREEN;
    if (level == "WARN") return YELLOW;
    if (level == "ERROR") return RED;
    return RESET;
}

// Convert string to lowercase
string toLowerStr(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

// Case-insensitive search
bool caseInsensitiveSearch(const string& text, const string& keyword) {
    string lowerText = toLowerStr(text);
    string lowerKeyword = toLowerStr(keyword);
    return lowerText.find(lowerKeyword) != string::npos;
}

vector<LogEntry> getFilteredLogs(const string& filter) {
    vector<LogEntry> filtered;
    for(const auto& entry : logs) {
        if(filter.empty() || entry.level == filter) {
            filtered.push_back(entry);
        }
    }
    return filtered;
}

bool isValidLogPath(const string& filename) {
    namespace fs = std::filesystem;

    try {
        fs::path filePath = fs::absolute(filename);

        if(!fs::exists(filePath)) {
            return true;
        }
        fs::path currentPath = fs::current_path();
        fs::path logDir = currentPath / "Log";

        string filePathStr = filePath.string();
        string currentPathStr = currentPath.string();
        string logDirStr = logDir.string();

        if(filePathStr.find(currentPathStr) == 0 || filePathStr.find(logDirStr) == 0) {
            return true;
        }

        if(filename.find("..") == string::npos && filename.find("\\..") == string::npos && filename.find("/..") == string::npos) {
            return true;
        }
        return false;
    } catch (...) {
        return false;
    }
}

// ======== Load Log File =========
void loadLogFile() {
    string filename;
    cout << "\n  " << GREEN << "Enter log file name: " << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, filename);

    // Check for empty input
    if (filename.empty()) {
        cerr << RED << "  ✗ No filename provided.\n" << RESET;
        return;
    }

    // Warn about file extension
    if (filename.find(".log") == string::npos) {
        cout << YELLOW << "  ⚠ Warning: File doesn't have .log extension\n" << RESET;
    }

    if (!isValidLogPath(filename)) {
        cerr << RED << "  ✗ Invalid or unauthorized file path.\n" << RESET;
        return;
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << RED << "  ✗ Could not open file: " << filename << RESET << "\n";
        return;
    }

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    if(fileSize > 10 * 1024 * 1024) {
        double sizeMB = fileSize / (1024.0 * 1024.0);
            cout << YELLOW << "  ⚠ Large file detected (" << fixed << setprecision(1) << sizeMB << "MB). Loading may take time...\n" << RESET;
    }

    logs.clear();
    logs.shrink_to_fit();
    logs.reserve(1000);
    string line;
    smatch match;
    int skipped = 0;

    while(getline(file, line)) {
        LogEntry entry;
        if(parseLogLine(line, entry)) {
            logs.push_back(entry);
        } else if(!line.empty()) {
            skipped++;
        }
    }

    file.close();
    cout << GREEN << "  ✓ Loaded " << logs.size() << " log entries.\n" << RESET;
    if (skipped > 0) {
        cout << YELLOW << "  ⚠ Skipped " << skipped << " malformed lines\n" << RESET;
    }
}

// ======== View Logs =========
void viewLogs(const string& filter) {
    if (logsEmpty()) return;

    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    if (filter.empty()) {
        cout << "  " << BRIGHT_CYAN << "ALL LOGS" << RESET << "\n";
    } else {
        cout << "  " << BRIGHT_CYAN << filter << " LOGS" << RESET << "\n";
    }
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

    int count = 0;
    ostringstream oss;
    for (const auto& entry : logs) {
        if (filter.empty() || entry.level == filter) {
            string levelColor = getLevelColor(entry.level);

            oss << "  " << CYAN << entry.timestamp << RESET 
                << " [" << levelColor << entry.level << RESET << "] " 
                << entry.message << "\n";
            count++;
        }
    }
    
    cout << oss.str();
    cout << "  " << BRIGHT_CYAN << "─────────────────────────────────────────────────────────────" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "Total: " << count << " entries" << RESET << "\n\n";
}

void viewLogsPaginated(const string& filter, int pageSize = 20) {
    if(logsEmpty()) return;

    vector<LogEntry> filtered = getFilteredLogs(filter);
    if(filtered.empty()) {
        cout << RED << "\n  ✗ No logs match the filter.\n" << RESET;
        return;
    }

    size_t totalPages = (filtered.size() + pageSize - 1) / pageSize;
    size_t currentPage = 0;

    while(true) {
        cout << "\033[H\033[2J"; // Clear screen
        cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
        if(filter.empty()) {
            cout << "  " << BRIGHT_CYAN << "ALL LOGS (Page " << (currentPage + 1) << "/" << totalPages << ")" << RESET << "\n";
        } else {
            cout << "  " << BRIGHT_CYAN << filter << " LOGS (Page " << (currentPage + 1) << "/" << totalPages << ")" << RESET << "\n";
        }
        cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

        size_t start = currentPage * pageSize;
        size_t end = std::min(start + pageSize, filtered.size());

        for(size_t i = start; i < end; ++i) {
            const auto& entry = filtered[i];
            string levelColor = getLevelColor(entry.level);
            cout << "  " << CYAN << entry.timestamp << RESET << " [" << levelColor << entry.level << RESET << "] " << entry.message << "\n";
        }

        cout << "\n  " << BRIGHT_CYAN << "─────────────────────────────────────────────────────────────" << RESET << "\n";
        cout << "  " << BRIGHT_CYAN << "Showing " << (start + 1) << "-" << end << " of " << filtered.size() << " entries" << RESET << "\n";
        cout << "  [N]ext  [P]revious  [Q]uit: ";

        char input;
        cin >> input;
        input = std::tolower(input);

        if(input == 'n' && currentPage < totalPages -1) {
            currentPage++;
        } else if(input == 'p' && currentPage < 0) {
            currentPage--;
        } else if(input == 'q') {
            break;
        }
    }
}

// ======== Search Logs =========
void searchLogs() {
    if (logsEmpty()) return;

    string keyword;
    cout << "\n  " << YELLOW << "Enter search keyword: " << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyword);

    // Check for empty input
    if (keyword.empty()) {
        cerr << RED << "  ✗ No search keyword provided.\n" << RESET;
        return;
    }

    // Add to search history
    searchHistory.push_back(keyword);

    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "SEARCH RESULTS FOR: \"" << keyword << "\" (case-insensitive)" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

    int matchCount = 0;
    ostringstream oss;
    for (const auto& entry : logs) {
        if (caseInsensitiveSearch(entry.message, keyword) || 
            caseInsensitiveSearch(entry.level, keyword)) {
            
            string levelColor = getLevelColor(entry.level);

            oss << "  " << CYAN << entry.timestamp << RESET 
                << " [" << levelColor << entry.level << RESET << "] " 
                << entry.message << "\n";
            matchCount++;
        }
    }

    if (matchCount > 0) {
        cout << oss.str();
        cout << "\n  " << BRIGHT_CYAN << "─────────────────────────────────────────────────────────────" << RESET << "\n";
        cout << "  " << BRIGHT_CYAN << "Found: " << matchCount << " matching entries" << RESET << "\n";
    } else {
        cout << "  " << RED << "✗ No matching logs found.\n" << RESET;
    }
    cout << "\n";
}

void searchAndExport() {
    if(logsEmpty()) return;

    string keyword;
    cout << "\n  " << YELLOW << "Enter search Keyword: " << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyword);


    if(keyword.empty()) {
        cerr << RED << "  ✗ No search keyword provided.\n" << RESET;
        return;
    }

    searchHistory.push_back(keyword);

    vector<LogEntry> results;
    for(const auto& entry : logs) {
        if(caseInsensitiveSearch(entry.message, keyword) || caseInsensitiveSearch(entry.level, keyword)) {
            results.push_back(entry);
        }
    }

    if(results.empty()) {
        cout << RED << "\n  ✗ No matching logs found.\n" << RESET;
        return;
    }

    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "SEARCH RESULTS FOR: \"" << keyword << "\"" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

    int displayCount = std::min(10, (int)results.size());
    for(int i = 0; i < displayCount; ++i){
        const auto& entry = results[i];
        string levelColor = getLevelColor(entry.level);
        cout << "  " << CYAN << entry.timestamp << RESET << " [" << levelColor << entry.level << RESET << "] " << entry.message << "\n";

        if(results.size() > 10) {
            cout << "  " << YELLOW << "... and " << (results.size() - 10) << "more matches\n" << RESET;
        }

        cout << "\n  " << GREEN << "✓ Found " << results.size() << " matches.\n" << RESET;
        cout << "  Do you want to export these results? (y/n): ";

        char choice;
        cin >> choice;

        if(choice == 'y' || choice == 'Y') {
            ostringstream desc;
            desc << "Search results for: \"" << keyword << "\"";
            exportLogs(results, desc.str());
            return;
        } else {
            cout << YELLOW << "  Export cancelled.\n" << RESET;
            return;
        }
    }
}

// ======== Show Statistics =========
void showStatistics() {
    if (logsEmpty()) return;

    unordered_map<string, int> countMap;
    int maxCount = 0;

    for(const auto& entry : logs) {
        countMap[entry.level]++;
        maxCount = std::max(maxCount, countMap[entry.level]);
    }

    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "LOG STATISTICS" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";
    cout << "  " << BRIGHT_CYAN << "Total Entries: " << logs.size() << RESET << "\n\n";

    vector<string> levels = {"INFO", "WARN", "ERROR"};

    for(const auto& level : levels) {
        if(countMap.find(level) == countMap.end()) continue;
        
        int count = countMap[level];
        string levelColor = getLevelColor(level);
        double percentage = logs.empty() ? 0.0 : (count * 100.0 / logs.size());

        int barLength = maxCount > 0 ? (count * 50) / maxCount : 0;
        string bar;
        for(int i = 0; i < barLength; ++i) bar += "█";

        cout << "  " << levelColor << std::left << std::setw(8) << level << RESET 
             << " " << levelColor << bar << RESET 
             << " " << count << " (" << fixed << setprecision(1) << percentage << "%)\n";
    }

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

    if (!logs.empty()) {
        cout << "\n  " << BRIGHT_CYAN << "─────────────────────────────────────────────────────────────" << RESET << "\n";
        cout << "  " << CYAN << "First Entry: " << RESET << logs.front().timestamp << "\n";
        cout << "  " << CYAN << "Last Entry:  " << RESET << logs.back().timestamp << "\n";
    }
    
    cout << "\n";
}

// ======== View Search History =========
void viewSearchHistory() {
    if (searchHistory.empty()) {
        cout << YELLOW << "\n  ⚠ No search history available.\n" << RESET;
        return;
    }

    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "SEARCH HISTORY" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

    for (size_t i = 0; i < searchHistory.size(); ++i) {
        cout << "  " << CYAN << (i + 1) << ". " << RESET << searchHistory[i] << "\n";
    }
    cout << "\n";
}

// ======== Export Logs to File =========
void exportLogs(const vector<LogEntry> & entries, const string& description) {
    if(entries.empty()) {
        cout << RED << "\n  ✗ No logs to export.\n" << RESET;
        return;
    }

    string filename;
    cout << "\n " << GREEN << "Enter export filename (without extension)" << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, filename);

    if(filename.empty()) {
        cerr << RED << "  ✗ No filename provided.\n" << RESET;
        return;
    }

    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    ostringstream oss;
    oss << filename << "_" << std::put_time(std::localtime(&time_t_now), "%Y%m%d_%H%M%S") << ".txt";
    string fullFilename = oss.str();

    std::ofstream outFile(fullFilename);
    if (!outFile.is_open()) {
        cerr << RED << "  ✗ Could not create export file.\n" << RESET;
        return;
    }

    outFile << "========================================\n";
    outFile << "LOG ANALYZER EXPORT\n";
    outFile << description << "\n";
    outFile << "Exported: " << std::put_time(std::localtime(&time_t_now), "%Y-%m-%d %H:%M:%S") << "\n";
    outFile << "Total Entries: " << entries.size() << "\n";
    outFile << "========================================\n\n";

    unordered_map<string, int> levelCount;
    for(const auto& entry : entries) {
        levelCount[entry.level]++;
    }

    outFile << "\n--- Statistics ---\n";
    for (const auto& pair : levelCount) {
        double percentage = (pair.second * 100.0) / entries.size();
        outFile << pair.first << ": " << pair.second << " (" << fixed << setprecision(1) << percentage << "%\n";
    }

    if(!entries.empty()) {
        outFile << "\nTime Range:\n";
        outFile << " First " << entries.front().timestamp << '\n';
        outFile << " Last " << entries.back().timestamp << '\n';
    }
    outFile << "========================================\n\n";


    for(const auto& entry : entries) {
        outFile << entry.timestamp << " [" << entry.level << "] " << entry.message << "\n";
    }

    outFile.close();
    cout << GREEN << "  ✓ Exported " << entries.size() << " entries to " << fullFilename << "\n" << RESET;
}

void exportMenu() {
    if(logsEmpty()) return;

    cout << "\n  " << BRIGHT_CYAN << "EXPORT OPTIONS" << RESET << "\n";
    cout << "  1. Export All Logs\n";
    cout << "  2. Export INFO Logs\n";
    cout << "  3. Export WARN Logs\n";
    cout << "  4. Export ERROR Logs\n";
    cout << "  5. Cancel\n";
    cout << "\n  " << BRIGHT_CYAN << "Select option (1-5): " << RESET;

    int choice;
    cin >> choice;

    if(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "\n  ✗ Invalid input.\n" << RESET;
        return;
    }

    switch (choice) {
        case 1: exportLogs(logs, "Filter: ALL"); break;
        case 2: exportLogs(getFilteredLogs("INFO"), "Filter: INFO"); break;
        case 3: exportLogs(getFilteredLogs("WARN"), "Filter: WARN"); break;
        case 4: exportLogs(getFilteredLogs("ERROR"), "Filter: WARN"); break;
        case 5: cout << YELLOW << " Export cancelled.\n" << RESET; break;
        default: cout << RED << "\n  ✗ Invalid option.\n" << RESET; break;
    }
}

bool parseTimestamp(const string& timestamp, std::tm& tm_struct) {
    istringstream ss(timestamp);
    ss >> std::get_time(&tm_struct, "%Y-%m-%d %H:%M:%S");
    return !ss.fail();
}

bool isWithinTimeRange(const string& timestamp, const string& startTime, const string& endTime) {
    std::tm entry_tm = {}, start_tm = {}, end_tm = {};

    if(!parseTimestamp(timestamp, entry_tm) || !parseTimestamp(startTime, start_tm) || !parseTimestamp(endTime, end_tm)) {
        return false;
    }

    time_t entry_time = std::mktime(&entry_tm);
    time_t start = std::mktime(&start_tm);
    time_t end = std::mktime(&end_tm);
    return entry_time >= start && entry_time <= end;
}

void viewLogsByTimeRange() {
    if(logs.empty()) return;

    string startTime, endTime;
    cout << "\n " << YELLOW << "Enter start time (YYYY-MM-DD HH:MM:SS): " << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, startTime);

    cout << " " << YELLOW << "Enter end time (YYYY-MM-DD HH:MM:SS: )" << RESET;
    getline(cin, endTime);

    std::tm test_tm = {};
    if(!parseTimestamp(startTime, test_tm)) {
        cout << RED << "\n  ✗ Invalid start time format. Please use YYYY-MM-DD HH:MM:SS\n" << RESET;
        return;
    }
    test_tm = {};
    if(!parseTimestamp(endTime, test_tm)) {
        cout << RED << "\n  ✗ Invalid end time format. Please use YYYY-MM-DD HH:MM:SS\n" << RESET;
        return;
    }

    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "LOGS FROM " << startTime << " TO " << endTime << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

    int count = 0;
    ostringstream oss;
    for (const auto& entry : logs) {
        if(isWithinTimeRange(entry.timestamp, startTime, endTime)) {
            string levelColor = getLevelColor(entry.level);
            oss << "  " << CYAN << entry.timestamp << RESET << " [" << levelColor << entry.level << RESET << "] " << entry.message << "\n";
            count++;
        }
    }

    if (count > 0) {
        cout << oss.str();
        cout << "  " << BRIGHT_CYAN << "─────────────────────────────────────────────────────────────" << RESET << "\n";
        cout << "  " << BRIGHT_CYAN << "Total: " << count << " entries" << RESET << "\n\n";
    } else {
        cout << "  " << RED << "✗ No logs found in specified time range.\n" << RESET;
    }
}

bool parseLogLine(const string& line, LogEntry& entry) {
    smatch match;

    if(regex_match(line, match, LOG_REGEX)) {
        entry.timestamp = match[1];
        entry.level = match[2];
        entry.message = match[3];
        return true;
    }

    if(regex_match(line, match, LOG_REGEX_ALT1)) {
        entry.timestamp = match[1];
        entry.level = match[2];
        entry.message = match[3];
        return true;
    }

    if(regex_match(line, match, LOG_REGEX_ALT2)) {
        entry.timestamp = match[1];
        entry.level = match[2];
        entry.message = match[3];
        return true;
    }
    
    return false;
}
// ======== Main Function =========
int main() {
    setupConsole();
    displayWelcomeBanner();

    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "\n  ✗ Invalid input. Please enter a number.\n" << RESET;
            continue;
        }

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
                cout << RED << "\n  ✗ Invalid option. Please select 1-9.\n" << RESET; 
                break;
        }
    }

    return 0;
}