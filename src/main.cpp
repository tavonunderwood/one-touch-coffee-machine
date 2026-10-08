#include <Arduino.h>
#include "MachineController.h"
#include "config.h"

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    initializeMachine();
}

void loop() {
    // No delay(): responsive encoder, push-to-start/cancel and timed states.
    updateMachine();
}

