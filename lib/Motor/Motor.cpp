#include "Motor.h"

Motor::Motor() : _pinFwd(0), _pinRev(0), _throttle(0.0f), _isRunning(false), _maxPwmValue(255) {}

void Motor::begin(uint8_t pinFwd, uint8_t pinRev, uint32_t freq, uint8_t resolution) {
    _pinFwd = pinFwd;
    _pinRev = pinRev;
    
    // Calculate max PWM value based on resolution (e.g., 10-bit = 1023)
    _maxPwmValue = (1 << resolution) - 1; 
    
    // Set the global PWM frequency and resolution for the ESP32
    analogWriteFrequency(freq);
    analogWriteResolution(resolution);

    pinMode(_pinFwd, OUTPUT);
    pinMode(_pinRev, OUTPUT);
    
    stop(); 
}

void Motor::start() {
    _isRunning = true;
    updatePins();
}

void Motor::stop() {
    _isRunning = false;
    analogWrite(_pinFwd, 0);
    analogWrite(_pinRev, 0);
}

void Motor::setThrottle(float throttle) {
    if (throttle > 1.0f) throttle = 1.0f;
    if (throttle < -1.0f) throttle = -1.0f;

    _throttle = throttle;

    if (_isRunning) {
        updatePins();
    }
}

void Motor::updatePins() {
    // Map the 0.0 to 1.0 throttle to the ESP32's configured PWM range
    uint32_t pwmValue = (uint32_t)(abs(_throttle) * _maxPwmValue);

    if (_throttle > 0) {
        // Forward
        analogWrite(_pinRev, 0);         
        analogWrite(_pinFwd, pwmValue);  
    } 
    else if (_throttle < 0) {
        // Reverse
        analogWrite(_pinFwd, 0);         
        analogWrite(_pinRev, pwmValue);  
    } 
    else {
        // Coast
        analogWrite(_pinFwd, 0);
        analogWrite(_pinRev, 0);
    }
}