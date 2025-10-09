# ESI Pillbox Stepper Project

This project controls a 28BYJ-48 stepper motor (with ULN2003 driver) for an **automatic pillbox**. It uses PlatformIO with VS Code for development.

---

## 🚀 Getting Started

### 1. Install VS Code
Download and install [Visual Studio Code](https://code.visualstudio.com/).

### 2. Install PlatformIO Extension
1. Open VS Code.  
2. Go to the **Extensions Marketplace** (left sidebar).  
3. Search for **"PlatformIO IDE"** and install it.  
   - This adds toolchains, library manager, and build/upload buttons.

### 3. Clone the Repository
```bash
git clone https://github.com/DevelopmentHF/ESIProject
cd pillbox-stepper
```

### 4. Open in VS Code
- Open the folder in VS Code (`File → Open Folder`).  
- PlatformIO should automatically detect `platformio.ini`.

---

## ⚡ Building & Uploading

1. Plug in your Arduino (e.g., Uno or Nano).  
2. In VS Code bottom bar:  
   - **✔ Build** → compiles the code.  
   - **→ Upload** → builds + uploads to your Arduino.  
   - **Plug icon (Monitor)** → opens Serial Monitor (baud 115200).  
3. Or use the command palette (`Ctrl+Shift+P` / `Cmd+Shift+P` on Mac):  
   - `PlatformIO: Build`  
   - `PlatformIO: Upload`  
   - `PlatformIO: Monitor`

---

## 📁 Project Structure

```
pillbox-stepper/
├─ platformio.ini        # Project config (board, libs)
├─ src/
│  └─ main.cpp           # Entry point
├─ include/
│  └─ config.h           # Pin mappings, constants
├─ lib/
│  ├─ Scheduler/         # Non-blocking task scheduler
│  └─ StepperDriver/     # Stepper motor control wrapper
└─ test/                 # (Optional) unit tests
```

- `src/main.cpp` → sketch entry point.  
- `include/` → global headers (pins, constants).  
- `lib/` → custom modules (scheduler, driver).  

---

## 🔧 Common Tasks

- **Add libraries**: edit `platformio.ini` → add under `lib_deps`.  
- **Change board**: edit `platformio.ini` `board = uno` → e.g. `nanoatmega328`.  
- **Clean build**: Command Palette → `PlatformIO: Clean`.

---

## 🤝 Notes for Arduino IDE users

If someone prefers the Arduino IDE:
- Copy `src/main.cpp` → `pillbox-stepper.ino`.  
- Move headers from `include/` and `lib/` into the same folder or `Arduino/libraries/`.  
- Install required libraries via Arduino Library Manager (`Stepper`, etc.).  

---

## 🛠 Requirements
- Arduino Uno/Nano (ATmega328P)  
- 28BYJ-48 stepper motor + ULN2003 driver board  
- External 5V supply for motor  
  - We chose to implement using 6xAA batteries and a step down DC voltage regulator
- Common ground between motor supply and Arduino  

---

## ✅ Quick Test

To confirm PlatformIO is installed and working before wiring the stepper, try this minimal sketch:
```cpp
#include <Arduino.h>

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
```
1. Replace `src/main.cpp` with this code.  
2. Build & upload in VS Code.  
3. The onboard LED should blink at 1 Hz.  

If this works, your environment is ready for the pillbox project.
