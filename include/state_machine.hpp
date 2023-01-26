#pragma once

#include "state_interface.hpp"
#include "states.hpp"
#include "device_manager.hpp"

class State;
struct AvailableStates;

struct Events
{
    uint8_t short_button_pressed;
    uint8_t long_button_pressed;
    uint8_t heating_up_done;
};

class StateMachine
{
    State *current_state;

public:
    uint32_t timer_ms;
    Events events;
    AvailableStates *available_states;
    DeviceManager device_manager;

    StateMachine(AvailableStates *av_states);
    void SetupStateMachine();
    void Run();
    void SetState(State &new_state);
    void ClearAllEvents();
    void ClearTimer();
};