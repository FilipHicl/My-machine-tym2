#include "kinematics.h"
#include <Arduino.h>
#include "Motor.h"
#include "../../include/pins.h"
/ 1. FIXED: Replaced cPhi with cPhi_left and cPhi_right in the constructor
kinematics::kinematics() : _wheelbase(100), _wheelDiameter(60), speed(0.0f), turnRate(0.0f), voltage(12.0f), cPhi_left(1.745f), cPhi_right(1.745f) {}

// Note: It's generally better to make these private members of the kinematics class 
// inside the .h file, but leaving them global here works if you only have one robot.
Motor leftMotor;
Motor rightMotor;

void kinematics::begin(uint16_t wheelbase, uint16_t wheelDiameter) {
    _wheelbase = wheelbase;
    _wheelDiameter = wheelDiameter;

    leftMotor.begin(Pins::motorLeftA, Pins::motorLeftB);
    rightMotor.begin(Pins::motorRightA, Pins::motorRightB);

    leftMotor.stop();
    rightMotor.stop();
}

void kinematics::setConstants(float cPhi_left, float cPhi_right, uint16_t wheelbase, uint16_t wheelDiameter){
    _wheelbase = wheelbase;
    _wheelDiameter = wheelDiameter;
    this->cPhi_left = cPhi_left;
    this->cPhi_right = cPhi_right;
}

void kinematics::setVoltage(float voltage) {
    this->voltage = voltage;
}

void kinematics::start() {
    leftMotor.start();
    rightMotor.start();
}

void kinematics::stop() {
    leftMotor.stop();
    rightMotor.stop();
}

void kinematics::updateMotors() {
    // Both of these are now correctly calculated in radians/second (rad/s)
    float forwardComponent = this->speed * (2000.0f / _wheelDiameter); 
    
    // 2. FIXED: Correct formula for wheel angular velocity during a turn
    float turnComponent = this->turnRate * ((float)_wheelbase / _wheelDiameter);

    float rightWheelTarget_w = forwardComponent + turnComponent;
    float leftWheelTarget_w = forwardComponent - turnComponent;

    // Convert target rad/s to a PWM duty cycle based on motor constants and battery voltage
    rightMotor.setThrottle((rightWheelTarget_w * cPhi_right) / voltage);
    leftMotor.setThrottle((leftWheelTarget_w  * cPhi_left) / voltage);
}

void kinematics::setSpeed(float speed) {
    this->speed = speed; 
    updateMotors();
}

void kinematics::setTurnRate(float turnRate) {
    this->turnRate = turnRate; 
    updateMotors();
}

void kinematics::reset() {
    speed = 0.0f;
    turnRate = 0.0f;    
    updateMotors();
}