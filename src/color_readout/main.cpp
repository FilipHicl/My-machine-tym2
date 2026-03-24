//#include <Arduino.h>
#include <Adafruit_TCS34725.h>

void setup() {
    Serial.begin(115200);
    Adafruit_TCS34725 sensor(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_16X);
    if (!sensor.begin()) {
        Serial.println("No TCS34725 found");
        while (1); // Halt if sensor is not found
    }
}

void loop() {
    Adafruit_TCS34725 sensor(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_16X);
    uint16_t r, g, b, c;
    sensor.getRawData(&r, &g, &b, &c);
    Serial.print("R: "); Serial.print(r/(float)c);
    Serial.print(" G: "); Serial.print(g/(float)c);
    Serial.print(" B: "); Serial.print(b/(float)c);
    Serial.print(" C: "); Serial.println(c);
    delay(1000); // Read every second
}