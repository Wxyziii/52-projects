#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <stack>
#include <algorithm>
#include <thread>
#include <chrono>
#include <windows.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

// Color definitions
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

// ═══════════════════════════════════════════════════════════════════
// UI DISPLAY FUNCTIONS
// ═══════════════════════════════════════════════════════════════════

void setupConsole() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

string getGradientColor(int lineIndex, int colIndex, int frame) {
    const string colors[] = {
        "\033[38;5;131m", // Muted red
        "\033[38;5;137m", // Terracotta
        "\033[38;5;173m", // Soft orange
        "\033[38;5;179m", // Muted gold
        "\033[38;5;185m", // Soft yellow
        "\033[38;5;186m", // Pale yellow
        "\033[38;5;150m", // Yellow-sage
        "\033[38;5;114m", // Soft green
        "\033[38;5;108m", // Sage
        "\033[38;5;72m",  // Teal-green
        "\033[38;5;73m",  // Muted cyan
        "\033[38;5;80m",  // Soft teal
        "\033[38;5;74m",  // Soft blue
        "\033[38;5;67m",  // Slate blue
        "\033[38;5;61m",  // Deeper slate
        "\033[38;5;97m",  // Soft purple
        "\033[38;5;103m", // Lavender
        "\033[38;5;139m", // Mauve
        "\033[38;5;132m", // Dusty magenta
        "\033[38;5;168m"  // Soft rose
    };
    // 45-degree diagonal: both lineIndex and colIndex contribute equally
    int colorIndex = (lineIndex + colIndex + frame) % 20;
    return colors[colorIndex];
}

