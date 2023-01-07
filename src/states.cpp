#include "states.hpp"

#include "operators.hpp"

void Idle::execute(StateMachine *sm)
{
    // while (true) that waits for a button hold
    Serial << "State Idle is running...\n";
    sm->setState(sm->avStates->startUp);
}

void Idle::exit(StateMachine *sm)
{
    Serial << "State Idle exits.\n";
}

void StartUp::execute(StateMachine *sm)
{
    Serial << "State StartUp is running...\n";
    sm->setState(sm->avStates->programOne);
}

void StartUp::exit(StateMachine *sm)
{
    Serial << "State StartUp exits.\n";
}

void ProgramOne::execute(StateMachine *sm)
{
    Serial << "State ProgramOne is running...\n";
    sm->setState(sm->avStates->idle);
}

void ProgramOne::exit(StateMachine *sm)
{
    Serial << "State ProgramOne exits.\n";
}