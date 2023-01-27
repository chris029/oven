#pragma once

#include "state_interface.hpp"
#include "state_machine.hpp"

class StateMachine;

class Idle : public State
{

public:
    void Enter(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm) {}
};

class StartUp : public State
{
    enum class SubState
    {
        INITIAL_FILL_UP,
        INITIAL_STALLING,
        FILL_UP,
        STALLING
    } sub_state;

public:
    StartUp();
    void Enter(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm) {}
};

class ProgramOne : public State
{
public:
    void Enter(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm) {}
};

class ProgramTwo : public State
{
public:
    void Enter(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm) {}
};

class TurnOff : public State
{
public:
    void Enter(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm) {}
};

class Cleaning : public State
{
public:
    void Enter(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm) {}
};

struct AvailableStates
{
    Idle idle;
    StartUp start_up;
    ProgramOne program_1;
    ProgramTwo program_2;
    TurnOff turn_off;
    Cleaning cleaning;
};