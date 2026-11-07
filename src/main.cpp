#include <Arduino.h>
#include "MachineController.h"
#include "config.h"

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    initializeMachine();

        // Load saved count, or initialize safely
    if (EEPROM.read(INIT_ADDR) != INIT_MARKER) {
        filtersRemaining = 0; // Require initial refill
        EEPROM.update(COUNT_ADDR, filtersRemaining);
        EEPROM.update(INIT_ADDR, INIT_MARKER);
    } else {
        filtersRemaining = EEPROM.read(COUNT_ADDR);

        if (filtersRemaining > MAX_FILTERS) {
            filtersRemaining = 0;
        }
    }
}

void loop() {
    // No delay(): responsive encoder, push-to-start/cancel and timed states.
    updateMachine();
}

