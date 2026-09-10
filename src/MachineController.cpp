//Faciliates state machine

#include <Arduino.h>
#include "MachineController.h"

static MachineState currentState = MachineState::IDLE;
static unsigned long stateStartTime = 0;

void changeState(MachineState newState)
{
    currentState = newState;
    stateStartTime = millis();
}

void initializeMachine()
{
    Serial.println("Machine Initialized. Current State: IDLE");
    changeState(MachineState::IDLE);
}

void updateMachine()
{
    switch (currentState)
    {
        case MachineState::IDLE:
            Serial.println("State: IDLE");
            changeState(MachineState::DOSING);
            break;

        case MachineState::DOSING:
            if(millis() - stateStartTime >= 2000)
            {
                Serial.println("Dose Complete");
                changeState(MachineState::GRINDING);
            }
            break;

        case MachineState::GRINDING:
            if(millis() - stateStartTime >= 3000)
            {
                Serial.println("Grinding Complete");
                changeState(MachineState::WAITING_FOR_BREW);
            }
            break;

        case MachineState::WAITING_FOR_BREW:
            if(millis() - stateStartTime >= 4000)
            {
                Serial.println("Filtering Complete");
                changeState(MachineState::CLEANING);
            }
            break;
        case MachineState::CLEANING:
            if(millis() - stateStartTime >= 2000)
            {
                Serial.println("Cleaning Complete");
                changeState(MachineState::IDLE);
            }

        case MachineState::ERROR:
            Serial.println("Error State Reached");
            break;
    }
}