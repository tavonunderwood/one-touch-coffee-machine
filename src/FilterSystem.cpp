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
        // Attach the servo after setting the initial position to avoid a sudden jump.
        filterServo.attach(PIN_FILTER_SERVO);
        moveHome();
    }

    void moveToDump() 
    {
        //Set this as the target angle for the filter disposal servo.
        filterServo.write(FILTER_DUMP_ANGLE_DEG);
        //Shimmy Sequence
        for (int i = 0; i < 25; i ++)
        {
            filterServo.write(30);
            delay(100);
            filterServo.write(26);
            delay(100);
        }
    }

    void moveHome() 
    {
        //Set this as the target angle for the filter disposal servo to return to home position.
        filterServo.write(FILTER_HOME_ANGLE_DEG);
    }
}