# Week 36: File Encryption GUI Tool

## Project Overview
Build a user-friendly GUI application for encrypting and decrypting files with drag-and-drop support.

## Learning Objectives
- File encryption/decryption
- Drag-and-drop functionality
- Progress tracking for large files
- Secure key handling
- GUI design for security tools
- Error handling and user feedback

## Features to Implement
- [ ] Drag-and-drop file selection
- [ ] AES-256 encryption
- [ ] Password input with confirmation
- [ ] Key file generation
- [ ] Encrypt/decrypt operations
- [ ] Progress bar for large files
- [ ] Batch file processing
- [ ] File integrity verification
- [ ] Secure file deletion
- [ ] Encryption settings (algorithm, mode)

## UI Layout
```
╔════════════════════════════════════════════╗
║      File Encryption Tool                  ║
╠════════════════════════════════════════════╣
║ ┌────────────────────────────────────────┐ ║
║ │  Drag files here or click to browse   │ ║
║ │           [Browse Files]               │ ║
║ └────────────────────────────────────────┘ ║
║                                            ║
║ Selected Files:                            ║
║ • document.pdf              (2.3 MB)       ║
║ • photos.zip                (45.8 MB)      ║
║                                            ║
║ Password: [****************]               ║
║ Confirm:  [****************]               ║
║                                            ║
║ Options:                                   ║
║ Algorithm: [AES-256 ▼]                     ║
║ ☑ Delete original after encryption        ║
║ ☑ Add .encrypted extension                ║
║                                            ║
║ [████████████░░░░] 75% - Encrypting...     ║
║ photos.zip (34.4 MB / 45.8 MB)             ║
║                                            ║
║    [Encrypt]    [Decrypt]    [Cancel]     ║
╚════════════════════════════════════════════╝
```

## Implementation Example
```cpp
class FileEncryptionTool : public QMainWindow {
    Q_OBJECT
private:
    QListWidget* fileList;
    QLineEdit* passwordInput;
    QProgressBar* progressBar;
    Encryptor encryptor;

private slots:
    void onEncryptClicked() {
        QString password = passwordInput->text();
        
        if (!validatePassword(password)) {
            showError("Password too weak!");
            return;
        }
        
        for (const auto& file : selectedFiles) {
            encryptFile(file, password);
        }
    }
    
    void encryptFile(const QString& path, 
                     const QString& password) {
        QFile input(path);
        QFile output(path + ".encrypted");
        
        encryptor.setPassword(password);
        encryptor.setProgressCallback([this](int percent) {
            progressBar->setValue(percent);
        });
        
        encryptor.encrypt(input, output);
    }
    
    void onFilesDropped(const QMimeData* data) {
        for (const QUrl& url : data->urls()) {
            addFileToList(url.toLocalFile());
        }
    }
};
```

## Key Concepts
- QDragEnterEvent/QDropEvent
- QMimeData for file handling
- QFileDialog for file selection
- Threading for encryption (avoid UI freeze)
- QCryptographicHash for checksums
- Secure memory handling
- Progress callbacks

## Extensions
- Add public key encryption
- Implement file shredding
- Create password strength meter
- Add compression before encryption
- Implement folder encryption
- Add cloud upload integration
- Create encrypted archive format
- Implement steganography
