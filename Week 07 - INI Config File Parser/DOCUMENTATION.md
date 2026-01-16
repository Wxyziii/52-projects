# Week 07 - INI Config File Parser

## English

### Overview
A parser for INI configuration files that reads, writes, and manages application settings. INI files are simple text-based configuration files commonly used in Windows and cross-platform applications.

### Features
- **Read INI Files**: Parse sections, keys, and values
- **Write Configuration**: Save settings back to INI files
- **Section Management**: Organize settings into logical sections
- **Key-Value Access**: Simple API to get/set configuration values
- **Comment Support**: Preserve and handle comments
- **Type Conversion**: Automatic conversion to strings, integers, booleans

### Technical Details
- **Language**: C++
- **File Format**: Standard INI format (sections, key=value pairs)
- **Parsing**: Line-by-line text processing
- **Data Structure**: Nested maps (section → key → value)

### Use Cases
- Application configuration management
- User preferences storage
- Game settings files
- Cross-platform configuration
- Learning file format parsing

---

## Norsk

### Oversikt
En parser for INI-konfigurasjonsfiler som leser, skriver og håndterer applikasjonsinnstillinger. INI-filer er enkle tekstbaserte konfigurasjonsfiler som ofte brukes i Windows og kryssplattformapplikasjoner.

### Funksjoner
- **Les INI-filer**: Parse seksjoner, nøkler og verdier
- **Skriv konfigurasjon**: Lagre innstillinger tilbake til INI-filer
- **Seksjonshåndtering**: Organiser innstillinger i logiske seksjoner
- **Nøkkel-verdi-tilgang**: Enkel API for å hente/sette konfigurasjonsverdier
- **Kommentarstøtte**: Bevar og håndter kommentarer
- **Typekonvertering**: Automatisk konvertering til strenger, heltall, boolske verdier

### Tekniske detaljer
- **Språk**: C++
- **Filformat**: Standard INI-format (seksjoner, nøkkel=verdi-par)
- **Parsing**: Linje-for-linje tekstbehandling
- **Datastruktur**: Nestede maps (seksjon → nøkkel → verdi)

### Bruksområder
- Applikasjonskonfigurasjonshåndtering
- Lagring av brukerpreferanser
- Spillinnstillingsfiler
- Kryssplattformkonfigurasjon
- Læring av filformatparsing
