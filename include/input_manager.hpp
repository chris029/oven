#pragma once

#include "state_machine.hpp"

class StateMachine;

class InputManager
{
    uint8_t button_timer;
    uint8_t button_pressed = false;
    uint8_t button_released = true;
    StateMachine *sm;
    void CheckButton();
    void CheckTemperatureRelay();

public:
    InputManager(StateMachine *sm);
    void SetupInputManager();
    void CheckInputs();
};
