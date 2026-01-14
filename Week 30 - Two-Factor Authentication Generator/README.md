# Week 30: Two-Factor Authentication Generator

## Project Overview
Create a TOTP (Time-based One-Time Password) generator compatible with Google Authenticator and similar apps.

## Learning Objectives
- TOTP algorithm implementation
- Base32 encoding/decoding
- HMAC-SHA1 cryptography
- QR code generation
- Time synchronization
- Secret key management

## Features to Implement
- [ ] TOTP code generation (RFC 6238)
- [ ] HOTP support (counter-based)
- [ ] QR code generation for setup
- [ ] Multiple account management
- [ ] Secret key import/export
- [ ] Backup codes generation
- [ ] Time sync verification
- [ ] Auto-refresh countdown
- [ ] Encrypted storage
- [ ] Search and categorization

## Usage Example
```sh
# Add new account
./totp add --name "GitHub" --secret "JBSWY3DPEHPK3PXP"

# Generate code
./totp generate GitHub
# Output: 123456 (valid for 25s)

# List all accounts
./totp list

# Export QR code
./totp qr GitHub -o github-qr.png

# Generate backup codes
./totp backup GitHub
```

## Interactive Display
```
╔════════════════════════════════════════════╗
║   Two-Factor Authentication Generator      ║
╠════════════════════════════════════════════╣
║ GitHub                                     ║
║ Code: 847293          [████████░░] 17s    ║
║                                            ║
║ Gmail                                      ║
║ Code: 562103          [███░░░░░░░] 8s     ║
║                                            ║
║ AWS                                        ║
║ Code: 910437          [██████████] 29s    ║
╠════════════════════════════════════════════╣
║ [Enter] Copy | [R]efresh | [Q]uit         ║
╚════════════════════════════════════════════╝
```

## TOTP Algorithm
```cpp
class TOTP {
    std::string generateCode(const std::string& secret) {
        // 1. Get current time step
        uint64_t timeStep = time(nullptr) / 30;
        
        // 2. Compute HMAC-SHA1
        std::string hmac = hmacSHA1(secret, timeStep);
        
        // 3. Dynamic truncation
        int offset = hmac[19] & 0x0f;
        int code = (hmac[offset] & 0x7f) << 24 |
                   (hmac[offset+1] & 0xff) << 16 |
                   (hmac[offset+2] & 0xff) << 8 |
                   (hmac[offset+3] & 0xff);
        
        // 4. Return 6-digit code
        return std::to_string(code % 1000000);
    }
};
```

## Key Concepts
- TOTP (Time-based OTP)
- HMAC-SHA1 algorithm
- Base32 encoding
- Unix timestamp
- QR code otpauth:// URI format
- Secret key security

## Extensions
- Add push notifications
- Implement cloud sync
- Create browser extension
- Add biometric unlock
- Support Steam Guard format
- Implement account recovery
- Add export encryption
- Create desktop widget
