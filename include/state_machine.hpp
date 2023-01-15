#pragma once

#include "state_interface.hpp"
#include "states.hpp"
#include "device_manager.hpp"

class State;
struct AvailableStates;

class StateMachine
{
    State *current_state;

public:
    AvailableStates *available_states;
    DeviceManager device_manager;

    StateMachine(AvailableStates *av_states);
    void SetupStateMachine();
    void Run();
    void SetState(State &new_state);
};