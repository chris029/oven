#pragma once

#include "state_interface.hpp"
#include "state_machine.hpp"

#define START_UP_TIME 300000 // (5 * 60 * 1000) min * s * ms
#define TIME_FOR_CLEANING 1800000 // (30 * 60 * 1000) min * s * ms

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
    void Exit(StateMachine *sm);
};

class ProgramOne : public State
{    
    enum class SubState
    {
        FILL_UP,
        STALLING
    } sub_state;

public:
    ProgramOne();
    void Enter(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm);
};

class ProgramTwo : public State
{
    enum class SubState
    {
        FILL_UP,
        STALLING
    } sub_state;

public:
    ProgramTwo();
    void Enter(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm);
};

class TurnOff : public State
{
public:
    void Enter(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm);
};

class Cleaning : public State
{
    enum class SubState
    {
        FILL_UP,
        STALLING
    } sub_state;
    
public:
    Cleaning();
    void Enter(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm);
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