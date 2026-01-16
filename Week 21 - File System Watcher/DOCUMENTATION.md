# Week 21 - File System Watcher

## English

### Overview
A file system monitoring tool that watches directories for changes (file creation, modification, deletion) and triggers actions in response. Useful for automation, backup systems, and development workflows.

### Features
- **Real-time Monitoring**: Detect file system changes instantly
- **Event Types**: Create, modify, delete, rename events
- **Recursive Watching**: Monitor subdirectories
- **Filtering**: Watch specific file types or patterns
- **Action Triggers**: Execute commands on events
- **Event Logging**: Record all detected changes

### Technical Details
- **Language**: C++
- **APIs**: inotify (Linux), ReadDirectoryChangesW (Windows)
- **Async Operations**: Non-blocking event monitoring
- **Event Queue**: Handle multiple simultaneous changes

### Use Cases
- Automated file processing
- Hot-reload development servers
- Backup synchronization
- Learning file system APIs
- Building development tools

---

## Norsk

### Oversikt
Et filsystemovervåkingsverktøy som overvåker kataloger for endringer (filoppretting, modifikasjon, sletting) og utløser handlinger som respons. Nyttig for automatisering, sikkerhetskopieringssystemer og utviklingsarbeidsflyt.

### Funksjoner
- **Sanntidsovervåking**: Detekter filsystemendringer øyeblikkelig
- **Hendelsestyper**: Opprett, endre, slett, gi nytt navn-hendelser
- **Rekursiv overvåking**: Overvåk underkataloger
- **Filtrering**: Overvåk spesifikke filtyper eller mønstre
- **Handlingsutløsere**: Utfør kommandoer på hendelser
- **Hendelseslogging**: Registrer alle oppdagede endringer

### Tekniske detaljer
- **Språk**: C++
- **APIer**: inotify (Linux), ReadDirectoryChangesW (Windows)
- **Asynkrone operasjoner**: Ikke-blokkerende hendelsesovervåking
- **Hendelseskø**: Håndter flere samtidige endringer

### Bruksområder
- Automatisert filbehandling
- Hot-reload utviklingsservere
- Sikkerhetskopieringssynkronisering
- Læring av filsystem-APIer
- Bygging av utviklingsverktøy
