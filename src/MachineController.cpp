#include <Arduino.h>
#include "MachineController.h"
#include "Grinder.h"
#include "FilterSystem.h"
#include "UserControls.h"
#include "pins.h"
#include "config.h"

namespace {
    MachineState state = MachineState::IDLE;
    unsigned long stateStartMs = 0;
    unsigned long activeGrindTimeMs = DEFAULT_GRIND_TIME_MS;

    void changeState(MachineState next) {
        // Turn off the motor as soon as grinding ends for any reason.
        if (state == MachineState::GRINDING && next != MachineState::GRINDING) {
            Grinder::stop();
        }

        state = next;
        stateStartMs = millis();
        digitalWrite(PIN_STATUS_LED, (next == MachineState::IDLE || next == MachineState::ERROR) ? LOW : HIGH);

        switch (next) {
            case MachineState::IDLE:
                Grinder::stop();
                FilterSystem::moveHome();
                Serial.println(F("[IDLE] Turn knob to choose grind time; press to start."));
                break;
            case MachineState::GRINDING:
                FilterSystem::moveHome();
                Grinder::start();
                Serial.print(F("[GRINDING] Motor ON for "));
                Serial.print(activeGrindTimeMs / 1000UL);
                Serial.println(F(" s."));
                break;
            case MachineState::BREW_WAIT:
                Serial.print(F("[BREW WAIT] Simulating brewing for "));
                Serial.print(BREW_SIMULATION_TIME_MS / 1000UL);
                Serial.println(F(" s."));
                break;
            case MachineState::DISPOSING:
                FilterSystem::moveToDump();
                Serial.println(F("[DISPOSING] Servo moved toward disposal position."));
                break;
            case MachineState::RETURNING:
                Grinder::stop();
                FilterSystem::moveHome();
                Serial.println(F("[RETURNING] Servo returning home."));
                break;
            case MachineState::ERROR:
                Grinder::stop();
                FilterSystem::moveHome();
                Serial.println(F("[ERROR] Motor stopped. Press knob to reset."));
                break;
        }
    }
}

void initializeMachine() {
    pinMode(PIN_STATUS_LED, OUTPUT);
    Grinder::begin();
    FilterSystem::begin();
    UserControls::begin();
    Serial.println(F("Coffee machine prototype initialized."));
    Serial.println(F("Press knob while operating to cancel the cycle."));
    changeState(MachineState::IDLE);
}

void updateMachine() {
    UserControls::update(state == MachineState::IDLE);

    if (UserControls::consumeButtonPress()) {
        if (state == MachineState::IDLE) {
            activeGrindTimeMs = UserControls::selectedGrindTimeMs(); // latch recipe
            changeState(MachineState::GRINDING);
        } else if (state == MachineState::ERROR) {
            changeState(MachineState::RETURNING);
        } else {
            Serial.println(F("[CANCEL] Cycle stopped by user."));
            changeState(MachineState::RETURNING);
        }
        return;
    }

    const unsigned long elapsedMs = millis() - stateStartMs;
    switch (state) {
        case MachineState::IDLE:
            break;

        case MachineState::GRINDING:
            if (elapsedMs >= GRINDER_HARD_TIMEOUT_MS) {
                changeState(MachineState::ERROR);
            } else if (elapsedMs >= activeGrindTimeMs) {
                changeState(MachineState::BREW_WAIT);
            }
            break;

        case MachineState::BREW_WAIT:
            if (elapsedMs >= BREW_SIMULATION_TIME_MS) {
                changeState(MachineState::DISPOSING);
            }
            break;

        case MachineState::DISPOSING:
            if (elapsedMs >= FILTER_DUMP_HOLD_MS) {
                changeState(MachineState::RETURNING);
            }
            break;

        case MachineState::RETURNING:
            if (elapsedMs >= FILTER_RETURN_SETTLE_MS) {
                changeState(MachineState::IDLE);
            }
            break;

        case MachineState::ERROR:
            // Stay stopped until user presses to reset.
            break;
    }
}

MachineState getMachineState() { return state; }