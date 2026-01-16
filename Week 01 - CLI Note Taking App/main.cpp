/*
 * ═══════════════════════════════════════════════════════════════════════════
 * CLI NOTE TAKING APPLICATION
 * ═══════════════════════════════════════════════════════════════════════════
 * 
 * A feature-rich command-line note-taking application with:
 * - Create, view, edit, and delete notes
 * - Search functionality (case-insensitive)
 * - Tag-based organization
 * - Undo/Redo operations with full history
 * - JSON-based persistence
 * - Color-coded interface with animated banner
 * - Export functionality
 * 
 * Author: Marcel Bialk
 * Date: January 2026
 * C++ Standard: C++17
 * Dependencies: nlohmann/json library (json.hpp)
 * 
 * ═══════════════════════════════════════════════════════════════════════════
 */

// ═══════════════════════════════════════════════════════════════════════════
// INCLUDES
// ═══════════════════════════════════════════════════════════════════════════

#include <iostream>         // Input/output streams
#include <string>           // String operations
#include <vector>           // Dynamic arrays for note storage
#include <fstream>          // File I/O for JSON persistence
#include <limits>           // Numeric limits for input validation
#include <stack>            // Stack for undo/redo functionality
#include <algorithm>        // STL algorithms (find, transform)
#include <thread>           // Sleep for banner animation
#include <chrono>           // Time operations for animation timing
#include <windows.h>        // Windows console API for ANSI colors
#include "json.hpp"         // nlohmann/json library for JSON handling

// ═══════════════════════════════════════════════════════════════════════════
// NAMESPACE DECLARATIONS
// ═══════════════════════════════════════════════════════════════════════════

using namespace std;
using json = nlohmann::json;

// ═══════════════════════════════════════════════════════════════════════════
// ANSI COLOR CODE DEFINITIONS
// ═══════════════════════════════════════════════════════════════════════════

#define RESET          "\033[0m"           // Reset all attributes
#define RED            "\033[38;5;131m"    // Muted red for errors
#define GREEN          "\033[38;5;108m"    // Muted green for success
#define YELLOW         "\033[38;5;179m"    // Muted yellow for warnings
#define BLUE           "\033[38;5;67m"     // Muted blue for info
#define MAGENTA        "\033[38;5;132m"    // Muted magenta
#define CYAN           "\033[38;5;73m"     // Muted cyan for headers
#define BRIGHT_RED     "\033[38;5;167m"    // Bright red
#define BRIGHT_GREEN   "\033[38;5;114m"    // Bright green
#define BRIGHT_YELLOW  "\033[38;5;185m"    // Bright yellow
#define BRIGHT_BLUE    "\033[38;5;74m"     // Bright blue
#define BRIGHT_MAGENTA "\033[38;5;139m"    // Bright magenta
#define BRIGHT_CYAN    "\033[38;5;80m"     // Bright cyan for emphasis

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: CONSOLE SETUP
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Configure Windows console for UTF-8 and ANSI escape sequence support
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
 * Creates smooth color transitions using 20 predefined colors
 * 
 * @param lineIndex  Vertical position in banner
 * @param colIndex   Horizontal position in banner
 * @param frame      Current animation frame number
 * @return           ANSI color code string
 */
