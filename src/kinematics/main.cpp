#include <Arduino.h>
#include "kinematics.h"

kinematics robot;

void setup() {
    Serial.begin(115200);
    robot.begin(210, 64);
    Serial.println("Kinematics initialized.");
    delay(5000);
    robot.start();
    robot.setVoltage(5.0f);
}

void loop() {
    
    robot.setSpeed(0.1f);
    delay(2000);
    robot.setSpeed(0.0f);
    delay(2000);
    robot.setSpeed(-0.1f);
    delay(2000);
    robot.setSpeed(0.0f);
    delay(2000);


}