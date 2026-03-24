#include <Arduino.h>

#include "kinematics.h"
#include "PIcontroll.h"
#include "ColorSensor.h"


kinematics robot;
PIController follow(40.0f, 10.0f); //P and I values
ColorSensor colorSensor;



unsigned long lastTime = 0;
long updateInterval = 20; // in milliseconds



void setup() {
    Serial.begin(115200);

    //Setup kin
    robot.begin(210, 64);
    //robot.begin();


    //Setup PI loop
    follow.setSetpoint(0.1f); // This is the target color error value you want to maintain (tune this based on your line and sensor)
    follow.setMaxTurnRate(0.8f);
    robot.start();
    

}

void loop() {
    float currentVelocity = 0.07f; 

    unsigned long now = millis();
        float dt = (now - lastTime) / 1000.0f; 

    if(now - lastTime >= updateInterval) {
        lastTime = now;

        if (dt > 0.0) {
            float sensorValue = colorSensor.update();
            float turnRate_rads = follow.update(sensorValue, currentVelocity, dt);

            Serial.print("  Turn rate: "); Serial.println(turnRate_rads);

            // Feed directly into your kinematics library!
            // Example: DiffDrive.setVelocities(linear_x, angular_z)
            robot.setSpeed(currentVelocity);
            robot.setTurnRate(turnRate_rads);
        }
    }
}