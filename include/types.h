#pragma once
#include <Arduino.h>

// Full prototype sequence. DOSING/WATER/HEATER states are not needed.
enum class MachineState : uint8_t {
    IDLE,
    GRINDING,
    BREW_WAIT,
    DISPOSING,
    RETURNING,
    ERROR
};