void displayWelcomeBanner() {
    const int frames = 40;
    const int delay_ms = 80;
    
    for (int frame = 0; frame < frames; ++frame) {
        cout << "\033[H\033[2J";
        cout << "\n";
        cout << "  " << getGradientColor(0, 0, frame) << "╔════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << "\n";
        cout << "  " << getGradientColor(0, 0, frame) << "║" << RESET << "                                                                                                " << getGradientColor(0, 95, frame) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(1, 0, frame) << "║" << RESET << "              " << getGradientColor(1, 4, frame) << "███▄▄▄▄    ▄██████▄      ███        ▄████████  ▄████████  ▄█        ▄█ " << RESET << " " << getGradientColor(1, 95, frame) << "          ║" << RESET << "\n";
        cout << "  " << getGradientColor(2, 0, frame) << "║" << RESET << "              " << getGradientColor(2, 4, frame) << "███▀▀▀██▄ ███    ███ ▀█████████▄   ███    ███ ███    ███ ███       ███" << RESET << " " << getGradientColor(2, 95, frame) << "           ║" << RESET << "\n";
        cout << "  " << getGradientColor(3, 0, frame) << "║" << RESET << "              " << getGradientColor(3, 7, frame) << "███   ███ ███    ███    ▀███▀▀██   ███    █▀  ███    █▀  ███       ███▌" << RESET << " " << getGradientColor(3, 95, frame) << "          ║" << RESET << "\n";
        cout << "  " << getGradientColor(5, 0, frame) << "║" << RESET << "              " << getGradientColor(5, 7, frame) << "███   ███ ███    ███     ███   ▀  ▄███▄▄▄     ███        ███       ███▌" << RESET << " " << getGradientColor(5, 95, frame) << "          ║" << RESET << "\n";
        cout << "  " << getGradientColor(6, 0, frame) << "║" << RESET << "              " << getGradientColor(6, 7, frame) << "███   ███ ███    ███     ███     ▀▀███▀▀▀     ███        ███       ███▌" << RESET << " " << getGradientColor(6, 95, frame) << "          ║" << RESET << "\n";
        cout << "  " << getGradientColor(7, 0, frame) << "║" << RESET << "              " << getGradientColor(7, 7, frame) << "███   ███ ███    ███     ███       ███    █▄  ███    █▄  ███       ███ " << RESET << " " << getGradientColor(7, 95, frame) << "          ║" << RESET << "\n";
        cout << "  " << getGradientColor(7, 0, frame) << "║" << RESET << "              " << getGradientColor(7, 7, frame) << "███   ███ ███    ███     ███       ███    ███ ███    ███ ███▌    ▄ ███ " << RESET << " " << getGradientColor(7, 95, frame) << "          ║" << RESET << "\n";
        cout << "  " << getGradientColor(7, 0, frame) << "║" << RESET << "              " << getGradientColor(7, 7, frame) << " ▀█   █▀   ▀██████▀     ▄████▀     ██████████ ████████▀  █████▄▄██ █▀ " << RESET << " " << getGradientColor(7, 95, frame) << "           ║" << RESET << "\n";
        cout << "  " << getGradientColor(7, 0, frame) << "║" << RESET << "              " << getGradientColor(7, 7, frame) << "                                                          ▀              " << RESET << " " << getGradientColor(7, 95, frame) << "        ║" << RESET << "\n";
        cout << "  " << getGradientColor(8, 0, frame) << "║" << RESET << "                                                                                                " << getGradientColor(8, 95, frame) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(9, 0, frame) << "║" << RESET << "                                          " << getGradientColor(9, 33, frame) << "Note Taking App" << RESET << "                                " << getGradientColor(9, 95, frame) << "       ║" << RESET << "\n";
        cout << "  " << getGradientColor(10, 0, frame) << "║" << RESET << "                                 " << getGradientColor(10, 27, frame) << "Priority Tracking • Search & Sort" << RESET << "                        " << getGradientColor(10, 95, frame) << "      ║" << RESET << "\n";
        cout << "  " << getGradientColor(11, 0, frame) << "║" << RESET << "                                                                                                " << getGradientColor(11, 95, frame) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(12, 0, frame) << "╚════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << "\n";
        
        cout << flush;
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
    
    cout << "\033[H\033[2J";
    cout << "\n";
        cout << "  " << getGradientColor(0, 0, frames-1) << "╔════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << "\n";
        cout << "  " << getGradientColor(0, 0, frames-1) << "║" << RESET << "                                                                                                " << getGradientColor(0, 95, frames-1) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(1, 0, frames-1) << "║" << RESET << "              " << getGradientColor(1, 4, frames-1) << "███▄▄▄▄    ▄██████▄      ███        ▄████████  ▄████████  ▄█        ▄█ " << RESET << " " << getGradientColor(1, 95, frames-1) << "          ║" << RESET << "\n";
        cout << "  " << getGradientColor(2, 0, frames-1) << "║" << RESET << "              " << getGradientColor(2, 4, frames-1) << "███▀▀▀██▄ ███    ███ ▀█████████▄   ███    ███ ███    ███ ███       ███" << RESET << " " << getGradientColor(2, 95, frames-1) << "           ║" << RESET << "\n";
        cout << "  " << getGradientColor(3, 0, frames-1) << "║" << RESET << "              " << getGradientColor(3, 7, frames-1) << "███   ███ ███    ███    ▀███▀▀██   ███    █▀  ███    █▀  ███       ███▌" << RESET << " " << getGradientColor(3, 95, frames-1) << "          ║" << RESET << "\n";
        cout << "  " << getGradientColor(5, 0, frames-1) << "║" << RESET << "              " << getGradientColor(5, 7, frames-1) << "███   ███ ███    ███     ███   ▀  ▄███▄▄▄     ███        ███       ███▌" << RESET << " " << getGradientColor(5, 95, frames-1) << "          ║" << RESET << "\n";
        cout << "  " << getGradientColor(6, 0, frames-1) << "║" << RESET << "              " << getGradientColor(6, 7, frames-1) << "███   ███ ███    ███     ███     ▀▀███▀▀▀     ███        ███       ███▌" << RESET << " " << getGradientColor(6, 95, frames-1) << "          ║" << RESET << "\n";
        cout << "  " << getGradientColor(7, 0, frames-1) << "║" << RESET << "              " << getGradientColor(7, 7, frames-1) << "███   ███ ███    ███     ███       ███    █▄  ███    █▄  ███       ███ " << RESET << " " << getGradientColor(7, 95, frames-1) << "          ║" << RESET << "\n";
        cout << "  " << getGradientColor(7, 0, frames-1) << "║" << RESET << "              " << getGradientColor(7, 7, frames-1) << "███   ███ ███    ███     ███       ███    ███ ███    ███ ███▌    ▄ ███ " << RESET << " " << getGradientColor(7, 95, frames-1) << "          ║" << RESET << "\n";
        cout << "  " << getGradientColor(7, 0, frames-1) << "║" << RESET << "              " << getGradientColor(7, 7, frames-1) << " ▀█   █▀   ▀██████▀     ▄████▀     ██████████ ████████▀  █████▄▄██ █▀ " << RESET << " " << getGradientColor(7, 95, frames-1) << "           ║" << RESET << "\n";
        cout << "  " << getGradientColor(7, 0, frames-1) << "║" << RESET << "              " << getGradientColor(7, 7, frames-1) << "                                                          ▀              " << RESET << " " << getGradientColor(7, 95, frames-1) << "        ║" << RESET << "\n";
        cout << "  " << getGradientColor(8, 0, frames-1) << "║" << RESET << "                                                                                                " << getGradientColor(8, 95, frames-1) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(9, 0, frames-1) << "║" << RESET << "                                          " << getGradientColor(9, 33, frames-1) << "Note Taking App" << RESET << "                                " << getGradientColor(9, 95, frames-1) << "       ║" << RESET << "\n";
        cout << "  " << getGradientColor(10, 0, frames-1) << "║" << RESET << "                                 " << getGradientColor(10, 27, frames-1) << "Priority Tracking • Search & Sort" << RESET << "                        " << getGradientColor(10, 95, frames-1) << "      ║" << RESET << "\n";
        cout << "  " << getGradientColor(11, 0, frames-1) << "║" << RESET << "                                                                                                " << getGradientColor(11, 95, frames-1) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(12, 0, frames-1) << "╚════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << "\n";
}

// ═══════════════════════════════════════════════════════════════════
// DATA STRUCTURES
// ═══════════════════════════════════════════════════════════════════

struct Note {
    int id;
    string title;
    string content;
    string createdAt;
    string modifiedAt;
};

// ═══════════════════════════════════════════════════════════════════
// HELPER FUNCTIONS
// ═══════════════════════════════════════════

bool notesEmpty(const vector<Note>& notes) {
    if (notes.empty()) {
        cout << "  " << YELLOW << "[!]" << RESET << " No notes available.\n";
        return true;
    }
    return false;
}

void displayMenu() {
    cout << "\n";
    cout << "  " << CYAN << "╔═════════════════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "                        " << BRIGHT_CYAN << "MAIN MENU" << RESET << "                              " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "╠═════════════════════════════════════════════════════════════════╣" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << GREEN << "1." << RESET << " [" << GREEN << "+" << RESET << "] Create Note      " << GREEN << "5." << RESET << " [" << GREEN << "?" << RESET << "] Search Notes           " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << BLUE << "2." << RESET << " [" << BLUE << "=" << RESET << "] View Note        " << BLUE << "6." << RESET << " [" << BLUE << "*" << RESET << "] Sort Notes             " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << YELLOW << "3." << RESET << " [" << YELLOW << "~" << RESET << "] Edit Note        " << YELLOW << "7." << RESET << " [" << YELLOW << "S" << RESET << "] Save Notes             " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << RED << "4." << RESET << " [" << RED << "X" << RESET << "] Delete Note      " << MAGENTA << "8." << RESET << " [" << MAGENTA << "L" << RESET << "] Load Notes             " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "                                                                 " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "║" << RESET << "  " << BRIGHT_RED << "0." << RESET << " [" << BRIGHT_RED << "!" << RESET << "] Exit                                               " << CYAN << "║" << RESET << "\n";
    cout << "  " << CYAN << "╚═════════════════════════════════════════════════════════════════╝" << RESET << "\n";
}

int readInt(const string& prompt) {
    int v;
    while (true) {
        cout << "  " << prompt;
        cin >> v;
        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  " << RED << "[X]" << RESET << " Invalid number. Please try again.\n";
    }
}

string readLine(const string& prompt) {
    cout << "  " << prompt;
    string s;
    getline(cin, s);
    return s;
}

// ═══════════════════════════════════════════════════════════════════
// NOTE OPERATIONS
// ═══════════════════════════════════════════════════════════════════

string currentTime() {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%d-%m %H:%M", localtime(&now));
    return buf;
}

void createNote(vector<Note>& notes) {
    Note n;
    string line;
    n.id = notes.empty() ? 1 : notes.back().id + 1;
    
    cout << "  " << CYAN << "▶" << RESET << " Enter title: ";
    getline(cin, n.title);
    
    cout << "  " << CYAN << "▶" << RESET << " Enter content (type '.' on a new line to finish):\n";
    n.content.clear();

    while (true) {
        cout << "  ";
        getline(cin, line);
        if (line == ".") break;
        n.content += line + '\n';
    }

    n.createdAt = currentTime();
    n.modifiedAt = n.createdAt;
    notes.push_back(n);

    cout << "  " << GREEN << "✓" << RESET << " Note created successfully!\n";
}

void editNote(vector<Note>& notes) {
    if (notesEmpty(notes)) return;

    int id;
    cout << "  " << CYAN << "▶" << RESET << " Enter note ID to edit: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto& n : notes) {
        if (n.id == id) {
            string input;

            cout << "  Current title: " << YELLOW << n.title << RESET << "\n";
            cout << "  " << CYAN << "▶" << RESET << " New title (empty to keep current): ";
            getline(cin, input);
            if (!input.empty()) n.title = input;

            cout << "  " << CYAN << "▶" << RESET << " New content (type '.' on a new line to finish, leave empty to keep current):\n";
            string newContent;
            string line;
            while (true) {
                cout << "  ";
                getline(cin, line);
                if (line == ".") break;
                newContent += line + '\n';
            }
            if (!newContent.empty()) n.content = newContent;

            n.modifiedAt = currentTime();
            cout << "  " << GREEN << "✓" << RESET << " Note updated successfully!\n";
            return;
        }
    }
    cout << "  " << RED << "✗" << RESET << " Note not found.\n";
}

