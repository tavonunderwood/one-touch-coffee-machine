#include <Arduino.h>
#include "Grinder.h"
#include "pins.h"
#include "config.h"

namespace {
    bool motorRunning = false;
}

namespace Grinder {
    void begin() {
        pinMode(PIN_GRINDER_PWM, OUTPUT);
        pinMode(PIN_GRINDER_DIR, OUTPUT);
        stop();
    }

    void start() {
        digitalWrite(PIN_GRINDER_DIR, GRINDER_DIRECTION_HIGH ? HIGH : LOW);
        analogWrite(PIN_GRINDER_PWM, GRINDER_PWM_VALUE);
        motorRunning = true;
    }

    void stop() {
        analogWrite(PIN_GRINDER_PWM, 0);
        motorRunning = false;
    }

    bool isRunning() { return motorRunning; }
}