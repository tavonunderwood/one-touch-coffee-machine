#pragma once
#include <Arduino.h>

namespace Grinder {
    void begin();
    void start();
    void stop();
    bool isRunning();
}