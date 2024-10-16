#pragma once

#include "states.hpp"
#include "device_manager.hpp"

struct Events
{
    int short_button_pressed;
    int long_button_pressed;
    int heating_up_done;
    int short_button_pressed_cnt = 0;
};

class StateMachine
{
    State *current_state;
    State *previous_state;

public:
    String current_state_label;
    int timer_ms;
    Events events;
    AvailableStates available_states;
    DeviceManager device_manager;

    StateMachine();
    void SetupStateMachine();
    void Run();
    void SetNextState(State &new_state);
    void SetPreviousState(State &new_state);
    State *GetPreviousState();
    void ClearAllEvents();
    void ClearTimer();
};