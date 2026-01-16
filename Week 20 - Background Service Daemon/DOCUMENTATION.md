# Week 20 - Background Service Daemon

## English

### Overview
A background service or daemon that runs continuously, performing tasks automatically without user interaction. Examples include scheduled tasks, file monitoring, or periodic data processing.

### Features
- **Daemonization**: Run as background process
- **Service Management**: Start, stop, restart functionality
- **Logging**: Comprehensive activity logs
- **Configuration**: Read settings from config files
- **Scheduled Tasks**: Execute tasks at specific intervals
- **Signal Handling**: Graceful shutdown on system signals
- **Auto-restart**: Recovery from crashes

### Technical Details
- **Language**: C++
- **Platform**: Windows Service or Linux daemon
- **APIs**: Service Control Manager (Windows) or systemd (Linux)
- **IPC**: Inter-process communication for control

### Use Cases
- System monitoring services
- Scheduled maintenance tasks
- Log rotation and cleanup
- Learning service architecture
- Understanding daemon processes

---

## Norsk

### Oversikt
En bakgrunnstjeneste eller daemon som kjører kontinuerlig, og utfører oppgaver automatisk uten brukerinteraksjon. Eksempler inkluderer planlagte oppgaver, filovervåking eller periodisk databehandling.

### Funksjoner
- **Daemonisering**: Kjør som bakgrunnsprosess
- **Tjenestehåndtering**: Start, stopp, restart-funksjonalitet
- **Logging**: Omfattende aktivitetslogger
- **Konfigurasjon**: Les innstillinger fra konfigurasjonsfiler
- **Planlagte oppgaver**: Utfør oppgaver ved spesifikke intervaller
- **Signalhåndtering**: Grasiøs nedstengning på systemsignaler
- **Auto-restart**: Gjenoppretting fra krasj

### Tekniske detaljer
- **Språk**: C++
- **Plattform**: Windows Service eller Linux daemon
- **APIer**: Service Control Manager (Windows) eller systemd (Linux)
- **IPC**: Inter-prosesskommunikasjon for kontroll

### Bruksområder
- Systemovervåkingstjenester
- Planlagte vedlikeholdsoppgaver
- Loggrotasjon og opprydding
- Læring av tjenestearkitektur
- Forståelse av daemon-prosesser
