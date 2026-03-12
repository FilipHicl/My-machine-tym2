#include <Arduino.h>
#include "kinematics.h"

kinematics robot;

void setup() {
    Serial.begin(115200);
    robot.begin();
    Serial.println("Kinematics initialized.");

}

void loop() {
    robot.start();
    Serial.println("Robot started.");
    robot.setSpeed(0.5f);
    Serial.println("Robot speed set.");
    delay(2000);
    robot.reset();
    delay(1000);
    robot.setSpeed(-0.5f);
    delay(2000);
    robot.reset();
    delay(1000);
    robot.setTurnRate(1000);
    delay(3000);
    robot.reset();
    delay(500);
    robot.setSpeed(0.2f);
    robot.setTurnRate(-0.785f);
    delay(5000);

}