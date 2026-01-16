/*
 * ═══════════════════════════════════════════════════════════════════════════
 * CLI TO DO LIST APPLICATION
 * ═══════════════════════════════════════════════════════════════════════════
 * 
 * A feature-rich command-line task management application with:
 * - Create, view, edit, and delete tasks
 * - Priority levels (Low, Medium, High)
 * - Due date tracking
 * - Task completion status
 * - Undo/Redo functionality with full history
 * - JSON-based persistence
 * - Color-coded interface with animated banner
 * - Sort by priority or status
 * - Search and filter capabilities
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
#include <vector>           // Dynamic arrays for task storage
#include <fstream>          // File I/O for JSON persistence
#include <limits>           // Numeric limits for input validation
#include <stack>            // Stack for undo/redo functionality
#include <algorithm>        // STL algorithms (sort, find, remove_if)
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

#define RESET   "\033[0m"                // Reset all attributes
#define RED     "\033[38;5;131m"         // Muted red for errors/high priority
#define GREEN   "\033[38;5;108m"         // Sage green for success/completed
#define YELLOW  "\033[38;5;179m"         // Muted gold for warnings/medium priority
#define BLUE    "\033[38;5;67m"          // Slate blue for info
#define MAGENTA "\033[38;5;132m"         // Dusty magenta
#define CYAN    "\033[38;5;73m"          // Muted cyan for headers
#define BRIGHT_RED     "\033[38;5;167m"  // Soft coral
#define BRIGHT_GREEN   "\033[38;5;114m"  // Soft green for low priority
#define BRIGHT_YELLOW  "\033[38;5;185m"  // Soft yellow
#define BRIGHT_BLUE    "\033[38;5;74m"   // Soft blue
#define BRIGHT_MAGENTA "\033[38;5;139m"  // Soft mauve
#define BRIGHT_CYAN    "\033[38;5;80m"   // Soft teal for emphasis

// ═══════════════════════════════════════════════════════════════════════════
// DATA STRUCTURES
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Task priority levels
 */
enum class Priority { Low, Medium, High };

/**
 * Convert Priority enum to single-character string
 * 
 * @param p Priority level
 * @return  "H" for High, "M" for Medium, "L" for Low
 */
string priorityToString(Priority p) {
    if (p == Priority::High) return "H";
    if (p == Priority::Medium) return "M";
    return "L";
}

/**
 * Convert integer to Priority enum
 * 
 * @param v Integer value (1=Low, 2=Medium, 3=High)
 * @return  Corresponding Priority level
 */
Priority intToPriority(int v) {
    if (v == 3) return Priority::High;
    if (v == 2) return Priority::Medium;
    return Priority::Low;
}

/**
 * Represents a single task with priority and due date
 */
struct Task {
    string title;                      // Task description
    bool completed = false;            // Completion status
    Priority priority = Priority::Medium;  // Importance level
    string dueDate;                    // Due date (YYYY-MM-DD format)
};

// ═══════════════════════════════════════════════════════════════════════════
// GLOBAL STATE - UNDO/REDO STACKS
// ═══════════════════════════════════════════════════════════════════════════

stack<vector<Task>> undoStack;  // Stack for undo operations
stack<vector<Task>> redoStack;  // Stack for redo operations

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
 * Shows "TASK MASTER" ASCII art with smooth color transitions
 */
