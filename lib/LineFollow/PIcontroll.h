#ifndef PI_CONTROLLER_H
#define PI_CONTROLLER_H

class PIController {
private:
    float kp;             // Proportional gain (now scaled for curvature)
    float ki;             // Integral gain
    float setpoint;       // The target sensor value
    float integral_sum;   // Accumulated error
    float max_turn_rate;  // Maximum physical rad/s your robot can turn

public:
    PIController(float p, float i) {
        kp = p;
        ki = i;
        setpoint = 0.0f;
        integral_sum = 0.0f;
        max_turn_rate = 3.14f; // Default to roughly 1 half-rotation per sec
    }
    

    void setSetpoint(float target) {
        setpoint = target;
    }

    void setTunings(float p, float i) {
        kp = p;
        ki = i;
    }

    // Set the physical limits of your chassis in rad/s
    void setMaxTurnRate(float max_rad_per_sec) {
        max_turn_rate = max_rad_per_sec;
    }

    void reset() {
        integral_sum = 0.0f;
    }

    // Now accepts velocity to scale the turn rate dynamically
    float update(float input, float velocity, float dt) {
        float error = setpoint - input;

        // 1. Calculate desired curvature (1/R)
        float p_out = kp * error;
        integral_sum += (error * dt);
        float i_out = ki * integral_sum;
        float curvature = p_out + i_out;

        // 2. Calculate requested Turn Rate (rad/s)
        // If velocity is 0, turn_rate becomes 0, which is physically accurate.
        float turn_rate = curvature * velocity;

        // 3. Clamping and Anti-Windup
        // We clamp against the physical limits of the chassis in rad/s.
        if (turn_rate > max_turn_rate) {
            turn_rate = max_turn_rate;
            // Un-wind the integral to prevent runaway
            integral_sum -= (error * dt); 
        } else if (turn_rate < -max_turn_rate) {
            turn_rate = -max_turn_rate;
            integral_sum -= (error * dt);
        }

        return turn_rate;
    }
};

#endif