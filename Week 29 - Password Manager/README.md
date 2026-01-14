# Week 29: Password Manager

## Project Overview
Build a secure password manager for storing and managing login credentials with encryption.

## Learning Objectives
- Secure credential storage
- Encryption implementation
- Password generation
- Clipboard security
- Auto-fill mechanisms
- Secure memory handling

## Features to Implement
- [ ] Master password protection
- [ ] AES-256 encryption
- [ ] Add/edit/delete credentials
- [ ] Password generator
- [ ] Search functionality
- [ ] Categories/folders
- [ ] Password strength meter
- [ ] Clipboard auto-clear
- [ ] Export/import (encrypted)
- [ ] Two-factor authentication
- [ ] Browser integration (optional)

## Usage Example
```sh
# Initialize password manager
./passman init

# Add new credential
./passman add \
  --name "GitHub" \
  --username "alice" \
  --url "https://github.com" \
  --generate

# List all entries
./passman list

# Get password (copy to clipboard)
./passman get GitHub

# Search entries
./passman search git
```

## Interactive Mode
```
╔════════════════════════════════════════════╗
║         Password Manager v1.0              ║
╠════════════════════════════════════════════╣
║ Entries: 23                                ║
╠════════════════════════════════════════════╣
║ 1. GitHub          alice@example.com       ║
║ 2. Gmail           alice@gmail.com         ║
║ 3. AWS Console     admin                   ║
║ 4. Database        root                    ║
╠════════════════════════════════════════════╣
║ [A]dd [E]dit [D]elete [G]enerate [Q]uit   ║
╚════════════════════════════════════════════╝
```

## Password Generator
```cpp
PasswordGenerator gen;
gen.setLength(16);
gen.includeUppercase(true);
gen.includeLowercase(true);
gen.includeNumbers(true);
gen.includeSymbols(true);

std::string password = gen.generate();
// Result: "Kj9#mP2$xL5&nQ8!"

int strength = gen.calculateStrength(password);
// Strength: 85/100 (Strong)
```

## Key Concepts
- AES-GCM encryption
- Key derivation (Argon2)
- Secure password generation
- Entropy calculation
- Secure memory wiping
- Time-based one-time passwords (TOTP)
- Clipboard security

## Extensions
- Add biometric authentication
- Implement password sharing
- Create browser extension
- Add breach monitoring
- Implement secure notes
- Add file attachments
- Create emergency access
- Implement cloud sync
