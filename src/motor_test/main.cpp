#include <Arduino.h>

#include "pins.h"
#include "Motor.h"


Motor leftMotor;
Motor rightMotor;

void setup() {
    Serial.begin(115200);
    
    // Use the pins with the Pins:: prefix
    leftMotor.begin(Pins::motorLeftA, Pins::motorLeftB);
    rightMotor.begin(Pins::motorRightA, Pins::motorRightB);
    
    leftMotor.start();
    rightMotor.start();
}

void loop() {
    leftMotor.setThrottle(0.5);
    rightMotor.setThrottle(0.5);
    delay(1000);
}