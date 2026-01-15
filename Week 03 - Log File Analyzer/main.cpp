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
    cout << "  " << CYAN << "╔═════════════════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "                    " << BRIGHT_CYAN << "LOG ANALYZER MENU" << RESET << "                            " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "╠═════════════════════════════════════════════════════════════════╣" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << GREEN << "1." << RESET << " Load Log File            " << BLUE << "6." << RESET << " Search Logs                     " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << GREEN << "2." << RESET << " View All Logs            " << MAGENTA << "7." << RESET << " Show Statistics                 " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << BLUE << "3." << RESET << " View INFO Logs           " << BRIGHT_MAGENTA << "8." << RESET << " View Search History             " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << YELLOW << "4." << RESET << " View WARN Logs           " << BRIGHT_RED << "9." << RESET << " Exit                            " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << RED << "5." << RESET << " View ERROR Logs                                              " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "                                                                 " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "╚═════════════════════════════════════════════════════════════════╝" << RESET << "\n";
    cout << "\n  " << BRIGHT_CYAN << "Select an option (1-9): " << RESET;
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

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << RED << "  ✗ Could not open file: " << filename << RESET << "\n";
        return;
    }

    logs.clear();
    logs.shrink_to_fit();
    string line;
    smatch match;
    int skipped = 0;

    while (getline(file, line)) {
        if (regex_match(line, match, LOG_REGEX)) {
            LogEntry entry;
            entry.timestamp = match[1];
            entry.level = match[2];
            entry.message = match[3];
            logs.push_back(entry);
        } else if (!line.empty()) {
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

// ======== Show Statistics =========
void showStatistics() {
    if (logsEmpty()) return;

    unordered_map<string, int> countMap;
    for (const auto& entry : logs) {
        countMap[entry.level]++;
    }

    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "LOG STATISTICS" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";
    cout << "  " << BRIGHT_CYAN << "Total Entries: " << logs.size() << RESET << "\n\n";

    for (const auto& pair : countMap) {
        string levelColor = getLevelColor(pair.first);
        double percentage = logs.empty() ? 0.0 : (pair.second * 100.0 / logs.size());

        cout << "  " << levelColor << pair.first << ": " << pair.second 
             << " (" << fixed << setprecision(2) << percentage << "%)" << RESET << "\n";
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
                cout << "\n  " << GREEN << "✓ Exiting Log Analyzer. Goodbye!\n\n" << RESET; 
                return 0;
            default: 
                cout << RED << "\n  ✗ Invalid option. Please select 1-9.\n" << RESET; 
                break;
        }
    }

    return 0;
}