#include "windows.h"

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
#include <unordered_set>
#include <map>
#include <filesystem>
#include <atomic>

using namespace std;

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

// Struct for log entries
struct LogEntry {
    string timestamp;
    string level;
    string message;
};

// Global variables
vector<LogEntry> logs;
vector<string> searchHistory;

unordered_map<string, vector<int>> levelIndex;
unordered_map<string, vector<int>> keywordIndex;

atomic<bool> tailing(false);

int PAGE_SIZE = 10;

// Function declarations
void setupConsole();
string getGradientColor(int lineIndex, int colIndex, int frame);
void displayWelcomeBanner();
void displayMenu();
void loadLogFile();
void viewLogs(const string& filter = "");
void searchLogs();
void showStatistics();
bool logsEmpty();

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
    const int frames = 40;
    const int delay_ms = 80;
    
    for (int frame = 0; frame < frames; ++frame) {
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
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
    
    // Final frame
    this_thread::sleep_for(chrono::milliseconds(500));
}

// ======== Menu Display =========
void displayMenu() {
    cout << "\n";
    cout << "  " << CYAN << "╔═════════════════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "                    " << BRIGHT_CYAN << "LOG ANALYZER MENU" << RESET << "                            " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "╠═════════════════════════════════════════════════════════════════╣" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << GREEN << "1." << RESET << " Load Log File            " << BLUE << "5." << RESET << " View ERROR Logs                 " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << GREEN << "2." << RESET << " View All Logs            " << YELLOW << "6." << RESET << " Search Logs                     " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << BLUE << "3." << RESET << " View INFO Logs           " << MAGENTA << "7." << RESET << " Show Statistics                 " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << YELLOW << "4." << RESET << " View WARN Logs           " << BRIGHT_RED << "8." << RESET << " Exit                            " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "                                                                 " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "╚═════════════════════════════════════════════════════════════════╝" << RESET << "\n";
    cout << "\n  " << BRIGHT_CYAN << "Select an option (1-8): " << RESET;
}

// ======== Helper =========
bool logsEmpty() {
    if (logs.empty()) {
        cout << RED << "\n  ⚠ No logs loaded. Please load a log file first.\n" << RESET;
        return true;
    }
    return false;
}

tm parseTimestamp(const string& ts) {
    tm t{};
    istringstream ss(ts);
    ss >> get_time(&t, "%Y-%m-%d %H:%M:%S");
    return t;
}

void buildIndexes() {
    levelIndex.clear();
    keywordIndex.clear();

    for(int i = 0; i < logs.size(); ++i) {
        levelIndex[logs[i].level].push_back(i);

        istringstream iss(logs[i].message);
        string word;
        while (iss >> word){
            keywordIndex[word].push_back(i);
        }
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

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << RED << "  ✗ Could not open file: " << filename << RESET << endl;
        return;
    }

    logs.clear();
    string line;
    regex logRegex(R"((\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}) \[(\w+)\] (.*))");
    smatch match;

    while (getline(file, line)) {
        if (regex_match(line, match, logRegex)) {
            LogEntry entry;
            entry.timestamp = match[1];
            entry.level = match[2];
            entry.message = match[3];
            logs.push_back(entry);
        }
    }

    file.close();
    cout << GREEN << "  ✓ Loaded " << logs.size() << " log entries.\n" << RESET;
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
    for (const auto& entry : logs) {
        if (filter.empty() || entry.level == filter) {
            string levelColor;
            if (entry.level == "INFO") levelColor = GREEN;
            else if (entry.level == "WARN") levelColor = YELLOW;
            else if (entry.level == "ERROR") levelColor = RED;
            else levelColor = RESET;

            cout << "  " << CYAN << entry.timestamp << RESET 
                 << " [" << levelColor << entry.level << RESET << "] " 
                 << entry.message << endl;
            count++;
        }
    }
    
    cout << "\n  " << BRIGHT_CYAN << "─────────────────────────────────────────────────────────────" << RESET << "\n";
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

    cout << "\n  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "SEARCH RESULTS FOR: \"" << keyword << "\"" << RESET << "\n";
    cout << "  " << BRIGHT_CYAN << "════════════════════════════════════════════════════════════" << RESET << "\n\n";

    bool found = false;
    for (const auto& entry : logs) {
        if (entry.message.find(keyword) != string::npos || 
            entry.level.find(keyword) != string::npos) {
            
            string levelColor;
            if (entry.level == "INFO") levelColor = GREEN;
            else if (entry.level == "WARN") levelColor = YELLOW;
            else if (entry.level == "ERROR") levelColor = RED;
            else levelColor = RESET;

            cout << "  " << CYAN << entry.timestamp << RESET 
                 << " [" << levelColor << entry.level << RESET << "] " 
                 << entry.message << endl;
            found = true;
        }
    }

    if (!found) {
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
        string levelColor;
        if (pair.first == "INFO") levelColor = GREEN;
        else if (pair.first == "WARN") levelColor = YELLOW;
        else if (pair.first == "ERROR") levelColor = RED;
        else levelColor = RESET;

        cout << "  " << levelColor << pair.first << ": " << pair.second 
             << " (" << (pair.second * 100.0 / logs.size()) << "%)" << RESET << endl;
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
                cout << "\n  " << GREEN << "✓ Exiting Log Analyzer. Goodbye!\n\n" << RESET; 
                return 0;
            default: 
                cout << RED << "\n  ✗ Invalid option. Please select 1-8.\n" << RESET; 
                break;
        }
    }

    return 0;
}