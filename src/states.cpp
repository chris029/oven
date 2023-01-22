#include "states.hpp"

#include "operators.hpp"

void Idle::Execute(StateMachine *sm)
{
    // while (true) that waits for a button hold
    Serial << "State Idle is running...\n";
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.idle);
    sm->device_manager.exhaust_fan.Start();
    sm->SetState(sm->available_states->start_up);
}

void Idle::Exit(StateMachine *sm)
{
    Serial << "State Idle exits.\n";
}

void StartUp::Execute(StateMachine *sm)
{
    Serial << "State StartUp is running...\n";
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.start_up);
    sm->device_manager.cartridge_heater.Start();
    sm->device_manager.exhaust_fan.SetRPM(800);
    sm->SetState(sm->available_states->program_1);
}

void StartUp::Exit(StateMachine *sm)
{
    Serial << "State StartUp exits.\n";
}

void ProgramOne::Execute(StateMachine *sm)
{
    Serial << "State ProgramOne is running...\n";
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_1);
    sm->device_manager.cartridge_heater.Stop();
    sm->SetState(sm->available_states->idle);
}

void ProgramOne::Exit(StateMachine *sm)
{
    Serial << "State ProgramOne exits.\n";
}