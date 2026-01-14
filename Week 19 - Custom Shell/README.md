# Week 19: Custom Shell

## Project Overview
Build a basic command-line shell with command execution, piping, and scripting support.

## Learning Objectives
- Process creation and management
- Standard I/O redirection
- Pipe implementation
- Command parsing
- Environment variable handling
- Signal handling

## Features to Implement
- [ ] Command prompt display
- [ ] Execute external programs
- [ ] Built-in commands (cd, exit, echo, etc.)
- [ ] Environment variable support ($VAR)
- [ ] I/O redirection (>, <, >>)
- [ ] Piping between commands (|)
- [ ] Background processes (&)
- [ ] Command history
- [ ] Tab completion
- [ ] Scripting support
- [ ] Alias support

## Usage Example
```sh
myshell> ls -la | grep txt > results.txt
myshell> echo $PATH
myshell> cd /home/user/documents
myshell> export MY_VAR=hello
myshell> gcc main.cpp -o main && ./main
myshell> find . -name "*.cpp" &
```

## Built-in Commands
```
cd <dir>          - Change directory
pwd               - Print working directory
exit [code]       - Exit shell
echo <text>       - Print text
export VAR=value  - Set environment variable
history           - Show command history
alias name=cmd    - Create command alias
jobs              - List background jobs
fg <job>          - Bring job to foreground
bg <job>          - Resume job in background
```

## Key Concepts
- fork() and exec() system calls
- Process IDs and wait()
- File descriptors and dup2()
- Pipe creation with pipe()
- Signal handling (SIGINT, SIGCHLD)
- Tokenization and parsing
- Terminal control

## Extensions
- Add job control (Ctrl+Z, fg, bg)
- Implement globbing (*.txt)
- Add command substitution $()
- Support conditionals (&&, ||)
- Create shell scripting language
- Add auto-suggestions
- Implement custom PATH handling
- Add plugin system for commands
