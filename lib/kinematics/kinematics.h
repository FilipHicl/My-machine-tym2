#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <Arduino.h>
#include "Motor.h"
#include "../../include/config.h"
class kinematics {
public:
    kinematics();

    void begin(uint16_t wheelbase, uint16_t wheelDiameter);

    // Initialize with optional parameters for ESP32 hardware PWM
    // freq: 20000 Hz eliminates audible motor whine
    // resolution: 10-bit gives 1024 steps of speed control instead of 256
    void setConstants(float cPhi_left, float cPhi_right, uint16_t wheelbase, uint16_t wheelDiameter);
    void start();
    void stop();
    void setVoltage(float voltage);
    void setSpeed(float speed);
    void setTurnRate(float turnRate);
    void reset();

private:
    int16_t _wheelbase;
    uint16_t _wheelDiameter;
    float speed = 0.0f; // in m/s
    float turnRate = 0.0f; // in rads/s
    float voltage = 12.0f;
    Motor leftMotor;
    Motor rightMotor;
    float cPhi_left;
    float cPhi_right;

    void updateMotors();

    // Velocity ramping state (new for smoothing)
    float target_speed = 0.0f;        // [m/s]
    float target_turn_rate = 0.0f;    // [rad/s]
    float current_speed = 0.0f;       // ramped
    float current_turn_rate = 0.0f;   // ramped
    float max_linear_accel;
    float max_angular_accel;
    unsigned long last_update_time = 0;

    // New methods
public:
    void setMaxAcceleration(float lin_accel_m_s2, float ang_accel_rad_s2);
};

#endif // KINEMATICS_H
