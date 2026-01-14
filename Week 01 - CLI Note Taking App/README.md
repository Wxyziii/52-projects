# CLI Note-Taking App

A colorful, interactive command-line note-taking application written in C++.

## Features
- Create, view, edit, and delete notes
- Search and sort notes by title
- Save and load notes to/from a JSON file
- Colorful, animated UI with Unicode box drawing
- User-friendly prompts and error messages
- Cross-platform (Windows, with color/Unicode support)

## Usage

### Build

Requires a C++ compiler (e.g. g++):

```sh
g++ -o main.exe main.cpp
```

### Run

```sh
./main.exe
```

### Main Menu

- `1` Create Note
- `2` View Note (detailed)
- `3` Edit Note
- `4` Delete Note
- `5` Search Notes
- `6` Sort Notes by Title
- `7` Save Notes
- `8` Load Notes
- `0` Exit

### Note Input
- When entering note content, type `.` on a new line to finish.
- When editing, leave fields empty to keep current values.

## Data Format
Notes are saved in `notes.json` in the following format:
```json
[
  {
    "id": 1,
    "title": "Sample Note",
    "content": "This is a note...",
    "createdAt": "2026-01-08 12:09",
    "modifiedAt": "2026-01-08 12:09"
  }
]
```

## Dependencies
- [nlohmann/json](https://github.com/nlohmann/json) (included as `json.hpp`)

## Screenshots

```
╔═════════════════════════════════════════════════════════════════╗
║                        MAIN MENU                                ║
╠═════════════════════════════════════════════════════════════════╣
║  1. [+] Create Note      5. [?] Search Notes                    ║
║  2. [=] View Note        6. [*] Sort Notes                      ║
║  3. [~] Edit Note        7. [S] Save Notes                      ║
║  4. [X] Delete Note      8. [L] Load Notes                      ║
║                                                                 ║
║  0. [!] Exit                                                    ║
╚═════════════════════════════════════════════════════════════════╝
```

## License
MIT
