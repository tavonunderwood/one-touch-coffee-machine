#pragma once
#include <Arduino.h>

// Arduino Mega 2560 pin assignments. All control signals use shared GND.

// KY-040 / EC11-style rotary encoder: CLK=A, DT=B, SW=push button.
constexpr uint8_t PIN_ENCODER_A = 22;
constexpr uint8_t PIN_ENCODER_B = 23;
constexpr uint8_t PIN_ENCODER_BUTTON = 2;

// Cytron MD30C in PWM/DIR mode: PWM controls speed, DIR controls direction.
constexpr uint8_t PIN_GRINDER_PWM = 5;
constexpr uint8_t PIN_GRINDER_DIR = 4;

// Standard hobby servo signal. Power servo from an adequate 5-6 V rail,
// NOT directly from the Arduino 5V output pin.
constexpr uint8_t PIN_FILTER_SERVO = 11;
constexpr uint8_t PIN_STATUS_LED = LED_BUILTIN;