void displayWelcomeBanner() {
    const int frames = 40;      // Total animation frames
    const int delay_ms = 80;    // Milliseconds per frame
    
    // Animation loop
    for (int frame = 0; frame < frames; ++frame) {
        // Clear screen and move cursor to home position
        cout << "\033[H\033[2J";
        
        cout << "\n";
        cout << "  " << getGradientColor(0, 0, frame) << "╔════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << "\n";
        cout << "  " << getGradientColor(0, 0, frame) << "║" << RESET << "                                                                                                " << getGradientColor(0, 95, frame) << "║" << RESET << "\n";
        
        cout << "  " << getGradientColor(1, 0, frame) << "║" << RESET << "    " << getGradientColor(1, 4, frame) << "████████╗ █████╗ ███████╗██╗  ██╗    ███╗   ███╗ █████╗ ███████╗████████╗███████╗██████╗ " << RESET << " " << getGradientColor(1, 95, frame) << "  ║" << RESET << "\n";
        cout << "  " << getGradientColor(2, 0, frame) << "║" << RESET << "    " << getGradientColor(2, 4, frame) << "╚══██╔══╝██╔══██╗██╔════╝██║ ██╔╝    ████╗ ████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗" << RESET << " " << getGradientColor(2, 95, frame) << "  ║" << RESET << "\n";
        cout << "  " << getGradientColor(3, 0, frame) << "║" << RESET << "       " << getGradientColor(3, 7, frame) << "██║   ███████║███████╗█████╔╝     ██╔████╔██║███████║███████╗   ██║   █████╗  ██████╔╝" << RESET << " " << getGradientColor(3, 95, frame) << "  ║" << RESET << "\n";
        cout << "  " << getGradientColor(5, 0, frame) << "║" << RESET << "       " << getGradientColor(5, 7, frame) << "██║   ██╔══██║╚════██║██╔═██╗     ██║╚██╔╝██║██╔══██║╚════██║   ██║   ██╔══╝  ██╔══██╗" << RESET << " " << getGradientColor(5, 95, frame) << "  ║" << RESET << "\n";
        cout << "  " << getGradientColor(6, 0, frame) << "║" << RESET << "       " << getGradientColor(6, 7, frame) << "██║   ██║  ██║███████║██║  ██╗    ██║ ╚═╝ ██║██║  ██║███████║   ██║   ███████╗██║  ██║" << RESET << " " << getGradientColor(6, 95, frame) << "  ║" << RESET << "\n";
        cout << "  " << getGradientColor(7, 0, frame) << "║" << RESET << "       " << getGradientColor(7, 7, frame) << "╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝" << RESET << " " << getGradientColor(7, 95, frame) << "  ║" << RESET << "\n";
        cout << "  " << getGradientColor(8, 0, frame) << "║" << RESET << "                                                                                                " << getGradientColor(8, 95, frame) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(9, 0, frame) << "║" << RESET << "                                 " << getGradientColor(9, 33, frame) << "Advanced Task Management System" << RESET << "                                " << getGradientColor(9, 95, frame) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(10, 0, frame) << "║" << RESET << "                           " << getGradientColor(10, 27, frame) << "Priority Tracking • Undo/Redo • Search & Sort" << RESET << "                        " << getGradientColor(10, 95, frame) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(11, 0, frame) << "║" << RESET << "                                                                                                " << getGradientColor(11, 95, frame) << "║" << RESET << "\n";
        cout << "  " << getGradientColor(12, 0, frame) << "╚════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << "\n";
        
        cout << flush;  // Force immediate display
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
    
    // Display final static banner with last frame colors
    cout << "\033[H\033[2J";
    cout << "\n";
    cout << "  " << getGradientColor(0, 0, frames-1) << "╔════════════════════════════════════════════════════════════════════════════════════════════════╗" << RESET << "\n";
    cout << "  " << getGradientColor(0, 0, frames-1) << "║" << RESET << "                                                                                                " << getGradientColor(0, 95, frames-1) << "║" << RESET << "\n";
    
    cout << "  " << getGradientColor(1, 0, frames-1) << "║" << RESET << "    " << getGradientColor(1, 4, frames-1) << "████████╗ █████╗ ███████╗██╗  ██╗    ███╗   ███╗ █████╗ ███████╗████████╗███████╗██████╗ " << RESET << " " << getGradientColor(1, 95, frames-1) << "  ║" << RESET << "\n";
    cout << "  " << getGradientColor(2, 0, frames-1) << "║" << RESET << "    " << getGradientColor(2, 4, frames-1) << "╚══██╔══╝██╔══██╗██╔════╝██║ ██╔╝    ████╗ ████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗" << RESET << " " << getGradientColor(2, 95, frames-1) << "  ║" << RESET << "\n";
    cout << "  " << getGradientColor(3, 0, frames-1) << "║" << RESET << "       " << getGradientColor(3, 7, frames-1) << "██║   ███████║███████╗█████╔╝     ██╔████╔██║███████║███████╗   ██║   █████╗  ██████╔╝" << RESET << " " << getGradientColor(3, 95, frames-1) << "  ║" << RESET << "\n";
    cout << "  " << getGradientColor(5, 0, frames-1) << "║" << RESET << "       " << getGradientColor(5, 7, frames-1) << "██║   ██╔══██║╚════██║██╔═██╗     ██║╚██╔╝██║██╔══██║╚════██║   ██║   ██╔══╝  ██╔══██╗" << RESET << " " << getGradientColor(5, 95, frames-1) << "  ║" << RESET << "\n";
    cout << "  " << getGradientColor(6, 0, frames-1) << "║" << RESET << "       " << getGradientColor(6, 7, frames-1) << "██║   ██║  ██║███████║██║  ██╗    ██║ ╚═╝ ██║██║  ██║███████║   ██║   ███████╗██║  ██║" << RESET << " " << getGradientColor(6, 95, frames-1) << "  ║" << RESET << "\n";
    cout << "  " << getGradientColor(7, 0, frames-1) << "║" << RESET << "       " << getGradientColor(7, 7, frames-1) << "╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝" << RESET << " " << getGradientColor(7, 95, frames-1) << "  ║" << RESET << "\n";
    cout << "  " << getGradientColor(8, 0, frames-1) << "║" << RESET << "                                                                                                " << getGradientColor(8, 95, frames-1) << "║" << RESET << "\n";
    cout << "  " << getGradientColor(9, 0, frames-1) << "║" << RESET << "                                 " << getGradientColor(9, 33, frames-1) << "Advanced Task Management System" << RESET << "                                " << getGradientColor(9, 95, frames-1) << "║" << RESET << "\n";
    cout << "  " << getGradientColor(10, 0, frames-1) << "║" << RESET << "                           " << getGradientColor(10, 27, frames-1) << "Priority Tracking • Undo/Redo • Search & Sort" << RESET << "                        " << getGradientColor(10, 95, frames-1) << "║" << RESET << "\n";
    cout << "  " << getGradientColor(11, 0, frames-1) << "║" << RESET << "                                                                                                " << getGradientColor(11, 95, frames-1) << "║" << RESET << "\n";
    cout << "  " << getGradientColor(12, 0, frames-1) << "╚════════════════════════════════════════════════════════════════════════════════════════════════╝" << RESET << "\n";
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: MENU DISPLAY
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Display main application menu with options
 * Shows 9 operations in organized layout
 */
void displayMenu() {
    cout << "\n";
    cout << "  ============================= MAIN MENU =============================\n";
    cout << "  1. [+] Add Task             5. [?] Search Tasks\n";
    cout << "  2. [=] View Tasks           6. [*] Sort Tasks\n";
    cout << "  3. [~] Edit Task            7. [<] Undo\n";
    cout << "  4. [X] Delete Task          8. [>] Redo\n";
    cout << "                              9. [!] Exit\n";
    cout << "  ====================================================================\n";
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

/**
 * Save current state to undo stack for undo functionality
 * Clears redo stack when new action is taken
 * 
 * @param tasks Current task list to save
 */
void saveState(const vector<Task>& tasks) {
    undoStack.push(tasks);
    
    // Clear redo stack when new action is performed
    while (!redoStack.empty()) redoStack.pop();
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: JSON PERSISTENCE
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Save all tasks to JSON file (tasks.json)
 * Creates formatted JSON with 4-space indentation
 * Each task includes: title, completed status, priority, due date
 * 
 * @param tasks Vector of tasks to save
 */
void saveTasks(const vector<Task>& tasks) {
    json j;
    j["tasks"] = json::array();

    // Convert each task to JSON object
    for (const auto& t : tasks) {
        j["tasks"].push_back({
            {"title", t.title},
            {"completed", t.completed},
            {"priority", (int)t.priority},
            {"dueDate", t.dueDate}
        });
    }

    // Write to file with pretty formatting
    ofstream file("tasks.json");
    if (file.is_open()) {
        file << j.dump(4);  // 4-space indentation
    }
}

/**
 * Load tasks from JSON file (tasks.json)
 * Handles missing file and invalid JSON gracefully
 * Uses value() method with defaults for safe extraction
 * 
 * @param tasks Vector to load tasks into
 */
void loadTasks(vector<Task>& tasks) {
    ifstream file("tasks.json");
    if (!file.is_open()) return;  // File doesn't exist yet

    json j;

    // Try to parse JSON, handle corruption
    try {
        file >> j;
    } catch (...) {
        cout << "  " << YELLOW << "[!]" << RESET << " Invalid JSON file. Starting fresh.\n";
        return;
    }

    // Extract tasks array if it exists
    if (j.contains("tasks") && j["tasks"].is_array()) {
        for (const auto& item : j["tasks"]) {
            Task task;
            task.title = item.value("title", "");
            task.completed = item.value("completed", false);
            task.priority = intToPriority(item.value("priority", 2));
            task.dueDate = item.value("dueDate", "");

            // Only add non-empty tasks
            if (!task.title.empty()) {
                tasks.push_back(task);
            }
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: UTILITY FUNCTIONS
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Check if a task with given title already exists
 * 
 * @param tasks Vector to search in
 * @param title Task title to search for
 * @return      true if task exists, false otherwise
 */
bool taskExists(const vector<Task>& tasks, const string& title) {
    for (const auto& t : tasks) {
        if (t.title == title) {
            return true;
        }
    }
    return false;
}

/**
 * Get color-coded priority symbol for display
 * 
 * @param p Priority level
 * @return  Color-coded string: [H] (red), [M] (yellow), or [L] (green)
 */
string getPrioritySymbol(Priority p) {
    if (p == Priority::High) return RED "[H]" RESET;
    if (p == Priority::Medium) return YELLOW "[M]" RESET;
    return GREEN "[L]" RESET;
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: CORE TASK OPERATIONS
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Display all tasks with formatted output
 * Shows completion status, priority, title, and due date
 * 
 * @param tasks Vector of tasks to display
 */
void displayTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\n  [i] No tasks found. Add one to get started!\n";
        return;
    }

    cout << "\n  ========================== YOUR TASKS ==========================\n\n";

    // Display each task with index, checkbox, priority, and details
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << "  " << i + 1 << ". ";
        
        // Show completion checkbox
        if (tasks[i].completed) {
            cout << "[V] ";  // Completed
        } else {
            cout << "[ ] ";  // Not completed
        }
        
        // Show priority and title
        cout << getPrioritySymbol(tasks[i].priority) << " " << tasks[i].title;
        
        // Show due date if set
        if (!tasks[i].dueDate.empty()) {
            cout << " (Due: " << tasks[i].dueDate << ")";
        }
        cout << '\n';
    }
    
    cout << "\n  ================================================================\n";
}

/**
 * Add a new task interactively
 * Prompts for title, priority, and optional due date
 * Validates for empty titles and duplicate task names
 * 
 * @param tasks Vector to add new task to
 */
void addTask(vector<Task>& tasks) {
    cout << "\n  ========================= ADD NEW TASK =========================\n\n";

    string title = readLine("Task title: ");
    
    // Validate title is not empty
    if (title.empty()) {
        cout << "  " << RED << "[X]" << RESET << " Task title cannot be empty.\n";
        return;
    }
    
    // Check for duplicate task title
    if (taskExists(tasks, title)) {
        cout << "  " << RED << "[X]" << RESET << " A task with this title already exists.\n";
        return;
    }

    // Get priority level
    int p = readInt("Priority (1 = Low, 2 = Medium, 3 = High): ");
    
    // Get optional due date
    string due = readLine("Due date (YYYY-MM-DD or leave empty): ");

    // Save state for undo, add task, persist to file
    saveState(tasks);
    tasks.push_back({title, false, intToPriority(p), due});
    saveTasks(tasks);
    
    cout << "  " << GREEN << "[V]" << RESET << " Task added successfully!\n";
}

/**
 * Delete a task by index with confirmation
 * Displays task list and prompts for selection
 * Requires user confirmation before deletion
 * 
 * @param tasks Vector to delete task from
 */
void deleteTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\n  [i] No tasks to delete.\n";
        return;
    }

    cout << "\n  ========================== DELETE TASK ==========================\n\n";

    displayTasks(tasks);
    
    // Get task number (1-indexed)
    int idx = readInt("Delete which task (number): ") - 1;
    
    // Validate index
    if (idx < 0 || idx >= (int)tasks.size()) {
        cout << "  " << RED << "[X]" << RESET << " Invalid task number.\n";
        return;
    }

    // Require confirmation
    string confirm = readLine("Confirm delete (y/n): ");
    if (confirm.empty() || tolower(confirm[0]) != 'y') {
        cout << "  " << RED << "[X]" << RESET << " Deletion cancelled.\n";
        return;
    }

    saveState(tasks);
    tasks.erase(tasks.begin() + idx);
    saveTasks(tasks);
    
    cout << "  " << GREEN << "[V]" << RESET << " Task deleted successfully!\n";
}

/**
 * Edit an existing task by index
 * Allows updating title, completion status, priority, and due date
 * Empty input keeps current value
 * 
 * @param tasks Vector of tasks to modify
 */
void editTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\n  [i] No tasks to edit.\n";
        return;
    }

    cout << "\n  =========================== EDIT TASK ===========================\n\n";

    displayTasks(tasks);
    
    // Get task number (1-indexed)
    int idx = readInt("Edit which task (number): ") - 1;
    
    // Validate index
    if (idx < 0 || idx >= (int)tasks.size()) {
        cout << "  " << RED << "[X]" << RESET << " Invalid task number.\n";
        return;
    }

    // Save state for undo
    saveState(tasks);
    Task& t = tasks[idx];

    // Update title (optional)
    cout << "\n  Current title: " << t.title << '\n';
    string nt = readLine("New title (leave empty to keep): ");
    if (!nt.empty() && !taskExists(tasks, nt)) {
        t.title = nt;
    }

    // Update completion status (optional)
    string c = readLine("Completed (y/n/leave empty to keep): ");
    if (!c.empty()) {
        t.completed = (tolower(c[0]) == 'y');
    }

    // Update priority (optional)
    int np = readInt("Priority (1 = Low, 2 = Medium, 3 = High, 0 = keep): ");
    if (np >= 1 && np <= 3) {
        t.priority = intToPriority(np);
    }

    // Update due date (optional)
    string nd = readLine("Due date (YYYY-MM-DD or leave empty): ");
    if (!nd.empty()) {
        t.dueDate = nd;
    }
    
    // Persist changes
    saveTasks(tasks);
    cout << "  " << GREEN << "[V]" << RESET << " Task updated successfully!\n";
}

/**
 * Search tasks by keyword in title
 * Case-sensitive substring search
 * Displays all matching tasks with full details
 * 
 * @param tasks Vector of tasks to search
 */
void searchTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\n  [i] No tasks to search.\n";
        return;
    }

    cout << "\n  ========================== SEARCH TASKS =========================\n\n";

    string query = readLine("Search query: ");
    
    // Validate query is not empty
    if (query.empty()) {
        cout << "  " << RED << "[X]" << RESET << " Search query cannot be empty.\n";
        return;
    }

    cout << "\n  Search results:\n\n";
    
    bool found = false;
    
    // Search through all tasks
    for (size_t i = 0; i < tasks.size(); ++i) {
        if (tasks[i].title.find(query) != string::npos) {
            cout << "  " << i + 1 << ". ";
            
            // Show completion checkbox
            if (tasks[i].completed) {
                cout << "[V] ";
            } else {
                cout << "[ ] ";
            }
            
            // Show priority and details
            cout << getPrioritySymbol(tasks[i].priority) << " " << tasks[i].title;
            
            if (!tasks[i].dueDate.empty()) {
                cout << " (Due: " << tasks[i].dueDate << ")";
            }
            cout << '\n';
            found = true;
        }
    }
    
    if (!found) {
        cout << "  [i] No tasks found matching \"" << query << "\"\n";
    }
    cout << '\n';
}

