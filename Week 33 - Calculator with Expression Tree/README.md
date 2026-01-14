# Week 33: Calculator with Expression Tree

## Project Overview
Build an advanced calculator that uses expression trees for evaluation and symbolic manipulation.

## Learning Objectives
- Expression tree construction
- Tree traversal algorithms
- Infix/postfix conversion
- Operator precedence
- Expression simplification
- Derivative calculation

## Features to Implement
- [ ] Expression tree building
- [ ] Tree-based evaluation
- [ ] Support for +, -, *, /, ^
- [ ] Parentheses handling
- [ ] Variable support
- [ ] Expression simplification
- [ ] Symbolic differentiation
- [ ] Pretty-print expressions
- [ ] Tree visualization
- [ ] Step-by-step evaluation

## Usage Example
```cpp
ExpressionTree tree;

// Parse expression
tree.parse("(x + 2) * (x - 3)");

// Evaluate
tree.setVariable("x", 5);
double result = tree.evaluate(); // (5+2)*(5-3) = 14

// Simplify
auto simplified = tree.simplify(); // x^2 - x - 6

// Differentiate
auto derivative = tree.differentiate("x"); // 2*x - 1

// Print tree
tree.printTree();
```

## Tree Visualization
```
Expression: (x + 2) * (x - 3)

Tree Structure:
        *
       / \
      +   -
     / \ / \
    x  2 x  3

Inorder: x + 2 * x - 3
Postorder: x 2 + x 3 - *
Preorder: * + x 2 - x 3
```

## CLI Example
```sh
$ ./calculator
> (3 + 4) * 5
Result: 35

> simplify x^2 + 2*x + 2*x + 1
Result: x^2 + 4*x + 1

> diff x^3 + 2*x^2 + x
Result: 3*x^2 + 4*x + 1

> eval x^2 + 3*x + 2 where x=5
Result: 42

> tree (a+b)*(c-d)
        *
       / \
      +   -
     / \ / \
    a  b c  d
```

## Key Concepts
- Binary expression trees
- Tree traversal (inorder, preorder, postorder)
- Recursive evaluation
- Pattern matching for simplification
- Derivative rules implementation
- Node types (operator, operand, variable)

## Extensions
- Add trigonometric functions
- Implement integration
- Add equation solving
- Create graphing capability
- Implement complex numbers
- Add matrix operations
- Create LaTeX export
- Implement CSE optimization
