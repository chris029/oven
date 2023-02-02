#pragma once

#include "state_interface.hpp"
#include "state_machine.hpp"

#define START_UP_TIME 300000         // (5 * 60 * 1000) min * s * ms
#define TIME_FOR_CLEANING 1800000    // (30 * 60 * 1000) min * s * ms
#define MINIMUM_STATE_DURATION 60000 // (1 * 60 * 1000) min * s * ms

#define INITIAL_FILL_UP_DURATION 110000  // (110 * 1000) s * ms
#define INITIAL_STALLING_DURATION 170000 // (170 * 1000) s * ms

#define STARTUP_FILL_UP_DURATION 1100  // ms
#define STARTUP_STALLING_DURATION 2900 // ms

#define PROGRAM_ONE_FILL_UP_DURATION 1100  // ms
#define PROGRAM_ONE_STALLING_DURATION 2900 // ms

#define PROGRAM_TWO_FILL_UP_DURATION 1500  // ms
#define PROGRAM_TWO_STALLING_DURATION 2500 // ms

#define PROGRAM_THREE_FILL_UP_DURATION 1900  // ms
#define PROGRAM_THREE_STALLING_DURATION 2100 // ms

#define PROGRAM_FOUR_FILL_UP_DURATION 2200  // ms
#define PROGRAM_FOUR_STALLING_DURATION 1800 // ms

#define PROGRAM_FIVE_FILL_UP_DURATION 2500  // ms
#define PROGRAM_FIVE_STALLING_DURATION 1500 // ms

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

class ProgramThree : public State
{
    enum class SubState
    {
        FILL_UP,
        STALLING
    } sub_state;

public:
    ProgramThree();
    void Enter(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm);
};

class ProgramFour : public State
{
    enum class SubState
    {
        FILL_UP,
        STALLING
    } sub_state;

public:
    ProgramFour();
    void Enter(StateMachine *sm);
    void Execute(StateMachine *sm);
    void Exit(StateMachine *sm);
};

class ProgramFive : public State
{
    enum class SubState
    {
        FILL_UP,
        STALLING
    } sub_state;

public:
    ProgramFive();
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
    ProgramThree program_3;
    ProgramFour program_4;
    ProgramFive program_5;
    TurnOff turn_off;
    Cleaning cleaning;
};