#pragma once

#include "state_interface.hpp"
#include "state_machine.hpp"

class StateMachine;

class Idle : public State
{
public:
    void enter(StateMachine *sm) {}
    void execute(StateMachine *sm);
    void exit(StateMachine *sm);
};

class StartUp : public State
{
public:
    void enter(StateMachine *sm) {}
    void execute(StateMachine *sm);
    void exit(StateMachine *sm);
};

class ProgramOne : public State
{
public:
    void enter(StateMachine *sm) {}
    void execute(StateMachine *sm);
    void exit(StateMachine *sm);
};

struct AvailableStates
{
    Idle idle;
    StartUp startUp;
    ProgramOne programOne;
};