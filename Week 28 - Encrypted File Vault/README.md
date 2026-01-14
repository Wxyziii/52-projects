# Week 28: Encrypted File Vault

## Project Overview
Create a secure file storage system with encryption for protecting sensitive files.

## Learning Objectives
- Cryptography fundamentals (AES, RSA)
- Key derivation (PBKDF2, Argon2)
- Secure file handling
- Password hashing
- Metadata protection
- Memory security

## Features to Implement
- [ ] AES-256 file encryption
- [ ] Password-based key derivation
- [ ] Secure vault creation
- [ ] Add/remove files from vault
- [ ] File integrity verification (HMAC)
- [ ] Encrypted filename storage
- [ ] Master password protection
- [ ] Key file support
- [ ] Automatic encryption on save
- [ ] Secure file deletion (shredding)

## Usage Example
```sh
# Create new vault
./vault create myvault.vault --password

# Add file to vault
./vault add myvault.vault secret.txt

# List files in vault
./vault list myvault.vault

# Extract file
./vault extract myvault.vault secret.txt -o decrypted.txt

# Change password
./vault passwd myvault.vault
```

## API Usage
```cpp
Vault vault("myvault.vault");

// Create and unlock
vault.create("strong_password");
vault.unlock("strong_password");

// Add encrypted file
vault.addFile("secret.txt");
vault.addFile("important.pdf", "documents/");

// Extract file
vault.extractFile("secret.txt", "output.txt");

// Lock vault
vault.lock();
```

## Vault Structure
```
Vault Format:
┌────────────────────────────┐
│ Header (Magic, Version)    │
├────────────────────────────┤
│ Salt (32 bytes)            │
├────────────────────────────┤
│ IV (16 bytes)              │
├────────────────────────────┤
│ HMAC (32 bytes)            │
├────────────────────────────┤
│ Encrypted Index            │
├────────────────────────────┤
│ Encrypted File Data        │
└────────────────────────────┘
```

## Key Concepts
- AES encryption (CBC, GCM modes)
- PBKDF2/Argon2 key derivation
- HMAC for authentication
- Initialization vectors (IV)
- Salt generation
- Secure memory wiping
- Constant-time comparison

## Extensions
- Add public key encryption (RSA)
- Implement file compression
- Add cloud sync support
- Create file versioning
- Implement secure sharing
- Add two-factor authentication
- Create automatic backup
- Implement steganography option
