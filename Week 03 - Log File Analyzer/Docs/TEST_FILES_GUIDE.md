# Test Log Files Documentation

This directory contains various test log files designed to test different aspects of the Log File Analyzer application.

---

## 📁 Test Files Overview

| File Name | Entries | Size | Purpose |
|-----------|---------|------|---------|
| `small_test.log` | 10 | ~600 B | Quick basic testing |
| `medium_test.log` | 51 | ~3.2 KB | Testing with moderate data |
| `large_test.log` | 1,000 | ~90 KB | Performance testing |
| `extra_large_test.log` | 10,000 | ~840 KB | Stress testing & performance |
| `malformed_test.log` | 14 (7 valid) | ~600 B | Error handling testing |
| `errors_heavy.log` | 26 | ~1.5 KB | Filter testing (mostly ERROR) |
| `info_heavy.log` | 40 | ~2.2 KB | Filter testing (mostly INFO) |

---

## 🎯 Test File Descriptions

### 1. small_test.log
**Purpose:** Quick validation testing  
**Entries:** 10 log lines  
**Content:**
- Mix of INFO, WARN, and ERROR levels
- Basic application lifecycle events
- Good for initial testing

**Use Cases:**
- Verify basic file loading
- Test all log level filters
- Quick search functionality validation

---

### 2. medium_test.log
**Purpose:** Realistic scenario testing  
**Entries:** 51 log lines  
**Content:**
- Detailed application workflow
- Database connection issues
- Email service warnings
- API operations
- Recovery scenarios

**Use Cases:**
- Test pagination (if implemented)
- Validate statistics accuracy
- Test search with multiple matches
- Realistic user scenarios

---

### 3. large_test.log
**Purpose:** Performance testing with large datasets  
**Entries:** 1,000 log lines  
**Content:**
- Randomly generated entries
- Various log levels (INFO, WARN, ERROR)
- User IDs and operations
- Diverse messages for search testing

**Use Cases:**
- Performance benchmarking
- Display optimization validation
- Memory usage testing
- Search performance testing

**Expected Performance:**
- Load time: < 1 second
- Display time: 5-10x faster than original (with ostringstream optimization)

---

### 4. extra_large_test.log
**Purpose:** Stress testing and extreme scenarios  
**Entries:** 10,000 log lines  
**Content:**
- Multiple components (Auth, API, Database, Cache, etc.)
- Weighted towards INFO (realistic production ratio)
- Duration metrics
- User IDs
- Various operations

**Use Cases:**
- Maximum stress testing
- Memory management validation
- Performance optimization verification
- Real-world large file scenarios

**Expected Performance:**
- Load time: < 3 seconds
- Should handle smoothly with optimizations

**Statistics Expected:**
- ~62.5% INFO
- ~25% WARN
- ~12.5% ERROR

---

### 5. malformed_test.log
**Purpose:** Error handling and robustness testing  
**Entries:** 14 total lines (7 valid, 7 malformed)  
**Content:**
- Valid log entries
- Lines without proper timestamp
- Lines without log level
- Empty lines
- Random text
- Incorrect format patterns

**Use Cases:**
- Test malformed line counter
- Verify error reporting
- Validate regex pattern matching
- Ensure application doesn't crash on bad data

**Expected Behavior:**
- Should load 7 valid entries
- Should report: "⚠ Skipped 6 malformed lines"
- Should not crash or throw errors

---

### 6. errors_heavy.log
**Purpose:** Testing ERROR level filtering  
**Entries:** 26 lines  
**Content:**
- 22 ERROR entries (~85%)
- 4 WARN entries (~15%)
- System failure scenario
- Critical errors
- Shutdown sequence

**Use Cases:**
- Test "View ERROR Logs" filter (option 5)
- Verify statistics calculation
- Test search for "error" keyword
- Validate color coding for errors

**Expected Statistics:**
- ERROR: 22 (84.62%)
- WARN: 4 (15.38%)

---

### 7. info_heavy.log
**Purpose:** Testing INFO level filtering  
**Entries:** 40 lines  
**Content:**
- 100% INFO entries
- System startup
- Health checks
- Normal operations
- Performance metrics
- Backup operations

**Use Cases:**
- Test "View INFO Logs" filter (option 3)
- Verify statistics with single level
- Test searches in INFO-only logs
- Validate display performance

**Expected Statistics:**
- INFO: 40 (100.00%)

---

## 🧪 Testing Scenarios

### Basic Functionality Tests

#### Test 1: Load Small File
```
1. Run: .\main.exe
2. Select option 1
3. Enter: Docs\small_test.log
4. Expected: "✓ Loaded 10 log entries"
```

#### Test 2: View All Logs
```
1. After loading small_test.log
2. Select option 2
3. Expected: Display all 10 entries with colors
```

#### Test 3: Filter by Level
```
1. After loading small_test.log
2. Select option 3 (INFO logs)
3. Expected: Should show INFO entries only
4. Repeat for WARN (option 4) and ERROR (option 5)
```

#### Test 4: Show Statistics
```
1. After loading any file
2. Select option 7
3. Expected: Percentage breakdown of log levels
4. Verify percentages add up to 100%
```