void deleteNote(vector<Note>& notes) {
    if (notesEmpty(notes)) return;

    int id;
    cout << "  " << CYAN << "▶" << RESET << " Enter note ID to delete: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max());

    auto it = remove_if(notes.begin(), notes.end(), [&](const Note& n) { return n.id == id; });

    if (it != notes.end()) {
        notes.erase(it, notes.end());
        cout << "  " << GREEN << "✓" << RESET << " Note deleted successfully!\n";
    } else {
        cout << "  " << RED << "✗" << RESET << " Note not found.\n";
    }
}

void viewNotes(vector<Note>& notes) {
    if (notesEmpty(notes)) return;

    cout << "\n  " << CYAN << "═══════════════════════════════════════════════════════════" << RESET << "\n";
    for (const auto& n : notes) {
        cout << "  " << BLUE << "ID:" << RESET << " " << n.id << "\n";
        cout << "  " << GREEN << "Title:" << RESET << " " << n.title << "\n";
        cout << "  " << YELLOW << "Created:" << RESET << " " << n.createdAt << "\n";
        cout << "  " << YELLOW << "Modified:" << RESET << " " << n.modifiedAt << "\n";
        cout << "  " << MAGENTA << "Content:" << RESET << "\n  " << n.content << "\n";
        cout << "  " << CYAN << "───────────────────────────────────────────────────────────" << RESET << "\n";
    }
}

