# Week 27: Simple HTTP Server

## Project Overview
Build a basic HTTP web server from scratch that can serve static files and handle HTTP requests.

## Learning Objectives
- HTTP protocol implementation
- Socket server programming
- Multi-threaded request handling
- MIME type detection
- URL routing
- Static file serving

## Features to Implement
- [ ] HTTP GET request handling
- [ ] Static file serving (HTML, CSS, JS, images)
- [ ] MIME type detection
- [ ] Directory listing
- [ ] Custom 404 error pages
- [ ] Basic routing system
- [ ] Query parameter parsing
- [ ] POST request handling
- [ ] Keep-alive connections
- [ ] Request logging
- [ ] Virtual hosts (optional)

## Usage Example
```sh
# Start server on port 8080
./httpserver --port 8080 --root ./public

# With custom config
./httpserver --config server.conf

# Enable directory listing
./httpserver --port 8080 --root ./files --list
```

## API Usage
```cpp
HttpServer server(8080);

// Serve static files
server.setDocumentRoot("./public");

// Add route
server.route("/api/hello", [](const Request& req, Response& res) {
    res.setStatus(200);
    res.setBody("Hello, World!");
});

// Start server
server.start();
```

## Example Session
```
[2026-01-14 10:30:15] Server started on port 8080
[2026-01-14 10:30:20] 192.168.1.100 GET /index.html 200 1.2kb 12ms
[2026-01-14 10:30:22] 192.168.1.100 GET /style.css 200 856b 5ms
[2026-01-14 10:30:23] 192.168.1.100 GET /script.js 200 2.4kb 8ms
[2026-01-14 10:30:45] 192.168.1.101 GET /api/data 404 - 2ms
```

## HTTP Response Format
```
HTTP/1.1 200 OK\r\n
Content-Type: text/html\r\n
Content-Length: 1234\r\n
Connection: keep-alive\r\n
\r\n
<html>...</html>
```

## Key Concepts
- Socket bind, listen, accept
- Multi-threading or async I/O
- HTTP request parsing
- Response generation
- MIME types mapping
- Path traversal prevention
- Error handling (404, 500)

## Extensions
- Add HTTPS support (SSL/TLS)
- Implement CGI/FastCGI
- Add gzip compression
- Implement range requests
- Create WebSocket support
- Add rate limiting
- Implement cache headers
- Support virtual hosts
