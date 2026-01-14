# Week 23: Window Overlay Application

## Project Overview
Create an application that draws a transparent overlay on top of other windows for annotations, HUD, or information display.

## Learning Objectives
- Window creation and manipulation
- Transparency and alpha blending
- Graphics rendering (GDI+, Direct2D, OpenGL)
- Input interception
- Layered windows
- Screen coordinate systems

## Features to Implement
- [ ] Create transparent overlay window
- [ ] Always-on-top functionality
- [ ] Click-through capability
- [ ] Drawing tools (pen, shapes, text)
- [ ] Screenshot capture
- [ ] FPS/performance counter display
- [ ] Custom widgets (clock, notes)
- [ ] Hotkey activation/deactivation
- [ ] Multi-monitor support
- [ ] Save/load overlay configurations

## Usage Example
```cpp
OverlayWindow overlay;

// Create overlay on primary monitor
overlay.create(0, 0, 1920, 1080);
overlay.setTransparency(0.7);
overlay.setClickThrough(true);

// Draw on overlay
overlay.drawText(100, 100, "Hello Overlay!");
overlay.drawRect(200, 200, 400, 300);
overlay.drawLine(50, 50, 500, 500);

// Show/hide
overlay.show();
```

## Use Cases
```
- Gaming HUD (FPS, stats)
- Screen annotation tool
- Presentation pointer
- Crosshair overlay
- Performance monitoring
- Real-time captions
- Drawing board
- Timer/stopwatch display
```

## Key Concepts
- Windows: Layered Windows, WS_EX_LAYERED, WS_EX_TRANSPARENT
- Linux: X11 shape extension, compositing
- Alpha blending and transparency
- GDI+/Direct2D for rendering
- Global mouse/keyboard hooks
- Window message handling

## Extensions
- Add recording feature
- Implement gesture recognition
- Create collaborative mode (network)
- Add OCR for on-screen text
- Implement magnifier tool
- Add color picker
- Create screenshot markup
- Implement window snapping