/**
 * Sort tasks by priority or completion status
 * Uses STL sort with lambda comparators
 * 
 * @param tasks Vector to sort (modified in-place)
 */
void sortTasks(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "\n  [i] No tasks to sort.\n";
        return;
    }

    cout << "\n  =========================== SORT TASKS ===========================\n\n";

    int opt = readInt("Sort by (1 = Priority, 2 = Completion): ");
    
    // Save state for undo
    saveState(tasks);

    if (opt == 1) {
        // Sort by priority (High to Low)
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.priority > b.priority;
        });
        cout << "  " << GREEN << "[V]" << RESET << " Tasks sorted by priority!\n";
    } else if (opt == 2) {
        // Sort by completion (incomplete first)
        sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
            return a.completed < b.completed;
        });
        cout << "  " << GREEN << "[V]" << RESET << " Tasks sorted by completion status!\n";
    } else {
        cout << "  " << RED << "[X]" << RESET << " Invalid option.\n";
        undoStack.pop();  // Remove invalid state
        return;
    }

    // Persist sorted order
    saveTasks(tasks);
}

// ═══════════════════════════════════════════════════════════════════════════
// IMPLEMENTATION: UNDO/REDO OPERATIONS
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Undo the last operation
 * Restores previous state from undo stack
 * Saves current state to redo stack
 * 
 * @param tasks Current task list to revert
 */
