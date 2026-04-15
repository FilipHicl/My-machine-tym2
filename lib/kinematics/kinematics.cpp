#include "kinematics.h"
#include <Arduino.h>
#include "Motor.h"
#include "../../include/pins.h"
// 1. FIXED: Replaced cPhi with cPhi_left and cPhi_right in the constructor
kinematics::kinematics() : _wheelbase(WHEELBASE_MM), _wheelDiameter(WHEEL_DIAMETER_MM), speed(0.0f), turnRate(0.0f), voltage(BATTERY_VOLTAGE), cPhi_left(DEFAULT_CPHI_LEFT), cPhi_right(DEFAULT_CPHI_RIGHT), current_speed(0.0f), current_turn_rate(0.0f), target_speed(0.0f), target_turn_rate(0.0f), last_update_time(0) {}

// Note: It's generally better to make these private members of the kinematics class 
// inside the .h file, but leaving them global here works if you only have one robot.
// Motors now encapsulated as private class members

void kinematics::begin(uint16_t wheelbase, uint16_t wheelDiameter) {
    _wheelbase = wheelbase;
    _wheelDiameter = wheelDiameter;

    this->leftMotor.begin(Pins::motorLeftA, Pins::motorLeftB);
    this->rightMotor.begin(Pins::motorRightA, Pins::motorRightB);

    this->leftMotor.stop();
    this->rightMotor.stop();
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
    this->leftMotor.start();
    this->rightMotor.start();
    last_update_time = millis(); // init ramp timer
}

void kinematics::stop() {
    this->leftMotor.stop();
    this->rightMotor.stop();
}

void kinematics::updateMotors() {
    // Velocity ramping (NEW: prevents lurching)
    if (last_update_time == 0) {
        last_update_time = millis();
    }
    unsigned long now = millis();
    float dt = (now - last_update_time) / 1000.0f;
    last_update_time = now;
    if (dt > 0.001f) {  // min dt 1ms
        // Ramp linear speed
        float delta_v = target_speed - current_speed;
        float max_delta_v = max_linear_accel * dt;
        current_speed += constrain(delta_v, -max_delta_v, max_delta_v);
        
        // Ramp turn rate
        float delta_w = target_turn_rate - current_turn_rate;
        float max_delta_w = max_angular_accel * dt;
        current_turn_rate += constrain(delta_w, -max_delta_w, max_delta_w);
    }

    // Map ramped speed -> wheel angular proxy. Positive `speed` -> forward (positive throttle).
    float forwardComponent = current_speed * (2000.0f / _wheelDiameter);

    // Turn component: positive turnRate should produce a left turn.
    float turnComponent = current_turn_rate * ((float)_wheelbase / _wheelDiameter);

    // Differential mixing: left = forward + turn, right = forward - turn
    float leftWheelTarget_w = forwardComponent + turnComponent;
    float rightWheelTarget_w = forwardComponent - turnComponent;

    // Convert target values to PWM throttle (-1..1) using motor constants and battery voltage.
    float right_throttle = constrain((rightWheelTarget_w * cPhi_right) / voltage, -1.0f, 1.0f);
    float left_throttle = constrain((leftWheelTarget_w * cPhi_left) / voltage, -1.0f, 1.0f);
    Serial.print("Throttles L: "); Serial.print(left_throttle, 3); Serial.print(" R: "); Serial.println(right_throttle, 3);
    this->rightMotor.setThrottle(right_throttle);
    this->leftMotor.setThrottle(left_throttle);
}


void kinematics::setSpeed(float speed) {
    target_speed = speed;
    updateMotors();
}

void kinematics::setTurnRate(float turnRate) {
    target_turn_rate = turnRate;
    updateMotors();
}

void kinematics::setMaxAcceleration(float lin_accel_m_s2, float ang_accel_rad_s2) {
    max_linear_accel = lin_accel_m_s2;
    max_angular_accel = ang_accel_rad_s2;
}

void kinematics::reset() {
    target_speed = 0.0f;
    target_turn_rate = 0.0f;
    current_speed = 0.0f;
    current_turn_rate = 0.0f;
    updateMotors();
}
