# Week 45: Static Code Analyzer

## Project Overview
Build a basic static analysis tool that checks C++ code for common issues, style violations, and potential bugs.

## Learning Objectives
- Abstract Syntax Tree (AST) parsing
- Code pattern recognition
- Rule-based analysis
- Clang/LLVM integration
- Error reporting
- Code metrics calculation

## Features to Implement
- [ ] Parse C++ source files
- [ ] Detect common code smells
- [ ] Check naming conventions
- [ ] Find unused variables/functions
- [ ] Detect potential null dereferences
- [ ] Check for memory leaks
- [ ] Cyclomatic complexity calculation
- [ ] Dead code detection
- [ ] Rule configuration (YAML/JSON)
- [ ] HTML/JSON report generation

## Usage Example
```sh
# Analyze single file
./analyzer main.cpp

# Analyze directory
./analyzer src/ --recursive

# With specific rules
./analyzer src/ --rules style,security

# Generate report
./analyzer src/ --report html -o report.html

# Show metrics
./analyzer src/ --metrics
```

## Detection Rules
```cpp
class Analyzer {
    std::vector<Rule*> rules_;
    
public:
    void analyze(const SourceFile& file) {
        AST ast = parseFile(file);
        
        for (auto* rule : rules_) {
            auto violations = rule->check(ast);
            reportViolations(violations);
        }
    }
};

// Example rule: Detect unused variables
class UnusedVariableRule : public Rule {
public:
    std::vector<Violation> check(const AST& ast) override {
        std::vector<Violation> violations;
        
        for (const auto& var : ast.getVariables()) {
            if (var.usageCount == 0) {
                violations.push_back({
                    Severity::Warning,
                    var.location,
                    "Unused variable: " + var.name
                });
            }
        }
        
        return violations;
    }
};
```

## Output Example
```
Analyzing: src/main.cpp
  Warning [line 15]: Unused variable 'count'
  Error [line 23]: Potential null dereference
  Warning [line 45]: Function too complex (CC: 15)
  Info [line 67]: Consider using 'auto' keyword

Analyzing: src/utils.cpp
  Warning [line 8]: Non-const reference parameter
  Error [line 34]: Memory leak detected

Summary:
  Files analyzed: 2
  Errors: 2
  Warnings: 4
  Info: 1
  
Metrics:
  Total lines: 1,234
  Code lines: 856
  Comment lines: 234
  Blank lines: 144
  Average CC: 4.2
```

## Checks to Implement
```yaml
# analyzer.yaml
rules:
  naming:
    - class_names: PascalCase
    - function_names: camelCase
    - variable_names: snake_case
    - constants: UPPER_CASE
    
  style:
    - max_line_length: 120
    - max_function_length: 50
    - max_params: 5
    - require_braces: true
    
  complexity:
    - max_cyclomatic_complexity: 10
    - max_nesting_depth: 4
    
  security:
    - no_gets: true
    - no_strcpy: true
    - check_buffer_overflow: true
    
  performance:
    - pass_by_const_ref: true
    - avoid_copies: true
```

## Clang LibTooling Integration
```cpp
class AnalyzerAction : 
    public clang::ASTFrontendAction {
public:
    std::unique_ptr<clang::ASTConsumer> 
    CreateASTConsumer(clang::CompilerInstance& CI,
                      StringRef file) override {
        return std::make_unique<AnalyzerConsumer>();
    }
};

class AnalyzerConsumer : 
    public clang::ASTConsumer {
public:
    void HandleTranslationUnit(
        clang::ASTContext& Context) override {
        
        auto* TU = Context.getTranslationUnitDecl();
        AnalyzerVisitor visitor;
        visitor.TraverseDecl(TU);
    }
};
```

## Key Concepts
- Abstract Syntax Tree (AST)
- Clang/LLVM LibTooling
- Control flow graph analysis
- Data flow analysis
- Pattern matching
- Cyclomatic complexity
- Rule engines

## Extensions
- Add custom rule creation
- Implement auto-fix suggestions
- Create IDE integration
- Add incremental analysis
- Implement interprocedural analysis
- Create CI/CD integration
- Add machine learning detection
- Implement security scanning