void viewAllNotes(vector<Note>& notes) {
    if (notesEmpty(notes)) return;
    
    cout << "\n  " << CYAN << "All Notes:" << RESET << "\n";
    for (const auto& n : notes) {
        cout << "  " << BLUE << n.id << "." << RESET << " " << n.title << '\n';
    }
}

void searchNotes(vector<Note>& notes) {
    if (notesEmpty(notes)) return;

    string keyword;
    cout << "  " << CYAN << "▶" << RESET << " Enter search keyword: ";
    getline(cin, keyword);

    bool found = false;
    cout << "\n  " << CYAN << "Search Results:" << RESET << "\n";
    cout << "  " << CYAN << "═══════════════════════════════════════════════════════════" << RESET << "\n";
    
    for (const auto& n : notes) {
        if (n.title.find(keyword) != string::npos || n.content.find(keyword) != string::npos) {
            found = true;
            cout << "  " << BLUE << "ID:" << RESET << " " << n.id << "\n";
            cout << "  " << GREEN << "Title:" << RESET << " " << n.title << "\n";
            cout << "  " << MAGENTA << "Content:" << RESET << "\n  " << n.content << "\n";
            cout << "  " << CYAN << "───────────────────────────────────────────────────────────" << RESET << "\n";
        }
    }
    
    if (!found) {
        cout << "  " << YELLOW << "[!]" << RESET << " No notes found matching '" << keyword << "'.\n";
    }
}

