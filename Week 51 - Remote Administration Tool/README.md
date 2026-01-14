# Week 51: Remote Administration Tool

## Project Overview
Build a secure remote administration tool for managing computers over a network (ethical use only, local network).

## Learning Objectives
- Network communication
- Remote desktop protocol
- File transfer
- Command execution
- Authentication and encryption
- Security best practices

## Features to Implement
- [ ] Secure authentication
- [ ] Remote desktop viewing
- [ ] Remote command execution
- [ ] File transfer (upload/download)
- [ ] File manager
- [ ] Process management
- [ ] System information viewer
- [ ] Screenshot capture
- [ ] Chat/messaging
- [ ] Session recording
- [ ] Multi-client support
- [ ] Encrypted communication (TLS)

## Architecture
```
┌─────────────────────────────────────┐
│         Admin Client (GUI)          │
├─────────────────────────────────────┤
│ - Desktop Viewer                    │
│ - File Manager                      │
│ - Process Manager                   │
│ - Command Shell                     │
└─────────────────┬───────────────────┘
                  │ TLS Encrypted
                  │ Connection
┌─────────────────▼───────────────────┐
│         Agent (Target PC)            │
├─────────────────────────────────────┤
│ - Screen Capture                    │
│ - Input Injection                   │
│ - File Operations                   │
│ - Process Control                   │
│ - Command Execution                 │
└─────────────────────────────────────┘
```

## Security Considerations
```
⚠️  IMPORTANT SECURITY NOTICE ⚠️

This tool is for ETHICAL use only:
- Only use on your own computers
- Only use on computers you have explicit permission to access
- Use only on local/private networks
- Implement strong authentication
- Use TLS encryption for all communications
- Log all connections and activities
- Comply with all applicable laws and regulations

Unauthorized access to computer systems is illegal.
```

## Protocol Definition
```cpp
enum class MessageType : uint8_t {
    AUTH_REQUEST = 0x01,
    AUTH_RESPONSE = 0x02,
    SCREEN_FRAME = 0x10,
    MOUSE_EVENT = 0x11,
    KEYBOARD_EVENT = 0x12,
    FILE_LIST_REQUEST = 0x20,
    FILE_LIST_RESPONSE = 0x21,
    FILE_DOWNLOAD = 0x22,
    FILE_UPLOAD = 0x23,
    EXECUTE_COMMAND = 0x30,
    COMMAND_OUTPUT = 0x31,
    PROCESS_LIST = 0x40,
    PROCESS_KILL = 0x41,
    SYSTEM_INFO = 0x50
};

struct Message {
    MessageType type;
    uint32_t length;
    std::vector<uint8_t> data;
};
```

## Agent Implementation
```cpp
class RemoteAgent {
    TLSSocket socket_;
    ScreenCapture screenCapture_;
    InputInjector inputInjector_;
    FileManager fileManager_;
    
public:
    void start(const std::string& serverAddr, 
               int port) {
        if (!authenticate(serverAddr, port)) {
            throw std::runtime_error(
                "Authentication failed");
        }
        
        socket_.connect(serverAddr, port);
        
        while (running_) {
            auto message = receiveMessage();
            handleMessage(message);
        }
    }
    
private:
    bool authenticate(const std::string& addr, 
                     int port) {
        // Exchange credentials
        // Verify server certificate
        // Establish secure session
        return true;
    }
    
    void handleMessage(const Message& msg) {
        switch (msg.type) {
        case MessageType::SCREEN_FRAME:
            sendScreenFrame();
            break;
            
        case MessageType::MOUSE_EVENT:
            handleMouseEvent(msg.data);
            break;
            
        case MessageType::KEYBOARD_EVENT:
            handleKeyboardEvent(msg.data);
            break;
            
        case MessageType::FILE_LIST_REQUEST:
            sendFileList(msg.data);
            break;
            
        case MessageType::EXECUTE_COMMAND:
            executeCommand(msg.data);
            break;
        }
    }
    
    void sendScreenFrame() {
        auto frame = screenCapture_.capture();
        auto compressed = compressJPEG(frame, 75);
        
        Message msg{
            MessageType::SCREEN_FRAME,
            static_cast<uint32_t>(compressed.size()),
            compressed
        };
        
        sendMessage(msg);
    }
};
```

## Client GUI
```cpp
class AdminClient : public QMainWindow {
    Q_OBJECT
private:
    TLSSocket socket_;
    QLabel* screenView_;
    QTreeWidget* fileTree_;
    QTableWidget* processTable_;
    
public:
    void connectToAgent(const std::string& host,
                       int port,
                       const std::string& password) {
        socket_.connect(host, port);
        
        // Authenticate
        Message authMsg{
            MessageType::AUTH_REQUEST,
            static_cast<uint32_t>(password.size()),
            std::vector<uint8_t>(
                password.begin(), password.end())
        };
        socket_.send(authMsg);
        
        // Start receiving frames
        startFrameReceiver();
    }
    
private slots:
    void onFrameReceived(const QImage& frame) {
        screenView_->setPixmap(
            QPixmap::fromImage(frame));
    }
    
    void onMouseClick(QMouseEvent* event) {
        // Send mouse event to agent
        Message msg{
            MessageType::MOUSE_EVENT,
            sizeof(MouseEvent),
            serializeMouseEvent(event)
        };
        socket_.send(msg);
    }
    
    void onFileDownloadClicked() {
        QString path = fileTree_->currentItem()->text();
        
        Message msg{
            MessageType::FILE_DOWNLOAD,
            static_cast<uint32_t>(path.size()),
            std::vector<uint8_t>(
                path.begin(), path.end())
        };
        socket_.send(msg);
    }
    
    void executeRemoteCommand(const QString& cmd) {
        Message msg{
            MessageType::EXECUTE_COMMAND,
            static_cast<uint32_t>(cmd.size()),
            std::vector<uint8_t>(
                cmd.begin(), cmd.end())
        };
        socket_.send(msg);
    }
};
```

## Key Concepts
- TLS/SSL for encryption
- Certificate-based authentication
- Screen capture (Windows: DXGI, Linux: X11)
- Input injection
- Frame compression (JPEG, H.264)
- Network protocol design
- Privilege escalation handling

## Extensions
- Add clipboard synchronization
- Implement audio streaming
- Create mobile client app
- Add wake-on-LAN support
- Implement port forwarding
- Add scripting automation
- Create web-based interface
- Implement session persistence

## Legal Disclaimer
```
This project is for educational purposes only.
Always ensure you have explicit authorization before
accessing any computer system remotely. Unauthorized
access is illegal and unethical.
```
