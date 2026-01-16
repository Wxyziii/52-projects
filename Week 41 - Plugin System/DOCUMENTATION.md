# Week 41 - Plugin System

## English

### Overview
A plugin architecture that allows loading external modules at runtime to extend application functionality. Uses dynamic libraries (DLLs/shared objects) for modular, extensible software design.

### Features
- **Dynamic Loading**: Load plugins at runtime
- **Plugin Discovery**: Auto-detect plugins in folders
- **Plugin API**: Standardized interface for plugins
- **Version Checking**: Ensure plugin compatibility
- **Enable/Disable**: Toggle plugins without restart
- **Plugin Metadata**: Name, version, author info
- **Dependency Management**: Handle plugin dependencies

### Technical Details
- **Language**: C++
- **Loading**: dlopen (Linux), LoadLibrary (Windows)
- **Interface**: Abstract base classes or C API
- **Build**: Separate compilation for plugins

### Use Cases
- Extensible applications
- Modular software architecture
- Learning dynamic linking
- Plugin-based systems
- Third-party extensions

---

## Norsk

### Oversikt
En plugin-arkitektur som tillater lasting av eksterne moduler ved kjøretid for å utvide applikasjonsfunksjonalitet. Bruker dynamiske biblioteker (DLLer/delte objekter) for modulær, utvidbar programvaredesign.

### Funksjoner
- **Dynamisk lasting**: Last plugins ved kjøretid
- **Plugin-oppdagelse**: Auto-detekter plugins i mapper
- **Plugin-API**: Standardisert grensesnitt for plugins
- **Versjonssjekking**: Sikre plugin-kompatibilitet
- **Aktiver/deaktiver**: Veksle plugins uten restart
- **Plugin-metadata**: Navn, versjon, forfatterinfo
- **Avhengighetshåndtering**: Håndter plugin-avhengigheter

### Tekniske detaljer
- **Språk**: C++
- **Lasting**: dlopen (Linux), LoadLibrary (Windows)
- **Grensesnitt**: Abstrakte baseklasser eller C API
- **Bygg**: Separat kompilering for plugins

### Bruksområder
- Utvidbare applikasjoner
- Modulær programvarearkitektur
- Læring av dynamisk linking
- Plugin-baserte systemer
- Tredjepartutvidelser
