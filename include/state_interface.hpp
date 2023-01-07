#pragma once

#include "state_machine.hpp"

class StateMachine;

class State
{
public:
    virtual void enter(StateMachine *program) = 0;
    virtual void execute(StateMachine *program) = 0;
    virtual void exit(StateMachine *program) = 0;
};