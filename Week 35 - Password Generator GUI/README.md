# Week 35: Password Generator GUI

## Project Overview
Create a graphical password generator with customizable options and strength indicators.

## Learning Objectives
- GUI design principles
- User input validation
- Clipboard integration
- Random number generation
- Visual feedback
- Widget customization

## Features to Implement
- [ ] Password length slider
- [ ] Character set checkboxes (a-z, A-Z, 0-9, symbols)
- [ ] Generate button
- [ ] Password preview display
- [ ] Copy to clipboard button
- [ ] Password strength meter
- [ ] Save generated passwords
- [ ] Password history
- [ ] Exclude similar characters option
- [ ] Generate multiple passwords

## UI Layout
```
╔════════════════════════════════════════════╗
║     Password Generator                     ║
╠════════════════════════════════════════════╣
║ Length: [========|====] 16                 ║
║                                            ║
║ ☑ Lowercase (a-z)                          ║
║ ☑ Uppercase (A-Z)                          ║
║ ☑ Numbers (0-9)                            ║
║ ☑ Symbols (!@#$%...)                       ║
║ ☐ Exclude similar (i, l, 1, O, 0)         ║
║                                            ║
║ ┌──────────────────────────────────────┐   ║
║ │ Generated Password:                  │   ║
║ │ Kj9#mP2$xL5&nQ8!                     │   ║
║ └──────────────────────────────────────┘   ║
║                                            ║
║ Strength: [████████░░] Strong (85/100)    ║
║                                            ║
║ [Generate]  [Copy]  [Save]  [History]     ║
╚════════════════════════════════════════════╝
```

## Qt Implementation
```cpp
class PasswordGeneratorWindow : public QMainWindow {
    Q_OBJECT
private:
    QSlider* lengthSlider;
    QCheckBox* lowercaseCheck;
    QCheckBox* uppercaseCheck;
    QCheckBox* numbersCheck;
    QCheckBox* symbolsCheck;
    QLineEdit* passwordDisplay;
    QProgressBar* strengthBar;
    
private slots:
    void generatePassword() {
        int length = lengthSlider->value();
        std::string charset;
        
        if (lowercaseCheck->isChecked())
            charset += "abcdefghijklmnopqrstuvwxyz";
        // ... add other character sets
        
        std::string password = 
            generator.generate(length, charset);
        passwordDisplay->setText(
            QString::fromStdString(password));
        updateStrength(password);
    }
    
    void copyToClipboard() {
        QClipboard* clipboard = 
            QApplication::clipboard();
        clipboard->setText(passwordDisplay->text());
        showNotification("Copied to clipboard!");
    }
};
```

## Key Concepts
- QSlider for range input
- QCheckBox for options
- QProgressBar for strength meter
- QClipboard for copy functionality
- Entropy calculation
- CSPRNG (cryptographically secure RNG)
- Password strength algorithms

## Extensions
- Add pronounceable password mode
- Implement passphrase generation
- Add password templates
- Create password policy checker
- Implement batch generation
- Add export to file
- Create password expiry tracker
- Implement breach checking
