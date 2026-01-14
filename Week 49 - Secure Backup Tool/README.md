# Week 49: Secure Backup Tool

## Project Overview
Build a comprehensive backup solution with incremental backups, encryption, compression, and cloud storage support.

## Learning Objectives
- Backup strategies (full, incremental, differential)
- File change detection
- Compression algorithms
- Encryption implementation
- Cloud storage APIs
- Restore procedures

## Features to Implement
- [ ] Full, incremental, and differential backups
- [ ] File change detection (checksums, timestamps)
- [ ] Compression (zlib, lz4, zstd)
- [ ] AES-256 encryption
- [ ] Multiple backup destinations
- [ ] Cloud storage support (S3, Azure, Dropbox)
- [ ] Backup scheduling
- [ ] Restore functionality
- [ ] Version history
- [ ] Deduplication
- [ ] Bandwidth throttling
- [ ] Backup verification

## Usage Example
```sh
# Create backup configuration
./backup init mybackup \
  --source /home/user/documents \
  --dest /backup/drive

# Perform full backup
./backup full mybackup

# Incremental backup (only changes)
./backup incremental mybackup

# Schedule automatic backups
./backup schedule mybackup \
  --full weekly \
  --incremental daily

# List backup versions
./backup list mybackup

# Restore specific version
./backup restore mybackup \
  --version 2026-01-14 \
  --dest /restore/path

# Verify backup integrity
./backup verify mybackup
```

## Configuration File
```yaml
# backup-config.yaml
name: mybackup
source:
  paths:
    - /home/user/documents
    - /home/user/photos
  exclude:
    - "*.tmp"
    - "*.cache"
    - ".git"

destination:
  type: local
  path: /backup/drive
  
compression:
  enabled: true
  algorithm: zstd
  level: 5
  
encryption:
  enabled: true
  algorithm: aes-256-gcm
  key_file: ~/.backup/key.enc
  
retention:
  keep_daily: 7
  keep_weekly: 4
  keep_monthly: 12
  
schedule:
  full: "0 2 * * 0"    # Sunday 2 AM
  incremental: "0 2 * * 1-6"  # Mon-Sat 2 AM
  
cloud:
  enabled: false
  provider: s3
  bucket: my-backups
  region: us-east-1
```

## Implementation
```cpp
class BackupManager {
public:
    void createFullBackup(const BackupConfig& config) {
        auto files = scanSourceFiles(config.source);
        
        BackupArchive archive(config.destination);
        archive.setCompression(config.compression);
        archive.setEncryption(config.encryption);
        
        for (const auto& file : files) {
            if (shouldExclude(file, config.exclude))
                continue;
                
            archive.addFile(file);
        }
        
        archive.finalize();
        updateIndex(archive.getMetadata());
    }
    
    void createIncrementalBackup(
        const BackupConfig& config) {
        
        auto lastBackup = getLastBackup(config.name);
        auto files = scanSourceFiles(config.source);
        
        BackupArchive archive(config.destination);
        archive.setCompression(config.compression);
        archive.setEncryption(config.encryption);
        
        for (const auto& file : files) {
            if (hasChanged(file, lastBackup)) {
                archive.addFile(file);
            }
        }
        
        archive.finalize();
    }
    
    void restore(const std::string& backupName,
                 const std::string& version,
                 const std::string& destination) {
        
        auto chain = buildBackupChain(
            backupName, version);
        
        // Restore from full backup first
        restoreArchive(chain.fullBackup, destination);
        
        // Apply incremental backups in order
        for (const auto& incremental : chain.incrementals) {
            restoreArchive(incremental, destination);
        }
    }
    
private:
    bool hasChanged(const FileInfo& file,
                   const BackupMetadata& lastBackup) {
        auto lastInfo = lastBackup.getFileInfo(file.path);
        if (!lastInfo) return true;
        
        return file.modifiedTime > lastInfo->modifiedTime ||
               file.checksum != lastInfo->checksum;
    }
    
    std::string calculateChecksum(const std::string& path) {
        std::ifstream file(path, std::ios::binary);
        SHA256 sha256;
        return sha256.digestFile(file);
    }
};

class BackupArchive {
public:
    void addFile(const FileInfo& file) {
        // Read file data
        auto data = readFile(file.path);
        
        // Compress
        if (compressionEnabled_) {
            data = compress(data, compressionAlgo_);
        }
        
        // Encrypt
        if (encryptionEnabled_) {
            data = encrypt(data, encryptionKey_);
        }
        
        // Write to archive
        writeBlock(file.path, data);
        
        // Update index
        index_.addEntry({
            file.path,
            file.size,
            file.modifiedTime,
            file.checksum
        });
    }
    
    void finalize() {
        // Write index
        writeIndex(index_);
        
        // Write metadata
        writeMetadata({
            timestamp_,
            totalSize_,
            fileCount_,
            compressionRatio_
        });
    }
};
```

## Archive Format
```
Backup Archive Structure:
┌──────────────────────────┐
│ Header                   │
│ - Magic number          │
│ - Version               │
│ - Timestamp             │
├──────────────────────────┤
│ Index                    │
│ - File list             │
│ - Checksums             │
│ - Offsets               │
├──────────────────────────┤
│ File Block 1             │
│ [encrypted+compressed]   │
├──────────────────────────┤
│ File Block 2             │
│ [encrypted+compressed]   │
├──────────────────────────┤
│ ...                      │
├──────────────────────────┤
│ Metadata                 │
│ - Statistics            │
│ - Integrity hash        │
└──────────────────────────┘
```

## Key Concepts
- Incremental backup strategies
- File change detection (mtime, checksums)
- Block-level deduplication
- Stream compression
- Authenticated encryption (AES-GCM)
- Backup chains and dependencies
- Cloud storage APIs (AWS S3, etc.)

## Extensions
- Add network backup (rsync-like)
- Implement block-level deduplication
- Create GUI interface
- Add disaster recovery features
- Implement bare-metal restore
- Add VSS support (Windows)
- Create mobile app for monitoring
- Implement P2P backup
