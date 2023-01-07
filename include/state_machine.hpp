#pragma once

#include "state_interface.hpp"
#include "states.hpp"

class State;
struct AvailableStates;

class StateMachine
{
public:
    State *currentState;
    AvailableStates *availableStates;

    StateMachine(AvailableStates *avStates);
    void run();
    void setState(State &newState);
};