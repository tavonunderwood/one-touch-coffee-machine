#pragma once

#include <Arduino.h>

/*
 * ============================================================
 * Coffee Maker - Pin Definitions
 * ============================================================
 *
 * Central location for all Arduino pin assignments.
 *
 * NOTE:
 * Pin assignments marked TBD are temporary and may change
 * once the final hardware is selected.
 *
 * Arduino Uno:
 *   Digital: D0-D13
 *   PWM:     D3, D5, D6, D9, D10, D11
 *   Analog:  A0-A5
 *
 * D0/D1 are reserved for Serial communication.
 */

// ============================================================
// SERIAL
// ============================================================

// D0 - RX
// D1 - TX
// Reserved for USB/Serial debugging.


// ============================================================
// USER INPUT
// ============================================================

constexpr uint8_t PIN_START_BUTTON = 2;


// ============================================================
// BEAN DISPENSER
// ============================================================

// Servo or motor controlling bean dispensing mechanism.
// TBD once dispensing mechanism is finalized.

constexpr uint8_t PIN_BEAN_DISPENSER = 3;


// ============================================================
// GRINDER
// ============================================================

// PWM output to grinder motor driver.
constexpr uint8_t PIN_GRINDER_PWM = 5;

// Motor driver enable pin.
constexpr uint8_t PIN_GRINDER_ENABLE = 4;


// ============================================================
// LOAD CELL
// ============================================================

// Intended for load-cell amplifier (e.g. HX711).
// Exact interface depends on final amplifier.

constexpr uint8_t PIN_LOADCELL_DATA  = 6;
constexpr uint8_t PIN_LOADCELL_CLOCK = 7;


// ============================================================
// WATER SYSTEM
// ============================================================

// Water pump control.
constexpr uint8_t PIN_WATER_PUMP = 8;

// Optional valve control.
constexpr uint8_t PIN_WATER_VALVE = 9;


// ============================================================
// HEATER
// ============================================================

// Heater control signal.
// This will drive external power electronics, NOT the heater
// directly from the Arduino.

constexpr uint8_t PIN_HEATER_CONTROL = 10;


// ============================================================
// TEMPERATURE SENSOR
// ============================================================

// Placeholder for analog temperature sensor.
// May change depending on final sensor.

constexpr uint8_t PIN_TEMPERATURE_SENSOR = A0;


// ============================================================
// STATUS / USER INTERFACE
// ============================================================

// Built-in Arduino Uno LED.
constexpr uint8_t PIN_STATUS_LED = LED_BUILTIN;