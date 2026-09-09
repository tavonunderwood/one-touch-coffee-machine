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
    serial.println("Machine Initialized. Current State: IDLE");
    changeState(MachiineState::IDLE);
}

void updateMachine()
{
    switch (currentState)
    {
        case MachineState::IDLE:
            serial.println("State: IDLE");
            changeState(MachineState::DOSING);
            break;

        case MachineState::DOSING:
            if(millis() - stateStartTime >= 2000)
            {
                serial.println("Dose Complete");
                changeState(MachineState::GRINDING);
            }
            break;

        case MachineState::GRINDING:
            if(millis() - stateStartTime >= 3000)
            {
                serial.println("Grinding Complete");
                changeState(MachineState::FILTERING);
            }
            break;

        case MachineState::WAITING_FOR_BREW:
            if(millis() - stateStartTime >= 4000)
            {
                serial.println("Filtering Complete");
                changeState(MachineState::CLEANING);
            }
            break;
        case MachineState::CLEANING:
            if(millis() - stateStartTime >= 2000)
            {
                serial.println("Cleaning Complete");
                changeState(MachineState::IDLE);
            }

        case MachineState::ERROR:
            serial.println("Error State Reached");
            break;
    }
}