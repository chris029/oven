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
    int8_t short_button_pressed_cnt = 0;
};

class StateMachine
{
    State *current_state;
    State *previous_state;

public:
    uint32_t timer_ms;
    Events events;
    AvailableStates *available_states;
    DeviceManager device_manager;

    StateMachine(AvailableStates *av_states);
    void SetupStateMachine();
    void Run();
    void SetNextState(State &new_state);
    void SetPreviousState(State &new_state);
    State *GetPreviousState();
    void ClearAllEvents();
    void ClearTimer();
};