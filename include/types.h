#pragma once
#include <Arduino.h>

// Full prototype sequence
enum class MachineState : uint8_t {
    IDLE,
    GRINDING,
    BREW_WAIT,
    DISPOSING,
    RETURNING,
    ERROR
};


