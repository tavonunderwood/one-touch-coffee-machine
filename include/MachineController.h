#ifndef MACHINE_CONTROLLER_H
#define MACHINE_CONTROLLER_H

enum class MachineState
{
    IDLE,
    DOSING,
    GRINDING,
    WAITING_FOR_BREW,
    CLEANING,
    ERROR
};

void initializeMachine();
void updateMachine();

#endif