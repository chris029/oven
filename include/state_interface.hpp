#pragma once

#include "state_machine.hpp"
#include "Arduino.h"

class StateMachine;

class State
{
protected:
    uint32_t state_timer_ms = 0;

public:
    virtual void Enter(StateMachine *program) = 0;
    virtual void Execute(StateMachine *program) = 0;
    virtual void Exit(StateMachine *program) = 0;
    void ClearStateTimer() { state_timer_ms = 0; };
    // increment 100ms (based on main timer - /timer.hpp)
    void IncrementStateTimer() { state_timer_ms += 100; };
};