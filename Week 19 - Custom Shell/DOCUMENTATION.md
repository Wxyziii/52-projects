# Week 19 - Custom Shell

## English

### Overview
A custom command-line shell that interprets and executes user commands, similar to bash, cmd, or PowerShell. Implements command parsing, process execution, pipes, redirections, and built-in commands.

### Features
- **Command Execution**: Run external programs
- **Built-in Commands**: cd, echo, pwd, exit, etc.
- **Pipes**: Chain commands with | operator
- **Redirections**: Input/output redirection (>, <, >>)
- **Environment Variables**: Get and set variables
- **Command History**: Navigate previous commands
- **Script Support**: Execute shell scripts

### Technical Details
- **Language**: C++
- **Process Management**: fork/exec on Linux, CreateProcess on Windows
- **Parsing**: Tokenization and command parsing
- **I/O Redirection**: File descriptor manipulation

### Use Cases
- Learning OS process management
- Understanding shell internals
- Custom automation environment
- Educational tool for teaching Unix concepts
- Building custom CLI tools

---

## Norsk

### Oversikt
Et tilpasset kommandolinje-shell som tolker og utfører brukerkommandoer, lik bash, cmd eller PowerShell. Implementerer kommandoparsing, prosessutførelse, pipes, omdirigeringer og innebygde kommandoer.

### Funksjoner
- **Kommandoutførelse**: Kjør eksterne programmer
- **Innebygde kommandoer**: cd, echo, pwd, exit, etc.
- **Pipes**: Lenk kommandoer med |-operatør
- **Omdirigeringer**: Inn/ut-omdirigering (>, <, >>)
- **Miljøvariabler**: Hent og sett variabler
- **Kommandohistorikk**: Naviger tidligere kommandoer
- **Skriptstøtte**: Utfør shell-skript

### Tekniske detaljer
- **Språk**: C++
- **Prosesshåndtering**: fork/exec på Linux, CreateProcess på Windows
- **Parsing**: Tokenisering og kommandoparsing
- **I/O-omdirigering**: Fildeskriptormanipulering

### Bruksområder
- Læring av OS-prosesshåndtering
- Forståelse av shell-internals
- Tilpasset automatiseringsmiljø
- Undervisningsverktøy for å lære Unix-konsepter
- Bygging av tilpassede CLI-verktøy
