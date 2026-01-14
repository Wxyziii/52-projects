# Week 26: HTTP Client

## Project Overview
Implement an HTTP client from scratch without using libcurl, supporting GET, POST, and other HTTP methods.

## Learning Objectives
- HTTP protocol fundamentals
- TCP socket programming
- Request/response parsing
- Header handling
- URL parsing
- SSL/TLS basics (optional)

## Features to Implement
- [ ] HTTP GET requests
- [ ] HTTP POST with form data
- [ ] PUT, DELETE, PATCH methods
- [ ] Custom headers
- [ ] Query parameters
- [ ] Response header parsing
- [ ] Status code handling
- [ ] Redirect following
- [ ] Chunked transfer encoding
- [ ] Connection keep-alive
- [ ] Basic authentication
- [ ] JSON request/response

## Usage Example
```cpp
HttpClient client;

// Simple GET
auto response = client.get("http://api.example.com/users");
std::cout << response.body << std::endl;

// POST with JSON
client.setHeader("Content-Type", "application/json");
auto response = client.post("http://api.example.com/users",
                            R"({"name":"Alice","age":30})");

// With query parameters
client.addParam("page", "1");
client.addParam("limit", "10");
auto response = client.get("http://api.example.com/users");
```

## CLI Tool
```sh
# GET request
./httpclient GET https://api.github.com/users/octocat

# POST with data
./httpclient POST https://httpbin.org/post \
  -H "Content-Type: application/json" \
  -d '{"key":"value"}'

# Save response to file
./httpclient GET https://example.com/file.zip -o file.zip

# Show headers
./httpclient --verbose GET https://example.com
```

## HTTP Request Format
```
GET /path HTTP/1.1\r\n
Host: example.com\r\n
User-Agent: MyHTTPClient/1.0\r\n
Accept: */*\r\n
Connection: keep-alive\r\n
\r\n
```

## Key Concepts
- URL parsing (scheme, host, port, path)
- HTTP request/response format
- Header field parsing
- Content-Length and chunked encoding
- Status codes (2xx, 3xx, 4xx, 5xx)
- Socket programming
- DNS resolution

## Extensions
- Add HTTPS support (OpenSSL/TLS)
- Implement connection pooling
- Add progress callbacks
- Support multipart/form-data
- Implement cookie jar
- Add proxy support
- Create async/promise API
- Support HTTP/2 protocol
