#include <Arduino.h>
#include <Servo.h>
#include "FilterSystem.h"
#include "pins.h"
#include "config.h"

namespace {
    Servo filterServo;
}

namespace FilterSystem {
    void begin() {
        // Write the target before attach to avoid an unintended jump to 90°.
        filterServo.write(FILTER_HOME_ANGLE_DEG);
        filterServo.attach(PIN_FILTER_SERVO);
        moveHome();
    }

    void moveToDump() {
        filterServo.write(FILTER_DUMP_ANGLE_DEG);
    }

    void moveHome() {
        filterServo.write(FILTER_HOME_ANGLE_DEG);
    }
}