# Week 30 - Two-Factor Authentication Generator

## English

### Overview
A two-factor authentication (2FA) token generator that creates time-based one-time passwords (TOTP) compatible with services like Google Authenticator. Enhances account security with second factor authentication.

### Features
- **TOTP Generation**: Time-based one-time passwords
- **QR Code Scanning**: Import accounts via QR codes
- **Multiple Accounts**: Manage 2FA for multiple services
- **Time Synchronization**: Accurate time-based tokens
- **Backup Codes**: Export/import account secrets
- **Countdown Timer**: Shows token validity period

### Technical Details
- **Language**: C++
- **Algorithm**: HMAC-SHA1 based TOTP (RFC 6238)
- **Time Source**: System time with NTP sync
- **Encoding**: Base32 secret key encoding

### Use Cases
- Enhancing account security
- Learning authentication systems
- Understanding TOTP/HOTP
- Building security tools
- Multi-factor authentication

---

## Norsk

### Oversikt
En to-faktor autentiseringsgenerator (2FA) som lager tidsbaserte engangspassord (TOTP) kompatible med tjenester som Google Authenticator. Forbedrer kontosikkerhet med andrefaltor-autentisering.

### Funksjoner
- **TOTP-generering**: Tidsbaserte engangspassord
- **QR-kodeskanning**: Importer kontoer via QR-koder
- **Flere kontoer**: Håndter 2FA for flere tjenester
- **Tidssynkronisering**: Nøyaktige tidsbaserte tokens
- **Sikkerhetskopikoder**: Eksporter/importer kontohemmeligheter
- **Nedtellingstimer**: Viser token-gyldighetperiode

### Tekniske detaljer
- **Språk**: C++
- **Algoritme**: HMAC-SHA1-basert TOTP (RFC 6238)
- **Tidskilde**: Systemtid med NTP-synk
- **Koding**: Base32 hemmelig nøkkelkoding

### Bruksområder
- Forbedring av kontosikkerhet
- Læring av autentiseringssystemer
- Forståelse av TOTP/HOTP
- Bygging av sikkerhetsverktøy
- Multifaktor-autentisering
