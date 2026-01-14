# Week 37: Screenshot Utility

## Project Overview
Create a screenshot capture tool with editing capabilities and various capture modes.

## Learning Objectives
- Screen capture APIs
- Image manipulation
- Drawing overlays
- Hotkey registration
- Image format handling
- System tray integration

## Features to Implement
- [ ] Full screen capture
- [ ] Region selection capture
- [ ] Window capture
- [ ] Scrolling window capture
- [ ] Delayed capture
- [ ] Annotation tools (arrows, text, shapes)
- [ ] Blur/pixelate regions
- [ ] Save to file or clipboard
- [ ] Multiple monitor support
- [ ] Quick sharing options

## Usage Modes
```
Capture Types:
1. Full Screen     - Entire desktop
2. Region          - User-defined rectangle
3. Window          - Specific window
4. Scrolling       - Long webpage/document
5. Free-form       - Custom shape

Hotkeys:
- Print Screen     - Full screen
- Alt+Print Screen - Active window
- Ctrl+Shift+S     - Region select
```

## UI Example
```
╔════════════════════════════════════════════╗
║   Screenshot Tool                          ║
╠════════════════════════════════════════════╣
║ Capture Mode:                              ║
║ ( ) Full Screen                            ║
║ (•) Region Selection                       ║
║ ( ) Active Window                          ║
║ ( ) Scrolling Capture                      ║
║                                            ║
║ Delay: [3] seconds                         ║
║                                            ║
║ Tools:                                     ║
║ [✏️] [➡️] [▭] [🔴] [A] [🌫️]                 ║
║                                            ║
║ Save Options:                              ║
║ Format: [PNG ▼]  Quality: [95%]            ║
║ ☑ Copy to clipboard                        ║
║ ☑ Auto-save to folder                      ║
║                                            ║
║    [Capture]  [Edit]  [Save]  [Share]     ║
╚════════════════════════════════════════════╝
```

## Implementation
```cpp
class ScreenshotTool : public QMainWindow {
    Q_OBJECT
private:
    void captureFullScreen() {
        QScreen* screen = QGuiApplication::primaryScreen();
        QPixmap screenshot = screen->grabWindow(0);
        showEditor(screenshot);
    }
    
    void captureRegion() {
        // Show semi-transparent overlay
        auto* selector = new RegionSelector();
        connect(selector, &RegionSelector::regionSelected,
                this, &ScreenshotTool::onRegionSelected);
        selector->showFullScreen();
    }
    
    void onRegionSelected(const QRect& region) {
        QScreen* screen = QGuiApplication::primaryScreen();
        QPixmap screenshot = screen->grabWindow(
            0, region.x(), region.y(),
            region.width(), region.height());
        showEditor(screenshot);
    }
    
    void showEditor(const QPixmap& image) {
        auto* editor = new ImageEditor(image);
        editor->show();
    }
};
```

## Key Concepts
- QScreen::grabWindow() for capture
- QPainter for annotations
- QRubberBand for region selection
- Global hotkeys with QxtGlobalShortcut
- Image formats (PNG, JPG, BMP)
- System tray icon with QSystemTrayIcon

## Extensions
- Add OCR for text extraction
- Implement video recording
- Add GIF creation
- Create screen color picker
- Implement scrolling capture
- Add cloud upload (Imgur, etc.)
- Create annotation templates
- Implement watermarking
