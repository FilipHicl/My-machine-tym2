#include <Arduino.h>
#include "kinematics.h"

kinematics robot;

void setup() {
    robot.begin();

}

void loop() {
    robot.start();
    robot.setSpeed(0.5f);
    delay(2000);
    robot.stop();
    delay(1000);
    robot.setSpeed(-0.5f);
    delay(2000);
    robot.reset();
    delay(1000);
    robot.setTurnRate(1.047f);
    delay(3000);
    robot.stop();
    delay(500);
    robot.setSpeed(0.2f);
    robot.setTurnRate(-0.785f);
    delay(5000);

}