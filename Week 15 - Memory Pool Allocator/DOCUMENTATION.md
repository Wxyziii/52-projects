# Week 15 - Memory Pool Allocator

## English

### Overview
A custom memory allocator that pre-allocates a large block of memory and manages smaller allocations from this pool. Reduces fragmentation and improves performance by avoiding frequent system memory calls.

### Features
- **Pre-allocation**: Large memory block allocated upfront
- **Fast Allocation**: O(1) allocation and deallocation
- **Reduced Fragmentation**: Better memory layout
- **Fixed or Variable Size**: Support different allocation strategies
- **Memory Tracking**: Monitor usage and detect leaks
- **Thread-Safe Option**: Concurrent allocation support

### Technical Details
- **Language**: C++
- **Strategy**: Free-list or bitmap-based allocation
- **Alignment**: Proper memory alignment handling
- **Complexity**: O(1) for allocation/deallocation

### Use Cases
- Game engines (frequent small allocations)
- Real-time systems
- Performance-critical applications
- Learning memory management
- Understanding allocator design

---

## Norsk

### Oversikt
En tilpasset minneallokator som pre-allokerer en stor minneblokk og håndterer mindre allokeringer fra denne poolen. Reduserer fragmentering og forbedrer ytelsen ved å unngå hyppige systemminne-anrop.

### Funksjoner
- **Pre-allokering**: Stor minneblokk allokert på forhånd
- **Rask allokering**: O(1) allokering og deallokering
- **Redusert fragmentering**: Bedre minneoppsett
- **Fast eller variabel størrelse**: Støtte forskjellige allokeringsstrategier
- **Minnesporing**: Overvåk bruk og detekter lekkasjer
- **Trådsikker opsjon**: Samtidig allokeringsstøtte

### Tekniske detaljer
- **Språk**: C++
- **Strategi**: Free-list eller bitmap-basert allokering
- **Justering**: Riktig håndtering av minnejustering
- **Kompleksitet**: O(1) for allokering/deallokering

### Bruksområder
- Spillmotorer (hyppige små allokeringer)
- Sanntidssystemer
- Ytelseskritiske applikasjoner
- Læring av minnehåndtering
- Forståelse av allokeringsdesign
