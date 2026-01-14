# Week 7: INI / Config File Parser

## Project Overview
Create a parser for INI configuration files, a common format for application settings.

## Learning Objectives
- Text file parsing
- Line-by-line processing
- Key-value pair extraction
- Section management
- Type conversion and validation

## Features to Implement
- [ ] Parse sections [SectionName]
- [ ] Parse key-value pairs (key=value)
- [ ] Handle comments (; or #)
- [ ] Trim whitespace
- [ ] Support for different data types (string, int, bool, float)
- [ ] Multi-line value support
- [ ] Write/modify config files
- [ ] Nested section support (optional)
- [ ] Include directive for other files

## INI Format Example
```ini
; Application configuration
[Database]
host = localhost
port = 5432
username = admin
enabled = true

[Logging]
level = debug
file = /var/log/app.log
```

## Key Concepts
- String parsing techniques
- State machine for parsing
- Configuration management patterns
- Default values and validation

## Extensions
- Add environment variable expansion
- Implement config inheritance
- Create a fluent API for access
- Add change notification system
- Support TOML or YAML formats
