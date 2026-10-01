//Faciliates state machine

#include <Arduino.h>
#include "MachineController.h"
#include "types.h"
#include "config.h"

static MachineState currentState = MachineState::IDLE;
static unsigned long stateStartTime = 0;

#define DISCRETE_DOSING 2000
#define BASE_GRINDING_TIME 10000

volatile bool startButtonPressed = false;

//Updates the machine state and records the start time of the new state
void changeState(MachineState newState)
{
    currentState = newState;
    stateStartTime = millis();
}
//Initializes the machine and sets the initial state to IDLE
void initializeMachine()
{
    Serial.println("Machine Initialized. Current State: IDLE");
    changeState(MachineState::IDLE);
}

//Updates the machine state based on the current state and elapsed time
void updateMachine()
{
    switch (currentState)
    {
        case MachineState::IDLE:
            Serial.println("State: IDLE");
            //Wait for state change trigger (e.g., button press)
            if (startButtonPressed)
            {
                startButtonPressed = false;
                changeState(MachineState::DOSING);
            }
            break;

        case MachineState::DOSING:
            //turn rotor based on amount wanted
            if(millis() - stateStartTime >= DISCRETE_DOSING)
            {
                //turn off rotor
                //
                Serial.println("Dose Complete");
                changeState(MachineState::GRINDING);
            }
            if (measuredDoseComplete)
            {
                currentState = MachineState::GRINDING;
            }
            break;

        case MachineState::GRINDING:
            //Start grinding process
            Serial.println("State: GRINDING");
            //Turn on motor with proper PWM
            analogWrite(GRINDER_MOTOR_PIN, GRINDER_PWM_VALUE);
            //Stop grinding after the specified time
            if(millis() - stateStartTime >= 3000)
            {
                Serial.println("Grinding Complete");
                changeState(MachineState::WAITING_FOR_BREW);
            }
            break;

        case MachineState::WAITING_FOR_BREW:
            Serial.println("State: WAITING_FOR_BREW");
            Serial.println("Water is dispensed into the filter");
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