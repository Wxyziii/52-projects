# Week 34: Cross-Platform GUI App

## Project Overview
Create a simple cross-platform GUI application using Qt or wxWidgets framework.

## Learning Objectives
- GUI framework basics
- Event-driven programming
- Layout management
- Signal/slot pattern (Qt)
- Cross-platform compilation
- Resource management

## Features to Implement
- [ ] Main window with menu bar
- [ ] Multiple widgets (buttons, text fields, etc.)
- [ ] Layout management
- [ ] Event handling
- [ ] File dialogs
- [ ] Settings persistence
- [ ] Status bar
- [ ] Toolbar with icons
- [ ] Multi-window support
- [ ] Keyboard shortcuts

## Example Application Ideas
```
1. Simple Text Editor
   - Open/save files
   - Find and replace
   - Syntax highlighting
   - Font customization

2. Image Viewer
   - Load/display images
   - Zoom in/out
   - Rotation
   - Basic filters

3. Todo List App
   - Add/edit/delete tasks
   - Mark as complete
   - Categories
   - Export to file
```

## Qt Example
```cpp
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow() {
        auto* central = new QWidget(this);
        auto* layout = new QVBoxLayout(central);
        
        auto* button = new QPushButton("Click Me!");
        connect(button, &QPushButton::clicked,
                this, &MainWindow::onButtonClicked);
        
        layout->addWidget(button);
        setCentralWidget(central);
    }

private slots:
    void onButtonClicked() {
        QMessageBox::information(this, "Hello", 
                                "Button clicked!");
    }
};
```

## CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyGUIApp)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(myapp main.cpp mainwindow.cpp)
target_link_libraries(myapp Qt5::Widgets)
```

## Key Concepts
- Event loop and event handling
- Signal/slot mechanism (Qt)
- Layout managers (vertical, horizontal, grid)
- Widget hierarchy
- QPainter for custom drawing
- Model-View architecture
- Resource files (.qrc)

## Extensions
- Add dark mode theme
- Implement drag and drop
- Create custom widgets
- Add internationalization (i18n)
- Implement undo/redo
- Add accessibility features
- Create installer/package
- Implement auto-updates
