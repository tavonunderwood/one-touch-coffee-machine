#pragma once

/*
 * ============================================================
 * System Configuration
 * ============================================================
 *
 * Contains system constants, operating parameters, calibration
 * values, and safety limits.
 *
 */

// ============================================================
// SERIAL / DEBUGGING
// ============================================================

constexpr unsigned long SERIAL_BAUD_RATE = 115200;

constexpr bool DEBUG_ENABLED = true;


// ============================================================
// COFFEE / RECIPE SETTINGS
// ============================================================

// Default mass of coffee beans for one brew [g]
constexpr float DEFAULT_BEAN_MASS_G = 18.0f;



// ============================================================
// BEAN DISPENSER
// ============================================================

// TODO: Tune after dispenser mechanism is built.

// Allowed error between requested and measured bean mass [g]
constexpr float BEAN_MASS_TOLERANCE_G = 0.5f;

// Maximum amount of time the dispenser may run [ms]
constexpr unsigned long DISPENSER_TIMEOUT_MS = 15000;

// Servo positions if a servo-controlled gate is used.
// TODO: Calibrate for actual mechanism.

constexpr int DISPENSER_CLOSED_ANGLE = 0;
constexpr int DISPENSER_OPEN_ANGLE   = 90;


// ============================================================
// GRINDER
// ============================================================

// Grinder PWM command.
// Arduino analogWrite range: 0-255.
//
// TODO: Determine appropriate speed after motor/driver testing.

constexpr uint8_t DEFAULT_GRINDER_PWM = 200;

// Maximum allowed continuous grinding time [ms]
constexpr unsigned long GRINDER_TIMEOUT_MS = 30000;

// Temporary grinding duration for early testing [ms].
// Eventually grinding may be controlled by another condition.

constexpr unsigned long DEFAULT_GRIND_TIME_MS = 10000;


// ============================================================
// LOAD CELL
// ============================================================

// TODO: Determine experimentally during load-cell calibration.

// Conversion factor used by the load-cell library.
constexpr float LOAD_CELL_CALIBRATION_FACTOR = 1.0f;

// Number of readings to average.
constexpr uint8_t LOAD_CELL_SAMPLE_COUNT = 10;

// Threshold below which the scale is considered effectively empty [g]
constexpr float SCALE_ZERO_THRESHOLD_G = 0.2f;


// ============================================================
// WATER SYSTEM
// ============================================================

// TODO: Determine after pump/flow hardware is selected.

// Maximum amount of time the water pump may run continuously [ms]
constexpr unsigned long WATER_PUMP_TIMEOUT_MS = 60000;

// Flow-meter calibration.
// Number of pulses generated per liter.
//
// Placeholder until actual flow sensor is selected.
constexpr float FLOW_SENSOR_PULSES_PER_LITER = 1.0f;


// ============================================================
// HEATER
// ============================================================

// Maximum safe water/heater temperature [deg C]
constexpr float MAX_TEMPERATURE_C = 100.0f;

// Minimum reasonable temperature reading [deg C]
// Used to help detect failed/disconnected sensors.
constexpr float MIN_VALID_TEMPERATURE_C = 0.0f;

// Maximum reasonable sensor reading [deg C]
constexpr float MAX_VALID_TEMPERATURE_C = 120.0f;

// Temperature tolerance for considering water "ready" [deg C]
constexpr float TEMPERATURE_TOLERANCE_C = 1.0f;

// Maximum time allowed to reach brewing temperature [ms]
constexpr unsigned long HEATER_TIMEOUT_MS = 180000;


// ============================================================
// CONTROL LOOP
// ============================================================

// General control-loop update interval [ms]
constexpr unsigned long CONTROL_INTERVAL_MS = 10;

// Temperature-control update interval [ms]
constexpr unsigned long TEMPERATURE_UPDATE_INTERVAL_MS = 100;


// ============================================================
// USER INTERFACE
// ============================================================

// Button debounce interval [ms]
constexpr unsigned long BUTTON_DEBOUNCE_MS = 50;

// Status update interval [ms]
constexpr unsigned long STATUS_UPDATE_INTERVAL_MS = 500;