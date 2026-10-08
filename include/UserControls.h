#pragma once
#include <Arduino.h>

namespace UserControls {
    void begin();
    // Poll every loop. Changes the selected duration only while idle.
    void update(bool allowDurationChange);
    // A one-shot event: returns true once per debounced push.
    bool consumeButtonPress();
    unsigned long selectedGrindTimeMs();
}