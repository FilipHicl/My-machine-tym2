#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
public:
    Motor();

    // Initialize with optional parameters for ESP32 hardware PWM
    // freq: 20000 Hz eliminates audible motor whine
    void begin(uint8_t pinFwd, uint8_t pinRev, uint32_t freq = 20000, uint8_t resolution = 10);

    void start();
    void stop();
    void setThrottle(float throttle);

private:
    uint8_t _pinFwd;
    uint8_t _pinRev;
    float _throttle;
    bool _isRunning;
    uint32_t _maxPwmValue; // Calculated based on chosen resolution

    void updatePins();
};

#endif // MOTOR_H