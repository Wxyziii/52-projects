# Week 44 - Dependency Injection Container

## English

### Overview
A dependency injection (DI) container that manages object creation and lifetime. Implements inversion of control (IoC) principle for loosely coupled, testable, and maintainable C++ code.

### Features
- **Service Registration**: Register types and implementations
- **Automatic Resolution**: Resolve dependencies automatically
- **Lifetime Management**: Singleton, transient, scoped lifetimes
- **Constructor Injection**: Auto-inject dependencies
- **Interface Binding**: Map interfaces to implementations
- **Factory Support**: Custom object creation
- **Circular Dependency Detection**: Prevent dependency cycles

### Technical Details
- **Language**: C++
- **Templates**: Heavy template metaprogramming
- **Patterns**: Factory, singleton, registry patterns
- **RTTI**: Runtime type information usage

### Use Cases
- Large application architecture
- Testable code design
- Learning design patterns
- Understanding IoC/DI
- Enterprise software development

---

## Norsk

### Oversikt
En avhengighetsinjeksjonsbeholder (DI) som håndterer objektopprettelse og levetid. Implementerer inversjons-av-kontroll (IoC) prinsippet for løst koblet, testbar og vedlikeholdbar C++-kode.

### Funksjoner
- **Tjenesteregistrering**: Registrer typer og implementeringer
- **Automatisk resolusjon**: Løs avhengigheter automatisk
- **Levetidshåndtering**: Singleton, transient, scoped levetider
- **Konstruktørinjeksjon**: Auto-injiser avhengigheter
- **Grensesnittbinding**: Koble grensesnitt til implementeringer
- **Fabrikk-støtte**: Tilpasset objektopprettelse
- **Sirkulær avhengighetsdeteksjon**: Forhindre avhengighetssykluser

### Tekniske detaljer
- **Språk**: C++
- **Maler**: Tung malmetaprogrammering
- **Mønstre**: Factory, singleton, registry-mønstre
- **RTTI**: Kjøretids typeinformasjonsbruk

### Bruksområder
- Stor applikasjonsarkitektur
- Testbar kodedesign
- Læring av designmønstre
- Forståelse av IoC/DI
- Bedriftsprogramvareutvikling
