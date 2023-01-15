#pragma once

#include "state_interface.hpp"
#include "states.hpp"

class State;
struct AvailableStates;

class StateMachine
{
public:
    State *current_state;
    AvailableStates *available_states;

    StateMachine(AvailableStates *av_states);
    void Run();
    void SetState(State &new_state);
};