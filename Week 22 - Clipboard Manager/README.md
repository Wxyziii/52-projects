# Week 22: Clipboard Manager

## Project Overview
Create a clipboard manager that tracks clipboard history and provides advanced clipboard features.

## Learning Objectives
- Clipboard API usage
- Event monitoring
- Data serialization
- Keyboard shortcuts/hotkeys
- Background process management
- UI notifications

## Features to Implement
- [ ] Monitor clipboard changes
- [ ] Store clipboard history
- [ ] Support text, images, files
- [ ] Search clipboard history
- [ ] Pin favorite items
- [ ] Categories/tags for items
- [ ] Quick paste via hotkey
- [ ] Clipboard sync across apps
- [ ] Export/import history
- [ ] Persistent storage

## Usage Example
```sh
# Start clipboard manager
./clipman

# Show history
./clipman history

# Search
./clipman search "important"

# Get specific item
./clipman get 5

# Clear history
./clipman clear
```

## UI Display
```
╔════════════════════════════════════════════╗
║        Clipboard Manager (Ctrl+Shift+V)    ║
╠════════════════════════════════════════════╣
║ 1. [TXT] Lorem ipsum dolor sit amet...    ║
║ 2. [IMG] screenshot_2026.png              ║
║ 3. [TXT] https://github.com/example       ║
║ 4. ⭐ [TXT] Important password            ║
║ 5. [FILE] document.pdf                    ║
╠════════════════════════════════════════════╣
║ [Enter] Paste | [Del] Remove | [*] Pin    ║
╚════════════════════════════════════════════╝
```

## Key Concepts
- Windows: Win32 Clipboard API, AddClipboardFormatListener
- Linux: X11 clipboard, XCB
- Clipboard format detection
- Global hotkey registration
- System tray integration
- Data encryption for sensitive content

## Extensions
- Add clipboard sync between devices
- Implement OCR for images
- Create smart paste (format detection)
- Add password protection
- Implement auto-clear after time
- Add blacklist for sensitive apps
- Create clipboard macros
- Implement cloud backup
