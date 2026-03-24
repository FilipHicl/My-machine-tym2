#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <Adafruit_TCS34725.h>
#include <Arduino.h>
#include <math.h>

class ColorSensor {
public:
    ColorSensor() : sensor(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_16X) {
        // You MUST measure these beforehand by placing the robot fully on the colored line.
        // Print the normalized (R/C, G/C, B/C) values to the serial monitor and save them here.
        target_r_norm = 0.62f; 
        target_g_norm = 0.21f;
        target_b_norm = 0.16f;
    }

    // 2. Hardware initialization (Call this inside your main setup() function)
    void begin() {
        sensor.begin();
    }

    // Fixed typo from setTargetCollor
    void setTargetColor(float r, float g, float b) {
        target_r_norm = r;
        target_g_norm = g;
        target_b_norm = b;
    }

    float update() {
        uint16_t r, g, b, c;
        sensor.getRawData(&r, &g, &b, &c);
        return calculateColorError(r, g, b, c);
    }

private:
    // 3. The sensor object is now completely hidden from the outside world
    Adafruit_TCS34725 sensor;

    // Target colors are also safely hidden
    float target_r_norm; 
    float target_g_norm;
    float target_b_norm;

    float calculateColorError(uint16_t r, uint16_t g, uint16_t b, uint16_t c) {
        if (c == 0) return 0.0f; 

        // Normalize the colors to make them immune to ambient light shadows
        float r_norm = (float)r / c;
        float g_norm = (float)g / c;
        float b_norm = (float)b / c;

        // Calculate Euclidean distance from the target line color
        float dr = r_norm - target_r_norm;
        float dg = g_norm - target_g_norm;
        float db = b_norm - target_b_norm;

        // The result is a positive number representing how "wrong" the color is.
        float color_distance = sqrt((dr * dr) + (dg * dg) + (db * db));

        return color_distance;
    }
};

#endif