#include "states.hpp"

#include "operators.hpp"

void Idle::Execute(StateMachine *sm)
{
    // while (true) that waits for a button hold
    // Serial << F("State Idle is running...\n");
    // Serial << F("Current timer value: ") << sm->timer << F("s\n");
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.idle);
    sm->device_manager.exhaust_fan.Start();
    sm->SetState(sm->available_states->start_up);
}

void Idle::Exit(StateMachine *sm)
{
    // Serial << "State Idle exits.\n";
}

void StartUp::Execute(StateMachine *sm)
{
    // Serial << "State StartUp is running...\n";
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.start_up);
    sm->device_manager.cartridge_heater.Start();
    sm->device_manager.exhaust_fan.SetRPM(800);
    sm->SetState(sm->available_states->program_1);
}

void StartUp::Exit(StateMachine *sm)
{
    // Serial << "State StartUp exits.\n";
}

void ProgramOne::Execute(StateMachine *sm)
{
    // Serial << "State Program_1 is running...\n";
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_1);
    sm->device_manager.cartridge_heater.Stop();
    sm->SetState(sm->available_states->program_2);
}

void ProgramOne::Exit(StateMachine *sm)
{
    // Serial << "State Program_1 exits.\n";
}

void ProgramTwo::Execute(StateMachine *sm)
{
    // Serial << "State Program_2 is running...\n";
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_2);
    sm->device_manager.cartridge_heater.Stop();
    sm->SetState(sm->available_states->idle);
}

void ProgramTwo::Exit(StateMachine *sm)
{
    // Serial << "State Program2 exits.\n";
}