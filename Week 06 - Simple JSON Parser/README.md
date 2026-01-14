# Week 6: Simple JSON Parser

## Project Overview
Build a JSON parser from scratch without external libraries to understand parsing techniques and data representation.

## Learning Objectives
- Lexical analysis and tokenization
- Recursive descent parsing
- Abstract Syntax Tree (AST) construction
- String processing and escape sequences
- Error handling and reporting

## Features to Implement
- [ ] Tokenizer/Lexer
- [ ] Parser for JSON syntax
- [ ] Support for objects, arrays, strings, numbers, booleans, null
- [ ] Nested structure handling
- [ ] Unicode escape sequence support
- [ ] Pretty-print JSON output
- [ ] Error messages with line/column numbers
- [ ] JSON serialization (object to JSON string)

## JSON Elements to Support
```json
{
  "string": "value",
  "number": 123.45,
  "boolean": true,
  "null": null,
  "array": [1, 2, 3],
  "object": {"nested": "value"}
}
```

## Key Concepts
- Context-free grammars
- Recursive descent parsing
- Variant types / sum types
- Memory-efficient data structures

## Extensions
- Add JSON Path query support
- Implement streaming parser for large files
- Add JSON Schema validation
- Create a JSON diff tool
- Support for comments (non-standard)
