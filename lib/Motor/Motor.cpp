#include "Motor.h"

Motor::Motor() : _pinFwd(0), _pinRev(0), _throttle(0.0f), _isRunning(false), _maxPwmValue(255) {}

void Motor::begin(uint8_t pinFwd, uint8_t pinRev) {
    _pinFwd = pinFwd;
    _pinRev = pinRev;
    _maxPwmValue = 255; // 8-bit Arduino default
    
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
