# Week 39: Desktop Notification System

## Project Overview
Create a cross-platform notification system for displaying alerts, reminders, and updates.

## Learning Objectives
- Native notification APIs
- Event scheduling
- Inter-process communication
- System tray integration
- Notification persistence
- Action buttons and callbacks

## Features to Implement
- [ ] Display notifications with title/body
- [ ] Support images/icons
- [ ] Action buttons (e.g., "Open", "Dismiss")
- [ ] Notification queue management
- [ ] Priority levels
- [ ] Sound alerts
- [ ] Persistent notifications
- [ ] Notification history
- [ ] Do Not Disturb mode
- [ ] Custom notification styles

## Usage Example
```cpp
NotificationSystem notif;

// Simple notification
notif.show("Title", "Message body");

// With icon
notif.show("Update Available", 
           "Version 2.0 is ready to install",
           "icon.png");

// With actions
notif.show("New Message",
           "You have a new email from Alice",
           NotificationPriority::HIGH)
    .addAction("Open", []() {
        openEmailClient();
    })
    .addAction("Dismiss", []() {
        // Do nothing
    })
    .setSound("notification.wav")
    .setTimeout(5000);

// Scheduled notification
notif.schedule("Reminder",
               "Meeting in 15 minutes",
               std::chrono::minutes(15));
```

## CLI Interface
```sh
# Send notification
./notify "Title" "Message"

# With icon and timeout
./notify "Title" "Message" \
  --icon info.png \
  --timeout 5000

# With actions
./notify "Question" "Save changes?" \
  --action "Save:save_cmd" \
  --action "Discard:discard_cmd"

# List active notifications
./notify --list

# Clear all
./notify --clear
```

## Notification Display
```
┌─────────────────────────────────────┐
│ ℹ️  System Update                   │
├─────────────────────────────────────┤
│ A new version is available.         │
│ Click to install now.               │
│                                     │
│ [Install Now]  [Later]  [×]        │
└─────────────────────────────────────┘
```

## Implementation
```cpp
class NotificationSystem {
public:
    void show(const Notification& notif) {
#ifdef _WIN32
        showWindowsToast(notif);
#elif __APPLE__
        showMacNotification(notif);
#elif __linux__
        showLibnotify(notif);
#endif
    }
    
private:
    void showWindowsToast(const Notification& notif) {
        // Use Windows Toast Notifications
        ToastNotification toast;
        toast.setTitle(notif.title);
        toast.setBody(notif.body);
        toast.setImage(notif.icon);
        
        for (const auto& action : notif.actions) {
            toast.addButton(action.label, action.callback);
        }
        
        toast.show();
    }
};
```

## Key Concepts
- Windows: Toast Notifications API
- macOS: NSUserNotificationCenter
- Linux: libnotify, D-Bus
- System tray icon management
- Notification grouping
- Action callbacks
- Persistence and history

## Extensions
- Add notification templates
- Implement rich text formatting
- Create notification channels
- Add snooze functionality
- Implement notification sync
- Add priority-based filtering
- Create notification analytics
- Implement custom sounds
