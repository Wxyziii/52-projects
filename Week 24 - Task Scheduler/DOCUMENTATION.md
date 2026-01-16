# Week 24 - Task Scheduler

## English

### Overview
A task scheduling system that executes commands or scripts at specified times or intervals. Similar to cron on Linux or Task Scheduler on Windows, but custom-built with flexible scheduling options.

### Features
- **Time-based Scheduling**: Run tasks at specific times
- **Recurring Tasks**: Daily, weekly, monthly schedules
- **Cron-like Syntax**: Flexible scheduling expressions
- **Task Management**: Add, remove, list scheduled tasks
- **Execution Logging**: Track task execution history
- **Error Handling**: Retry failed tasks

### Technical Details
- **Language**: C++
- **Timing**: std::chrono for time management
- **Persistence**: Save schedules to file
- **Execution**: Process spawning for task execution

### Use Cases
- Automated backups
- Periodic data processing
- System maintenance tasks
- Learning scheduling algorithms
- Understanding time-based automation

---

## Norsk

### Oversikt
Et oppgaveplanleggingssystem som utfører kommandoer eller skript på spesifiserte tidspunkter eller intervaller. Lik cron på Linux eller Task Scheduler på Windows, men tilpasset bygget med fleksible planleggingsalternativer.

### Funksjoner
- **Tidsbasert planlegging**: Kjør oppgaver på spesifikke tidspunkter
- **Tilbakevendende oppgaver**: Daglige, ukentlige, månedlige planer
- **Cron-lignende syntaks**: Fleksible planleggingsuttrykk
- **Oppgavehåndtering**: Legg til, fjern, list planlagte oppgaver
- **Utførelseslogging**: Spor oppgaveutførelseshistorikk
- **Feilhåndtering**: Prøv mislykkede oppgaver på nytt

### Tekniske detaljer
- **Språk**: C++
- **Timing**: std::chrono for tidshåndtering
- **Persistens**: Lagre tidsplaner til fil
- **Utførelse**: Prosess-spawning for oppgaveutførelse

### Bruksområder
- Automatiserte sikkerhetskopier
- Periodisk databehandling
- Systemvedlikeholdsoppgaver
- Læring av planleggingsalgoritmer
- Forståelse av tidsbasert automatisering
