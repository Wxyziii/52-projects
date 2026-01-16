# Week 13 - Multi-Threaded File Copier

## English

### Overview
A high-performance file copying utility that uses multiple threads to copy files in parallel. Significantly faster than single-threaded copying, especially for large files or multiple files across different drives.

### Features
- **Parallel File Copying**: Multiple files copied simultaneously
- **Chunked Copying**: Large files split into chunks for parallel processing
- **Progress Tracking**: Real-time progress for each file
- **Error Handling**: Resume capability on failures
- **Speed Metrics**: Display transfer rates and ETA
- **Thread Pool**: Configurable number of worker threads

### Technical Details
- **Language**: C++
- **Threading**: std::thread with synchronization
- **File I/O**: Binary file operations
- **Buffer Management**: Efficient memory usage

### Use Cases
- Fast backup operations
- Large file transfers
- Batch file copying
- Learning parallel I/O operations
- Understanding concurrency benefits

---

## Norsk

### Oversikt
Et høyytelsesfilkopieringsverktøy som bruker flere tråder for å kopiere filer parallelt. Betydelig raskere enn entrådet kopiering, spesielt for store filer eller flere filer på tvers av forskjellige stasjoner.

### Funksjoner
- **Parallel filkopiering**: Flere filer kopiert samtidig
- **Chunked kopiering**: Store filer delt i biter for parallell behandling
- **Fremdriftssporing**: Sanntidsfremdrift for hver fil
- **Feilhåndtering**: Gjenopptakelsesevne ved feil
- **Hastighetsmålinger**: Vis overføringshastigheter og ETA
- **Trådpool**: Konfigurerbart antall arbeidstråder

### Tekniske detaljer
- **Språk**: C++
- **Tråding**: std::thread med synkronisering
- **Fil I/O**: Binære filoperasjoner
- **Bufferstyring**: Effektiv minnebruk

### Bruksområder
- Raske sikkerhetskopieringsoperasjoner
- Store filoverføringer
- Batch-filkopiering
- Læring av parallelle I/O-operasjoner
- Forståelse av samtidighetsfordeler
