# Week 31: Secure Key Derivation Tool

## Project Overview
Build a tool for deriving cryptographic keys from passwords using modern key derivation functions.

## Learning Objectives
- Key derivation functions (KDF)
- Password hashing best practices
- Salt generation
- Memory-hard functions
- Cryptographic parameters tuning
- Key stretching

## Features to Implement
- [ ] PBKDF2 implementation
- [ ] Argon2 support (Argon2i, Argon2d, Argon2id)
- [ ] Scrypt implementation
- [ ] bcrypt hashing
- [ ] Salt generation
- [ ] Configurable iterations/memory
- [ ] Key length customization
- [ ] Benchmark mode for tuning
- [ ] Multiple output formats (hex, base64)
- [ ] Batch key generation

## Usage Example
```sh
# Derive key using Argon2
./kdf derive --algo argon2id \
  --password "mypassword" \
  --salt "random_salt" \
  --length 32

# Generate and store
./kdf generate \
  --algo pbkdf2 \
  --password "secret" \
  --iterations 100000 \
  -o key.bin

# Benchmark for optimal parameters
./kdf benchmark --algo argon2id --time 2000

# Verify password against hash
./kdf verify --hash "$argon2id$v=19$m=65536..."
```

## API Usage
```cpp
KDF kdf;

// Argon2
auto key = kdf.argon2id(
    "password",
    "salt",
    32,              // key length
    65536,          // memory (KB)
    4,              // parallelism
    3               // iterations
);

// PBKDF2
auto key = kdf.pbkdf2(
    "password",
    "salt",
    32,             // key length
    100000,         // iterations
    HashAlgo::SHA256
);

// Verify
bool valid = kdf.verify("password", hash);
```

## Output Example
```
Deriving key with Argon2id...
Parameters:
  Memory: 65536 KB
  Iterations: 3
  Parallelism: 4
  Salt: A1B2C3D4E5F6...
  
Derived Key (32 bytes):
  Hex: 7f3e8c92a1b4d5e6f7a8b9c0d1e2f3a4...
  Base64: fz6MkqG01eb3qLnA0eL...
  
Time: 2.143s
```

## Key Concepts
- Memory-hard functions
- Time-memory trade-offs
- Password stretching
- Salt uniqueness
- Iteration count tuning
- Side-channel resistance
- Argon2 variants (i/d/id)

## Extensions
- Add HSM integration
- Implement HKDF (key expansion)
- Add key splitting (Shamir)
- Create password policy checker
- Implement peppering
- Add hardware acceleration
- Create audit logging
- Support key rotation
