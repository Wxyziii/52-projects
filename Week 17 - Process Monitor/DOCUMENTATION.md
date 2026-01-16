# Week 17 - Process Monitor

## English

### Overview
A system monitoring tool that tracks running processes, their resource usage (CPU, memory), and provides detailed information about system activity. Similar to Task Manager or htop but custom-built.

### Features
- **Process Listing**: Show all running processes
- **Resource Monitoring**: CPU and memory usage per process
- **Real-time Updates**: Continuous monitoring
- **Process Details**: PID, name, parent process, threads
- **Filtering**: Search and filter processes
- **Kill Process**: Terminate selected processes

### Technical Details
- **Language**: C++
- **System APIs**: Windows API or Linux /proc filesystem
- **Platform-Specific**: OS-dependent implementations
- **Refresh Rate**: Configurable update intervals

### Use Cases
- System administration
- Performance troubleshooting
- Resource leak detection
- Learning OS internals
- Understanding process management

---

## Norsk

### Oversikt
Et systemovervåkingsverktøy som sporer kjørende prosesser, deres ressursbruk (CPU, minne), og gir detaljert informasjon om systemaktivitet. Lik oppgavebehandler eller htop, men tilpasset bygget.

### Funksjoner
- **Prosessliste**: Vis alle kjørende prosesser
- **Ressursovervåking**: CPU og minnebruk per prosess
- **Sanntidsoppdateringer**: Kontinuerlig overvåking
- **Prosessdetaljer**: PID, navn, foreldreprosess, tråder
- **Filtrering**: Søk og filtrer prosesser
- **Drep prosess**: Avslutt valgte prosesser

### Tekniske detaljer
- **Språk**: C++
- **System-APIer**: Windows API eller Linux /proc-filsystem
- **Plattformspesifikk**: OS-avhengige implementeringer
- **Oppdateringsrate**: Konfigurerbare oppdateringsintervaller

### Bruksområder
- Systemadministrasjon
- Ytelsesfeilsøking
- Deteksjon av ressurslekkasjer
- Læring av OS-internals
- Forståelse av prosesshåndtering