string getGradientColor(int lineIndex, int colIndex, int frame) {
    // 20-color palette for smooth gradient transitions
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
    
    // Calculate diagonal gradient (45-degree angle)
    // Both line and column positions contribute equally
    int colorIndex = (lineIndex + colIndex + frame) % 20;
    return colors[colorIndex];
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: ANIMATED WELCOME BANNER
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Display animated welcome banner with gradient color cycling
 * Shows "NOTECLI" ASCII art with smooth color transitions
 */
void displayWelcomeBanner() {
    const int frames = 40;      // Total animation frames
    const int delay_ms = 80;    // Milliseconds per frame
    
    // Animation loop
    for (int frame = 0; frame < frames; ++frame) {
        cout << "\033[H\033[2J";  // Clear screen
        cout << "\n";
        
        // Draw banner with animated gradient colors
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
        
        cout << flush;  // Force immediate display
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
    
    // Display final static frame
    cout << "\033[H\033[2J";  // Clear screen one last time
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

// ═══════════════════════════════════════════════════════════════════════════
// DATA STRUCTURES
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Represents a single note entry
 */
struct Note {
    int id;                // Unique identifier
    string title;          // Note title/summary
    string content;        // Main note content
    string createdAt;      // Creation timestamp
    string modifiedAt;     // Last modification timestamp
};

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: UTILITY FUNCTIONS
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Check if notes vector is empty and display message
 * 
 * @param notes Vector of notes to check
 * @return      true if empty, false otherwise
 */
bool notesEmpty(const vector<Note>& notes) {
    if (notes.empty()) {
        cout << "  " << YELLOW << "[!]" << RESET << " No notes available.\n";
        return true;
    }
    return false;
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: MENU DISPLAY
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Display main application menu with color-coded options
 * Shows 8 main operations organized in 2 columns
 */
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

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: INPUT HELPERS
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Read and validate integer input from user
 * Continues prompting until valid integer is entered
 * 
 * @param prompt Message to display to user
 * @return       Valid integer from user
 */
int readInt(const string& prompt) {
    int v;
    while (true) {
        cout << "  " << prompt;
        cin >> v;
        
        // Check if input is valid integer
        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        
        // Clear error state and try again
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  " << RED << "[X]" << RESET << " Invalid number. Please try again.\n";
    }
}

/**
 * Read a line of text from user
 * 
 * @param prompt Message to display to user
 * @return       String entered by user
 */
string readLine(const string& prompt) {
    cout << "  " << prompt;
    string s;
    getline(cin, s);
    return s;
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: NOTE OPERATIONS
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Get current system time formatted as string
 * 
 * @return Formatted timestamp string (YYYY-DD-MM HH:MM)
 */
string currentTime() {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%d-%m %H:%M", localtime(&now));
    return buf;
}

/**
 * Create a new note interactively
 * Prompts for title and multi-line content (end with '.')
 * Automatically assigns ID and timestamps
 * 
 * @param notes Vector to add new note to
 */
void createNote(vector<Note>& notes) {
    Note n;
    string line;
    
    // Generate new ID (1 or last ID + 1)
    n.id = notes.empty() ? 1 : notes.back().id + 1;
    
    // Get note title
    cout << "  " << CYAN << "▶" << RESET << " Enter title: ";
    getline(cin, n.title);
    
    // Get multi-line content
    cout << "  " << CYAN << "▶" << RESET << " Enter content (type '.' on a new line to finish):\n";
    n.content.clear();

    while (true) {
        cout << "  ";
        getline(cin, line);
        if (line == ".") break;  // End marker
        n.content += line + '\n';
    }

    // Set timestamps
    n.createdAt = currentTime();
    n.modifiedAt = n.createdAt;
    
    notes.push_back(n);

    cout << "  " << GREEN << "✓" << RESET << " Note created successfully!\n";
}

/**
 * Edit an existing note by ID
 * Allows updating title and/or content
 * Empty input keeps current value
 * Updates modification timestamp
 * 
 * @param notes Vector of notes to search and modify
 */
void editNote(vector<Note>& notes) {
    if (notesEmpty(notes)) return;

    int id;
    cout << "  " << CYAN << "▶" << RESET << " Enter note ID to edit: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Search for note with matching ID
    for (auto& n : notes) {
        if (n.id == id) {
            string input;

            // Update title (optional)
            cout << "  Current title: " << YELLOW << n.title << RESET << "\n";
            cout << "  " << CYAN << "▶" << RESET << " New title (empty to keep current): ";
            getline(cin, input);
            if (!input.empty()) n.title = input;

            // Update content (optional)
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

            // Update modification timestamp
            n.modifiedAt = currentTime();
            cout << "  " << GREEN << "✓" << RESET << " Note updated successfully!\n";
            return;
        }
    }
    cout << "  " << RED << "✗" << RESET << " Note not found.\n";
}

/**
 * Delete a note by ID
 * Uses remove_if algorithm with lambda for efficient deletion
 * 
 * @param notes Vector to remove note from
 */
void deleteNote(vector<Note>& notes) {
    if (notesEmpty(notes)) return;

    int id;
    cout << "  " << CYAN << "▶" << RESET << " Enter note ID to delete: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max());

    // Use STL remove_if with lambda to find and mark for deletion
    auto it = remove_if(notes.begin(), notes.end(), [&](const Note& n) { return n.id == id; });

    if (it != notes.end()) {
        notes.erase(it, notes.end());  // Actually remove from vector
        cout << "  " << GREEN << "✓" << RESET << " Note deleted successfully!\n";
    } else {
        cout << "  " << RED << "✗" << RESET << " Note not found.\n";
    }
}

/**
 * Display all notes with full details
 * Shows ID, title, timestamps, and complete content
 * 
 * @param notes Vector of notes to display
 */
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

/**
 * Display condensed list of all notes (ID and title only)
 * 
 * @param notes Vector of notes to list
 */
void viewAllNotes(vector<Note>& notes) {
    if (notesEmpty(notes)) return;
    
    cout << "\n  " << CYAN << "All Notes:" << RESET << "\n";
    for (const auto& n : notes) {
        cout << "  " << BLUE << n.id << "." << RESET << " " << n.title << '\n';
    }
}

/**
 * Search notes by keyword in title or content
 * Case-sensitive substring search
 * Displays all matching notes with full details
 * 
 * @param notes Vector of notes to search
 */
void searchNotes(vector<Note>& notes) {
    if (notesEmpty(notes)) return;

    string keyword;
    cout << "  " << CYAN << "▶" << RESET << " Enter search keyword: ";
    getline(cin, keyword);

    bool found = false;
    cout << "\n  " << CYAN << "Search Results:" << RESET << "\n";
    cout << "  " << CYAN << "═══════════════════════════════════════════════════════════" << RESET << "\n";
    
    // Search through all notes
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

/**
 * Sort notes alphabetically by title
 * Uses STL sort with lambda comparator
 * 
 * @param notes Vector to sort (modified in-place)
 */
void sortNotesByTitle(vector<Note>& notes) {
    if (notesEmpty(notes)) return;

    // Sort using lambda for title comparison
    sort(notes.begin(), notes.end(), [](const Note& a, const Note& b) { 
        return a.title < b.title; 
    });

    cout << "  " << GREEN << "✓" << RESET << " Notes sorted by title successfully!\n";
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: JSON PERSISTENCE
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Save all notes to JSON file (notes.json)
 * Creates formatted JSON with 4-space indentation
 * Each note includes all fields: id, title, content, timestamps
 * 
 * @param notes Vector of notes to save
 */
void saveNotes(vector<Note>& notes) {
    json j;
    
    // Convert each note to JSON object
    for (const auto& n : notes) {
        j.push_back({
            {"id", n.id},
            {"title", n.title},
            {"content", n.content},
            {"createdAt", n.createdAt},
            {"modifiedAt", n.modifiedAt}
        });
    }

    // Write to file with pretty formatting
    ofstream file("notes.json");
    if (file.is_open()) {
        file << j.dump(4);  // 4-space indentation
        cout << "  " << GREEN << "✓" << RESET << " Notes saved successfully!\n";
    } else {
        cout << "  " << RED << "✗" << RESET << " Error saving notes.\n";
    }
}

/**
 * Load notes from JSON file (notes.json)
 * Clears existing notes before loading
 * Handles missing file gracefully
 * 
 * @param notes Vector to load notes into
 */
void loadNotes(vector<Note>& notes) {
    ifstream file("notes.json");
    if (!file) {
        cout << "  " << YELLOW << "[!]" << RESET << " No saved notes file found.\n";
        return;
    }

    json j;
    file >> j;  // Parse JSON from file

    // Clear existing notes and load from JSON
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

// ═══════════════════════════════════════════════════════════════════════════
// MAIN PROGRAM
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Application entry point
 * 
 * Workflow:
 * 1. Initialize console for colors
 * 2. Show animated banner
 * 3. Main menu loop:
 *    - Display options
 *    - Process user choice
 *    - Execute corresponding function
 *    - Loop until exit
 * 
 * @return 0 on successful exit
 */
int main() {
    // Initialize console for UTF-8 and ANSI colors
    setupConsole();
    
    // Note storage
    vector<Note> notes;

    // Show animated welcome banner
    displayWelcomeBanner();
    
    // Main application loop
    while (true) {
        displayMenu();
        int choice = readInt("Choice: ");
        
        // Process user selection
        switch (choice) {
            case 1:  // Create new note
                createNote(notes);
                break;
                
            case 2:  // View all notes with details
                viewNotes(notes);
                break;
                
            case 3:  // Edit existing note
                editNote(notes);
                break;
                
            case 4:  // Delete note
                deleteNote(notes);
                break;
                
            case 5:  // Search notes by keyword
                searchNotes(notes);
                break;
                
            case 6:  // Sort notes alphabetically
                sortNotesByTitle(notes);
                break;
                
            case 7:  // Save notes to JSON file
                saveNotes(notes);
                break;
                
            case 8:  // Load notes from JSON file
                loadNotes(notes);
                break;
                
            case 0:  // Exit application
                cout << "\n  " << CYAN << "Thank you for using NoteCLI! Goodbye!" << RESET << "\n\n";
                return 0;
                
            default:  // Invalid option
                cout << "  " << RED << "✗" << RESET << " Invalid option. Please choose 0-8.\n";
                break;
        }
    }

    return 0;
}