#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;

struct LogEntry {
    string timestamp;
    string level;
    string message;
};

vector<LogEntry> logs;

void loadLogFile();
void viewLogs(const string& filter = "");
void searchLogs();
void showStatistics();
bool logsEmpty();

// ======== Helper: Check if logs are empty =========
bool logsEmpty() {
    if (logs.empty()) {
        cout << "No logs loaded. Please load a log file first.\n";
        return true;
    }
    return false;
}

void loadLogFile() {
    string filename;
    cout << "Enter log file name: ";
    cin >> filename;
    cin.ignore(numeric_limits<streamsize>::max()), '\n';

    ifstream file(filename);
    if(!file.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return;
    }

    logs.clear();
    string line;
    regex logRegex(R"((\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}) \[(\w+)\] (.*))");
    smatch match;

    while(getline(file, line)) {
        if(regex_match(line, match, logRegex)) {
            LogEntry entry;
            entry.timestamp = match[1];
            entry.level = match[2];
            entry.message = match[3];
            logs.push_back(entry);
        }
    }

    file.close();
    cout << "Loaded " << logs.size() << " log entries.\n";
}

void viewLogs(const string& filter) {
    if(logsEmpty()) return;

    for(const auto& entry : logs) {
        if(filter.empty() || entry.level == filter) {
            cout << entry.timestamp << " [" << entry.level << "] " << entry.message << endl;
        }
    }
}

void searchLogs() {
    if(logsEmpty()) return;

    string keyword;
    cout << "Enter search keyword: ";
    cin.ignore();
    getline(cin, keyword);

    bool found = false;
    for(const auto& entry : logs) {
        if(entry.message.find(keyword) != string::npos || entry.level.find(keyword) != string::npos) {
            cout << entry.timestamp << " [" << entry.level << "] " << entry.message << endl;
            found = true;
        }
    }

    if(!found) cout << "No matching logs found.\n";
}

