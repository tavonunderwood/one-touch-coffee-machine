#pragma once
#include <Arduino.h>

// ===== Serial diagnostics =====
constexpr unsigned long SERIAL_BAUD_RATE = 115200UL;

// ===== Rotary encoder with integral push button =====
// Set true if the knob's direction is reversed in your installation.
constexpr bool ENCODER_REVERSE_DIRECTION = false;
// Many mechanical encoders generate 4 valid transitions per click.
// If yours takes two clicks to change a setting, try 2.
constexpr uint8_t ENCODER_TRANSITIONS_PER_DETENT = 4;
constexpr unsigned long BUTTON_DEBOUNCE_MS = 40UL;

// ===== Grinder =====
// Current prototype runs the Pololu 50:1 gearmotor at fixed PWM.
// Dose is estimated from elapsed time; there is no speed feedback.
constexpr uint8_t GRINDER_PWM_VALUE = 255;  // 0..255
constexpr bool GRINDER_DIRECTION_HIGH = true;
constexpr unsigned long MIN_GRIND_TIME_MS = 5000UL;
constexpr unsigned long MAX_GRIND_TIME_MS = 90000UL;
constexpr unsigned long DEFAULT_GRIND_TIME_MS = 30000UL;
constexpr unsigned long GRIND_TIME_STEP_MS = 5000UL;
constexpr unsigned long GRINDER_HARD_TIMEOUT_MS = 95000UL;

// Optional estimate from an earlier calibration; NOT closed-loop dosing.
constexpr float APPROX_GRINDER_RPM = 200.0f;
constexpr float APPROX_GRAMS_PER_100_REVS = 6.13f;

// ===== Demonstration brewing =====
// No heater/water/pump used: this is just a timed pause.
constexpr unsigned long BREW_SIMULATION_TIME_MS = 10000UL;

// ===== Filter disposal servo =====
// These are servo commands, not guaranteed actual shaft displacement.
// Set HOME and DUMP to suit the physical linkage without binding.
constexpr uint8_t FILTER_HOME_ANGLE_DEG = 0;
constexpr uint8_t FILTER_DUMP_ANGLE_DEG = 55;
constexpr unsigned long FILTER_DUMP_HOLD_MS = 1500UL;
constexpr unsigned long FILTER_RETURN_SETTLE_MS = 1500UL;