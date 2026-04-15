// Robot Configuration - Tunable parameters
// Edit here or add web tuning later (Phase 3)

#pragma once

// Kinematics
const uint16_t WHEELBASE_MM = 210;
const uint16_t WHEEL_DIAMETER_MM = 64;  // [mm], measure & validate
const float DEFAULT_CPHI_LEFT = 1.6f;   // [unitless], post-calibration
const float DEFAULT_CPHI_RIGHT = 1.6f;  // Balance to same wheel speed at equal throttle
const float BATTERY_VOLTAGE = 12.0f;    // [V], measured

// Ramping (new)
const float MAX_LINEAR_ACCEL = 2.0f;    // [m/s²], prevents slip/lurch
const float MAX_ANGULAR_ACCEL = 4.0f;   // [rad/s²]

// Line Following (prep Phase 2)
const float PI_P_GAIN = 40.0f;
const float PI_I_GAIN = 10.0f;
const float BASE_VELOCITY = 0.07f;      // [m/s]
const float SLOW_FACTOR = 0.35f;

const long LOOP_UPDATE_MS = 20;
