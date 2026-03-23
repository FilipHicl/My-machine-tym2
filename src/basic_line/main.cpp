#include <Arduino.h>

#include "kinematics.h"
#include "PIcontroll.h"
#include "ColorSensor.h"


kinematics robot;
PIController follow(2.0f, 0.5f); //P and I values
ColorSensor colorSensor;



unsigned long lastTime = 0;
long updateInterval = 20; // in milliseconds

void setup() {
    Serial.begin(115200);

    //Setup kin
    robot.begin();


    //Setup PI loop
    follow.setMaxTurnRate(0.8f);
    follow.setSetpoint(0.3f); //Change according to color calibration
    

}

void loop() {
    float currentVelocity = 0.2f; 

    unsigned long now = millis();
        float dt = (now - lastTime) / 1000.0f; 

    if(now - lastTime >= updateInterval) {
        lastTime = now;

        if (dt > 0.0) {
            float sensorValue = colorSensor.update();
            float turnRate_rads = follow.update(sensorValue, currentVelocity, dt);

            // Feed directly into your kinematics library!
            // Example: DiffDrive.setVelocities(linear_x, angular_z)
            robot.setSpeed(currentVelocity);
            robot.setTurnRate(turnRate_rads);
        }
    }
}