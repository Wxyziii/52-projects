# Week 49 - Secure Backup Tool

## English

### Overview
A secure backup utility that creates encrypted, compressed backups of files and directories. Features incremental backups, versioning, and restoration capabilities for reliable data protection.

### Features
- **Encrypted Backups**: AES-256 encryption
- **Compression**: Reduce backup size
- **Incremental Backups**: Only backup changes
- **Versioning**: Keep multiple backup versions
- **Scheduling**: Automatic backup scheduling
- **Restoration**: Easy file recovery
- **Integrity Checking**: Verify backup validity
- **Cloud Support**: Upload to cloud storage

### Technical Details
- **Language**: C++
- **Encryption**: AES-256 with secure key derivation
- **Compression**: zlib, zstd, or similar
- **Storage**: Local or cloud (S3, Azure, etc.)
- **Metadata**: Track file versions and changes

### Use Cases
- Data backup and recovery
- Disaster recovery planning
- Personal file protection
- Learning encryption and compression
- Building reliable backup systems

---

## Norsk

### Oversikt
Et sikkert sikkerhetskopieringsverktøy som oppretter krypterte, komprimerte sikkerhetskopier av filer og kataloger. Inneholder inkrementelle sikkerhetskopier, versjonering og gjenopprettingsevner for pålitelig databeskyttelse.

### Funksjoner
- **Krypterte sikkerhetskopier**: AES-256-kryptering
- **Komprimering**: Reduser sikkerhetskopistørrelse
- **Inkrementelle sikkerhetskopier**: Bare sikkerhetskopier endringer
- **Versjonering**: Behold flere sikkerhetskopiversjoner
- **Planlegging**: Automatisk sikkerhetskopieringsplanlegging
- **Gjenoppretting**: Enkel filgjenoppretting
- **Integritetskontroll**: Verifiser sikkerhetskopigyldighet
- **Sky-støtte**: Last opp til skylagring

### Tekniske detaljer
- **Språk**: C++
- **Kryptering**: AES-256 med sikker nøkkelderivering
- **Komprimering**: zlib, zstd, eller lignende
- **Lagring**: Lokal eller sky (S3, Azure, etc.)
- **Metadata**: Spor filversjoner og endringer

### Bruksområder
- Datasikkerhetkopiering og gjenoppretting
- Katastrofegjenopprettingsplanlegging
- Personlig filbeskyttelse
- Læring av kryptering og komprimering
- Bygging av pålitelige sikkerhetskopieringssystemer
