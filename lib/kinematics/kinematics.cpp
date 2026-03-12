#include "kinematics.h"
#include <Arduino.h>
#include "Motor.h"
#include "../../include/pins.h"

kinematics::kinematics() : _wheelbase(100), _wheelDiameter(60), speed(0.0f), turnRate(0.0f), voltage(12.0f), cPhi(1.745f) {}

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

void kinematics::setVoltage(float voltage) {
    this->voltage = voltage;
}

void kinematics::start() {
    //updateMotors();
    leftMotor.start();
    rightMotor.start();
    // Implement logic to start the robot, e.g., set initial motor speeds
}

void kinematics::stop() {
    leftMotor.stop();
    rightMotor.stop();
    // Implement logic to stop the robot, e.g., set motor speeds to zero
}

void kinematics::updateMotors() {
    float rightWheelTargetSpeed = this->speed*(2 / (_wheelDiameter/1000.0)) + ((this->turnRate) * _wheelbase)/2;
    float leftWheelTargetSpeed = this->speed*(2 / (_wheelDiameter/1000.0)) - ((this->turnRate) * _wheelbase)/2;

    rightMotor.setThrottle((rightWheelTargetSpeed * cPhi)/voltage);
    leftMotor.setThrottle((leftWheelTargetSpeed * cPhi)/voltage);
}

void kinematics::setSpeed(float speed) {
    this->speed = speed;
    updateMotors();
    // Implement logic to convert speed to motor throttle and set it
}

void kinematics::setTurnRate(float turnRate) {
    this->turnRate = turnRate;
    updateMotors();
    // Implement logic to convert turn rate to motor throttle and set it
}

void kinematics::reset() {
    speed = 0.0f;
    turnRate = 0.0f;    
    updateMotors();
    //leftMotor.stop();
    //rightMotor.stop();

}