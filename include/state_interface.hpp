#pragma once

#include "state_machine.hpp"

class StateMachine;

class State
{
public:
    virtual void Enter(StateMachine *program) = 0;
    virtual void Execute(StateMachine *program) = 0;
    virtual void Exit(StateMachine *program) = 0;
};