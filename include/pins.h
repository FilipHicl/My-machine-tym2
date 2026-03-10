#pragma once  // Tells the compiler to only include this file once

#include <Arduino.h> // Needed for the uint8_t data type

// Wrapping pins in a namespace keeps them organized and prevents naming conflicts
namespace Pins {

    // --- Motor Driver Pins ---
    // constexpr means these are evaluated at compile-time (takes up zero RAM!)
    constexpr uint8_t motorLeftA  = 4;
    constexpr uint8_t motorLeftB  = 5;
    constexpr uint8_t motorRightA = 6;
    constexpr uint8_t motorRightB = 7;

    // --- Status Indicators ---
    // On most ESP32-S3 DevKitC boards, the built-in RGB WS2812 LED is on pin 48
    constexpr uint8_t builtInRGB = 48;

    // --- Sensors (Examples for later) ---
    // constexpr uint8_t ultrasonicTrig = 10;
    // constexpr uint8_t ultrasonicEcho = 11;

} // End of Pins namespace