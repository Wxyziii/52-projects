# Week 16: Expression Parser & Evaluator

## Project Overview
Create a parser and evaluator for mathematical expressions with support for operators, functions, and variables.

## Learning Objectives
- Lexical analysis and tokenization
- Parsing algorithms (recursive descent, Shunting Yard)
- Abstract Syntax Tree (AST) construction
- Operator precedence handling
- Expression evaluation
- Error reporting

## Features to Implement
- [ ] Tokenizer for math expressions
- [ ] Operator precedence parsing
- [ ] Support for +, -, *, /, ^, %
- [ ] Parentheses handling
- [ ] Mathematical functions (sin, cos, sqrt, log, etc.)
- [ ] Variable support
- [ ] Expression simplification
- [ ] Error messages with position
- [ ] Scientific notation
- [ ] Unary operators (+, -)

## Usage Example
```cpp
ExpressionEvaluator eval;

// Simple expression
double result = eval.evaluate("2 + 3 * 4"); // 14

// With functions
result = eval.evaluate("sqrt(16) + sin(0)"); // 4

// With variables
eval.setVariable("x", 5);
result = eval.evaluate("x^2 + 2*x + 1"); // 36
```

## Supported Features
```
Operators: + - * / ^ % ( )
Functions: sin, cos, tan, sqrt, log, ln, abs, ceil, floor
Variables: x, y, z, custom names
Examples:
  3 + 4 * 2           → 11
  (3 + 4) * 2         → 14
  sin(pi / 2)         → 1
  2^3 + sqrt(16)      → 12
  x^2 - 2*x + 1       → (x-1)^2
```

## Key Concepts
- Shunting Yard algorithm
- Recursive descent parsing
- Infix to postfix conversion
- AST traversal
- Operator associativity
- Token types and precedence

## Extensions
- Add symbolic differentiation
- Implement expression simplification
- Support complex numbers
- Add matrix operations
- Create graphing capability
- Implement LaTeX output
- Add user-defined functions
- Support logical operators
