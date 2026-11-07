#include <Arduino.h>
#include <Servo.h>
#include "Revolver.h"
#include "pins.h"
#include "config.h"
#include <EEPROM.h>

namespace {
    Servo filterServo;
}

namespace FilterSystem {
    void begin() {

        uint8_t stateStartMs = millis();
        //Begin homing sequence
        homing = true;


    }
    void turnCCW() 
    {
        stateStartMs = millis();
        digitalWrite(PIN_STEPPER_DIR, LOW); // Set direction to counter-clockwise
        //200 pulses per 1.8 degrees of rotation.  25 pulses = 45 degrees of rotation.
        //Send 25 puleses per second
        if (homing) {
            // Handle homing logic here
        }
        else {
            for (int i = 0; i < 25; i ++)
            {
                digitalWrite(PIN_STEPPER_STEP, HIGH);
                digitalWrite(PIN_STEPPER_STEP, LOW);
                while (millis() - stateStartMs >= CCW_TIME_MS) 
                {
                    // Wait for the specified time to elapse
                }
            }

            }
    }

    void turnCW() 
    {
        digitalWrite(PIN_STEPPER_DIR, HIGH); // Set direction to clockwise
        //200 pulses per 1.8 degrees of rotation.  25 pulses = 45 degrees of rotation.
        for (int i = 0; i < 25; i ++)
        {
            digitalWrite(PIN_STEPPER_STEP, HIGH);
            digitalWrite(PIN_STEPPER_STEP, LOW);
            while (millis() - stateStartMs >= CW_TIME_MS) 
            {
                // Wait for the specified time to elapse
            }
        }
    }
    void filterDispensed() {
        // Handle the logic for when the filter has been dispensed
        if (filtersRemaining == 0) return;

        filtersRemaining--;

        // Save to nonvolatile memory
        EEPROM.update(COUNT_ADDR, filtersRemaining);
    }


}