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
    Serial.println("Motor on");
    delay(500);
    leftMotor.setThrottle(0);
    rightMotor.setThrottle(0);
    Serial.println("Motor off");
    delay(500);
    leftMotor.setThrottle(-0.5);
    rightMotor.setThrottle(-0.5);
    Serial.println("Motor on");
    delay(500);
    leftMotor.setThrottle(0);
    rightMotor.setThrottle(0);
    Serial.println("Motor off");
    delay(500);

}
    
