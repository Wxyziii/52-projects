# Week 47: Cross-Platform Password Manager (Full)

## Project Overview
Build a full-featured, cross-platform password manager with GUI, encryption, cloud sync, and browser integration.

## Learning Objectives
- Complete application architecture
- Secure credential storage
- Cross-platform GUI development
- Browser extension integration
- Cloud synchronization
- End-to-end encryption

## Features to Implement
- [ ] Master password with 2FA
- [ ] AES-256-GCM encryption
- [ ] Add/edit/delete credentials
- [ ] Password generator with policies
- [ ] Search and filtering
- [ ] Categories and tags
- [ ] Secure notes
- [ ] File attachments
- [ ] Browser extension integration
- [ ] Cloud sync (encrypted)
- [ ] Import/export (1Password, LastPass, etc.)
- [ ] Password health audit
- [ ] Breach monitoring
- [ ] Auto-fill functionality
- [ ] Secure sharing

## Architecture
```
┌─────────────────────────────────────┐
│         GUI Layer (Qt/wxWidgets)    │
├─────────────────────────────────────┤
│         Application Logic           │
│  - Credential Manager               │
│  - Password Generator               │
│  - Sync Manager                     │
├─────────────────────────────────────┤
│         Security Layer              │
│  - Encryption (AES-256-GCM)         │
│  - Key Derivation (Argon2)          │
│  - TOTP Generator                   │
├─────────────────────────────────────┤
│         Storage Layer               │
│  - Local Database (SQLite)          │
│  - Cloud Storage API                │
├─────────────────────────────────────┤
│      Browser Extension (Optional)   │
│  - Chrome/Firefox Extension         │
│  - Native Messaging Host            │
└─────────────────────────────────────┘
```

## Main Window UI
```
╔════════════════════════════════════════════════════╗
║ 🔐 Password Manager                    [_][□][×] ║
╠════════════════════════════════════════════════════╣
║ [+New] [🔍Search] [⚙️Settings]           👤 Alice  ║
╠═══════════════════╦════════════════════════════════╣
║ 📁 All Items (87) ║ GitHub                         ║
║ ⭐ Favorites (12) ║ https://github.com             ║
║                   ║ alice@example.com              ║
║ 📂 Categories     ║ ••••••••••••                   ║
║   💼 Work (23)    ║                                ║
║   🏠 Personal(45) ║ Created: 2025-12-15            ║
║   💳 Banking (8)  ║ Modified: 2026-01-10           ║
║   🎮 Gaming (11)  ║                                ║
║                   ║ 🏷️ Tags: important, dev        ║
║ 🗂️ Types          ║                                ║
║   🔐 Logins       ║ [Edit] [Copy User] [Copy Pass] ║
║   💳 Cards        ║ [Launch URL] [Delete]          ║
║   📝 Notes        ║                                ║
╠═══════════════════╩════════════════════════════════╣
║ 🔒 Locked | Last sync: 2 mins ago | Health: ⚠️ 3   ║
╚════════════════════════════════════════════════════╝
```

## Core Classes
```cpp
class PasswordManager {
    VaultDatabase vault_;
    Encryptor encryptor_;
    SyncManager syncManager_;
    
public:
    bool unlock(const std::string& masterPassword);
    void lock();
    
    Credential addCredential(const Credential& cred);
    void updateCredential(const Credential& cred);
    void deleteCredential(const std::string& id);
    
    std::vector<Credential> search(
        const std::string& query);
    
    void enableSync(const CloudProvider& provider);
    void sync();
    
    HealthReport auditPasswords();
    std::vector<Breach> checkBreaches();
};

class Encryptor {
public:
    void setMasterKey(const std::string& password);
    std::string encrypt(const std::string& plaintext);
    std::string decrypt(const std::string& ciphertext);
    
private:
    std::vector<uint8_t> deriveKey(
        const std::string& password,
        const std::vector<uint8_t>& salt);
};

class BrowserExtension {
public:
    void registerNativeHost();
    void handleMessage(const json& msg);
    void autoFill(const Credential& cred);
};
```

## Database Schema
```sql
CREATE TABLE credentials (
    id TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    username TEXT,
    password_encrypted BLOB,
    url TEXT,
    notes_encrypted BLOB,
    category TEXT,
    tags TEXT,
    created_at INTEGER,
    modified_at INTEGER,
    last_used_at INTEGER
);

CREATE TABLE attachments (
    id TEXT PRIMARY KEY,
    credential_id TEXT,
    filename TEXT,
    data_encrypted BLOB,
    FOREIGN KEY(credential_id) 
        REFERENCES credentials(id)
);

CREATE TABLE audit_log (
    id INTEGER PRIMARY KEY,
    action TEXT,
    timestamp INTEGER,
    details TEXT
);
```

## Key Concepts
- Zero-knowledge architecture
- End-to-end encryption
- Key derivation (Argon2)
- Secure memory handling
- TOTP implementation
- OAuth for cloud sync
- Native messaging protocol
- Password strength analysis

## Extensions
- Add biometric authentication
- Implement secure sharing
- Create mobile apps (iOS/Android)
- Add emergency access
- Implement password inheritance
- Create CLI interface
- Add hardware key support (YubiKey)
- Implement offline mode
