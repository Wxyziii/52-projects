# Week 43 - Scripting Engine

## English

### Overview
A scripting engine that embeds a scripting language (Lua, Python, JavaScript) into a C++ application. Allows users to extend application functionality through scripts without recompiling.

### Features
- **Script Execution**: Run scripts from files or strings
- **API Binding**: Expose C++ functions to scripts
- **Variable Sharing**: Pass data between C++ and scripts
- **Error Handling**: Script error reporting
- **Sandboxing**: Limit script capabilities for security
- **Hot Reload**: Reload scripts without restart
- **Multiple Languages**: Support different scripting languages

### Technical Details
- **Language**: C++
- **Embedded Languages**: Lua, Python (pybind11), V8 (JavaScript)
- **Binding**: Function/class exposure to scripts
- **Integration**: Bi-directional communication

### Use Cases
- Game modding support
- Application customization
- Learning language embedding
- Plugin systems
- User-defined automation

---

## Norsk

### Oversikt
En skriptmotor som integrerer et skriptspråk (Lua, Python, JavaScript) i en C++-applikasjon. Lar brukere utvide applikasjonsfunksjonalitet gjennom skript uten rekompilering.

### Funksjoner
- **Skriptutførelse**: Kjør skript fra filer eller strenger
- **API-binding**: Eksponér C++-funksjoner til skript
- **Variabeldeling**: Pass data mellom C++ og skript
- **Feilhåndtering**: Skriptfeilrapportering
- **Sandboxing**: Begrens skriptevner for sikkerhet
- **Hot reload**: Last skript på nytt uten restart
- **Flere språk**: Støtte forskjellige skriptspråk

### Tekniske detaljer
- **Språk**: C++
- **Innebygde språk**: Lua, Python (pybind11), V8 (JavaScript)
- **Binding**: Funksjon/klasse-eksponering til skript
- **Integrasjon**: Toveis kommunikasjon

### Bruksområder
- Spillmoddingstøtte
- Applikasjonstilpasning
- Læring av språkinnbygging
- Plugin-systemer
- Brukerdefinert automatisering