---

### Search Functionality Tests

#### Test 5: Basic Search
```
1. Load medium_test.log
2. Select option 6
3. Enter: "database"
4. Expected: Show all entries containing "database"
```

#### Test 6: Search History
```
1. Perform multiple searches
2. Select option 8 (View Search History)
3. Expected: See numbered list of all searches
```

#### Test 7: Case Sensitivity
```
1. Search for: "ERROR"
2. Search for: "error"
3. Expected: Should find both patterns
```

---

### Performance Tests

#### Test 8: Large File Load
```
1. Load large_test.log (1,000 entries)
2. Measure load time
3. Expected: < 1 second
4. View all logs
5. Expected: Fast display (ostringstream optimization)
```

#### Test 9: Extra Large File
```
1. Load extra_large_test.log (10,000 entries)
2. Measure load time
3. Expected: < 3 seconds
4. Test filters and search
5. Expected: Responsive performance
```

---

### Error Handling Tests

#### Test 10: Malformed Entries
```
1. Load malformed_test.log
2. Expected: "✓ Loaded 7 log entries"
3. Expected: "⚠ Skipped 6 malformed lines"
4. Verify statistics work correctly
```

#### Test 11: Non-Existent File
```
1. Select option 1
2. Enter: "nonexistent.log"
3. Expected: "✗ Could not open file: nonexistent.log"
```

#### Test 12: Empty Filename
```
1. Select option 1
2. Press Enter without typing
3. Expected: "✗ No filename provided"
```

---

### Filter Tests

#### Test 13: Error-Heavy File
```
1. Load errors_heavy.log
2. Select option 5 (View ERROR Logs)
3. Expected: Show 22 ERROR entries
4. Select option 7 (Statistics)
5. Expected: ERROR: 22 (84.62%), WARN: 4 (15.38%)
```

#### Test 14: Info-Heavy File
```
1. Load info_heavy.log
2. Select option 3 (View INFO Logs)
3. Expected: Show all 40 entries
4. Select option 7 (Statistics)
5. Expected: INFO: 40 (100.00%)
```

---

## 📊 Expected Statistics

### small_test.log
- INFO: 5 (50.00%)
- WARN: 2 (20.00%)
- ERROR: 3 (30.00%)

### medium_test.log
- INFO: 35 (68.63%)
- WARN: 11 (21.57%)
- ERROR: 5 (9.80%)

### large_test.log
- Distribution varies (random generation)
- Should have mix of all three levels

### extra_large_test.log
- INFO: ~6,250 (62.50%)
- WARN: ~2,500 (25.00%)
- ERROR: ~1,250 (12.50%)

### errors_heavy.log
- ERROR: 22 (84.62%)
- WARN: 4 (15.38%)

### info_heavy.log
- INFO: 40 (100.00%)

---

## 🎨 Visual Validation

When viewing logs, verify color coding:
- **INFO:** Green
- **WARN:** Yellow  
- **ERROR:** Red
- **Timestamp:** Cyan
- **Headers:** Bright Cyan

---

## 🔧 Troubleshooting

### If Files Don't Load
1. Check file paths (use `Docs\filename.log`)
2. Verify files exist: `Get-ChildItem .\Docs\*.log`
3. Check file permissions

### If Statistics Look Wrong
1. Load file and view all logs
2. Manually count each level
3. Verify against statistics display
4. Check for malformed entries

### If Search Doesn't Find Results
1. Verify file is loaded
2. Check spelling
3. Try searching for log level names
4. Search is case-sensitive

---

## 📝 Notes

- All files use format: `YYYY-MM-DD HH:MM:SS [LEVEL] Message`
- Dates are all in January 2026
- Files are UTF-8 encoded
- Files can be viewed in any text editor
- Malformed lines are intentional in `malformed_test.log`

---

## 🚀 Quick Start

**For First Time Testing:**
```bash
# Run the program
.\main.exe

# Load small file for quick test
1 → Docs\small_test.log

# Try each menu option
2 → View All Logs
3 → View INFO Logs
4 → View WARN Logs
5 → View ERROR Logs
6 → Search (try: "database")
7 → Show Statistics
8 → View Search History
9 → Exit
```

**For Performance Testing:**
```bash
# Load large file
1 → Docs\large_test.log

# Or extra large file
1 → Docs\extra_large_test.log

# Test display speed
2 → View All Logs (should be fast!)
```

**For Error Handling Testing:**
```bash
# Load malformed file
1 → Docs\malformed_test.log

# Should see: "Loaded 7 entries" + "Skipped 6 malformed lines"
```

---

## ✅ Expected Outcomes

All test files should:
- ✓ Load without crashing
- ✓ Display correctly with colors
- ✓ Filter properly by log level
- ✓ Show accurate statistics
- ✓ Support search functionality
- ✓ Handle errors gracefully

Performance with optimizations:
- ✓ Fast loading (< 3s even for 10,000 entries)
- ✓ Fast display (5-10x faster than original)
- ✓ No lag when viewing/filtering

---

**Last Updated:** 2026-01-14  
**Test Files Version:** 1.0  
**Total Test Coverage:** 7 files, 11,151 log entries
