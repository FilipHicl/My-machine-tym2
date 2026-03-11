#ifndef KINEMATICS_H
#define KINEMATICS_H

#include <Arduino.h>
class kinematics {
public:
    kinematics();

    // Initialize with optional parameters for ESP32 hardware PWM
    // freq: 20000 Hz eliminates audible motor whine
    // resolution: 10-bit gives 1024 steps of speed control instead of 256
    void begin(uint16_t wheelbase = 100, uint16_t wheelDiameter = 60);


    void start();
    void stop();
    void setVoltage(float voltage);
    void setSpeed(float speed);
    void setTurnRate(float turnRate);
    void reset();

private:
    int16_t _wheelbase;
    uint16_t _wheelDiameter;
    float speed; // in m/s
    float turnRate = 0.0f; // in rads/s
    float voltage = 12.0f;
    float cPhi = 1.745f; // Placeholder for a constant related to the robot's kinematics

    void updateMotors();
};

#endif // KINEMATICS_H