void sortNotesByTitle(vector<Note>& notes) {
    if (notesEmpty(notes)) return;

    sort(notes.begin(), notes.end(), [](const Note& a, const Note& b) { return a.title < b.title; });

    cout << "  " << GREEN << "✓" << RESET << " Notes sorted by title successfully!\n";
}

void saveNotes(vector<Note>& notes) {
    json j;
    for (const auto& n : notes) {
        j.push_back({
            {"id", n.id},
            {"title", n.title},
            {"content", n.content},
            {"createdAt", n.createdAt},
            {"modifiedAt", n.modifiedAt}
        });
    }

    ofstream file("notes.json");
    if (file.is_open()) {
        file << j.dump(4);
        cout << "  " << GREEN << "✓" << RESET << " Notes saved successfully!\n";
    } else {
        cout << "  " << RED << "✗" << RESET << " Error saving notes.\n";
    }
}

void loadNotes(vector<Note>& notes) {
    ifstream file("notes.json");
    if (!file) {
        cout << "  " << YELLOW << "[!]" << RESET << " No saved notes file found.\n";
        return;
    }

    json j;
    file >> j;

    notes.clear();
    for (const auto& item : j) {
        notes.push_back({
            item["id"],
            item["title"],
            item["content"],
            item["createdAt"],
            item["modifiedAt"]
        });
    }

    cout << "  " << GREEN << "✓" << RESET << " Notes loaded successfully! (" << notes.size() << " note(s))\n";
}
// ═══════════════════════════════════════════════════════════════════
// MAIN PROGRAM
// ═══════════════════════════════════════════════════════════════════

int main() {
    setupConsole();
    vector<Note> notes;

    displayWelcomeBanner();
    
    while (true) {
        displayMenu();
        int choice = readInt("Choice: ");
        
        switch (choice) {
            case 1:
                createNote(notes);
                break;
            case 2:
                viewNotes(notes);
                break;
            case 3:
                editNote(notes);
                break;
            case 4:
                deleteNote(notes);
                break;
            case 5:
                searchNotes(notes);
                break;
            case 6:
                sortNotesByTitle(notes);
                break;
            case 7:
                saveNotes(notes);
                break;
            case 8:
                loadNotes(notes);
                break;
            case 0:
                cout << "\n  " << CYAN << "Thank you for using NoteCLI! Goodbye!" << RESET << "\n\n";
                return 0;
            default:
                cout << "  " << RED << "✗" << RESET << " Invalid option. Please choose 0-8.\n";
                break;
        }
    }

    return 0;
}