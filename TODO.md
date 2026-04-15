# Robot Improvements - Phase 1: Motor Fixes & Compilation

**Status: In Progress - Fixes Applied**

## Checklist

- [x] Planning complete and approved
- [x] Update kinematics.h: Fix config.h include path → `../../include/config.h`
- [x] Update kinematics.cpp: Fix this-> for motors, balance cPhi (done), implement velocity ramping logic
- [x] Update src/final_app/main.cpp: Fix "Wi‑Fi.h" → "WiFi.h"
- [x] Update lib/Motor/Motor.cpp: ESP32 ledc PWM (fix deprecated analogWriteFreq/Resolution)
- [x] Create include/config.h for tunable constants (wheelDiameter, cPhi, maxAccel, etc.) - **ENHANCED** with wheelbase_mm etc.
- [ ] **Compile test:** `pio run -e final_app` (or VSCode: Ctrl+Alt+B → PlatformIO: Build)
- [ ] Calibrate: Run motor test (`pio run -e motor_test`), update empirical cPhi in config.h
- [ ] Test straight-line drift and smoothness
- [ ] Phase 1 complete → Proceed to Phase 2 (line tracking)

**Next:** Test compilation after PATH fix / VSCode build.

**Notes:** 
- Added config.h enhancements (wheelbase_mm etc.).
- Changes backward-compatible.
- PIO CLI PATH: Add `C:\Users\slany\.platformio\penv\Scripts` to PATH (restart terminal).
- VSCode PIO extension handles builds without CLI.
