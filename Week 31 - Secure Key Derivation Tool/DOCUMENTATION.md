# Week 31 - Secure Key Derivation Tool

## English

### Overview
A cryptographic key derivation tool that converts passwords into secure encryption keys using algorithms like PBKDF2, Argon2, or scrypt. Essential for secure password-based encryption systems.

### Features
- **Multiple Algorithms**: PBKDF2, Argon2, scrypt support
- **Configurable Parameters**: Iterations, memory, parallelism
- **Salt Generation**: Secure random salt creation
- **Key Stretching**: Slow down brute-force attacks
- **Output Formats**: Hex, Base64 encoding
- **Benchmark Mode**: Compare algorithm performance

### Technical Details
- **Language**: C++
- **Algorithms**: PBKDF2-SHA256, Argon2id, scrypt
- **Libraries**: OpenSSL, libsodium
- **Security**: Constant-time comparison

### Use Cases
- Password-based encryption
- Learning key derivation
- Understanding cryptographic security
- Building secure systems
- Password hashing

---

## Norsk

### Oversikt
Et kryptografisk nøkkelderiveringsverktøy som konverterer passord til sikre krypteringsnøkler ved hjelp av algoritmer som PBKDF2, Argon2 eller scrypt. Essensielt for sikre passordbaserte krypteringssystemer.

### Funksjoner
- **Flere algoritmer**: PBKDF2, Argon2, scrypt-støtte
- **Konfigurerbare parametere**: Iterasjoner, minne, parallellisme
- **Salt-generering**: Sikker tilfeldig salt-opprettelse
- **Nøkkelstrekning**: Bremse brute-force-angrep
- **Utdataformater**: Hex, Base64-koding
- **Benchmark-modus**: Sammenlign algoritmeprestasjon

### Tekniske detaljer
- **Språk**: C++
- **Algoritmer**: PBKDF2-SHA256, Argon2id, scrypt
- **Biblioteker**: OpenSSL, libsodium
- **Sikkerhet**: Konstant-tids sammenligning

### Bruksområder
- Passordbasert kryptering
- Læring av nøkkelderivering
- Forståelse av kryptografisk sikkerhet
- Bygging av sikre systemer
- Passord-hashing
