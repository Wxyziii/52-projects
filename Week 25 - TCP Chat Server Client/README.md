# Week 25: TCP Chat Server + Client

## Project Overview
Build a multi-client TCP chat server and client application with real-time messaging capabilities.

## Learning Objectives
- Socket programming
- TCP connection handling
- Multi-client server architecture
- Thread-per-client or async I/O
- Message framing and protocols
- Network error handling

## Features to Implement
- [ ] TCP server with multiple clients
- [ ] Client connection/disconnection handling
- [ ] Broadcast messages to all clients
- [ ] Private messaging between users
- [ ] Username/authentication
- [ ] Chat rooms/channels
- [ ] Message history
- [ ] Typing indicators
- [ ] File transfer support
- [ ] Command system (/help, /quit, /msg)

## Usage Example
```sh
# Start server
./chatserver --port 8888

# Connect client
./chatclient --host localhost --port 8888

# Client commands
/join #general
/msg Alice Hello!
/users
/quit
```

## Chat Session
```
[Server] Chat server started on port 8888
[Server] Client connected: 192.168.1.100
[Server] User 'Alice' joined #general

[Alice]: Hello everyone!
[Bob]: Hi Alice!
[You → Alice]: Private message
[Server] User 'Charlie' joined #general
[Charlie]: Hey all!
```

## Protocol Design
```
Message Format:
[TYPE][LENGTH][DATA]

Types:
- 0x01: Text message
- 0x02: Private message
- 0x03: Join room
- 0x04: User list request
- 0x05: File transfer
- 0x06: Disconnect

Example:
[0x01][0x000B]["Hello World"]
```

## Key Concepts
- Socket API (socket, bind, listen, accept)
- select() or epoll for multiplexing
- Thread pool for client handling
- Message serialization
- Keep-alive mechanisms
- Graceful disconnection

## Extensions
- Add SSL/TLS encryption
- Implement presence system
- Add emoji and formatting
- Create web-based client
- Implement message persistence
- Add user authentication (OAuth)
- Create bot API
- Implement voice chat