void undo(vector<Task>& tasks) {
    if (undoStack.empty()) {
        cout << "\n  " << CYAN << "[i]" << RESET << " Nothing to undo.\n";
        return;
    }
    
    // Save current state to redo stack
    redoStack.push(tasks);
    
    // Restore previous state
    tasks = undoStack.top();
    undoStack.pop();
    saveTasks(tasks);
    
    cout << "  " << GREEN << "[V]" << RESET << " Undo successful!\n";
}

/**
 * Redo the last undone operation
 * Restores state from redo stack
 * Saves current state to undo stack
 * 
 * @param tasks Current task list to advance
 */
void redo(vector<Task>& tasks) {
    if (redoStack.empty()) {
        cout << "\n  " << CYAN << "[i]" << RESET << " Nothing to redo.\n";
        return;
    }
    
    // Save current state to undo stack
    undoStack.push(tasks);
    
    // Restore redone state
    tasks = redoStack.top();
    redoStack.pop();
    saveTasks(tasks);
    
    cout << "  " << GREEN << "[V]" << RESET << " Redo successful!\n";
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN FUNCTION
// ═══════════════════════════════════════════════════════════════════════════

/**
 * Application entry point
 * 
 * Workflow:
 * 1. Initialize console for ANSI colors
 * 2. Load tasks from JSON file
 * 3. Show animated welcome banner
 * 4. Main menu loop:
 *    - Display menu options
 *    - Process user input
 *    - Execute corresponding function
 *    - Loop until exit
 * 
 * @return 0 on successful exit
 */
int main() {
    // Initialize console for UTF-8 and ANSI colors
    setupConsole();
    
    // Task storage
    vector<Task> tasks;
    
    // Load existing tasks from file
    loadTasks(tasks);

    // Show animated welcome banner
    displayWelcomeBanner();

    // Main application loop
    while (true) {
        displayMenu();

        int choice = readInt("Choice: ");

        // Process user selection
        switch (choice) {
            case 1:  // Add new task
                addTask(tasks);
                break;

            case 2:  // View all tasks
                displayTasks(tasks);
                break;

            case 3:  // Edit task
                editTask(tasks);
                break;

            case 4:  // Delete task
                deleteTask(tasks);
                break;

            case 5:  // Search tasks
                searchTasks(tasks);
                break;

            case 6:  // Sort tasks
                sortTasks(tasks);
                break;

            case 7:  // Undo last operation
                undo(tasks);
                break;

            case 8:  // Redo last undone operation
                redo(tasks);
                break;

            case 9:
                cout << "\n";
                cout << "  ============================================================\n";
                cout << "             Thank you for using Task Manager!\n";
                cout << "             Stay organized, stay productive!\n";
                cout << "  ============================================================\n";
                cout << "\n";
                saveTasks(tasks);
                return 0;

            default:
                cout << "  " << RED << "[X]" << RESET << " Invalid option. Please choose 1-9.\n";
                break;
        }
    }

    return 0;
}