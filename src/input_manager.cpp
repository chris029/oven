#include <Arduino.h>

#include "input_manager.hpp"
#include "operators.hpp"

#define BUTTON_PIN 10
#define THERMAL_RELAY_PIN 5

InputManager::InputManager(StateMachine *sm)
{
    this->sm = sm;
}

void InputManager::SetupInputManager()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(THERMAL_RELAY_PIN, INPUT_PULLUP);
}

void InputManager::CheckInputs()
{
    this->CheckButton();
    this->CheckTemperatureRelay();
}

void InputManager::CheckButton()
{
    Serial << "Button: checking button...\n";

    // if (digitalRead(BUTTON_PIN) == LOW)
    // {
    //     this->button_pressed = true;
    //     this->button_timer++;
    //     Serial << "Button: button pressed\n";
    //     Serial << "Button: held for " << this->button_timer << "00 ms\n";
    // }
    // else
    // {
    //     Serial << "Button: button released\n";
    //     this->button_pressed = false;
    //     this->sm->events.short_button_pressed = false;
    //     this->sm->events.long_button_pressed = false;
    // }

    // if (this->button_pressed)
    // {
    //     // 30 * 100 ms (main timer) = 3 s
    //     if (this->button_timer < 30)
    //     {
    //         this->sm->events.short_button_pressed = true;
    //     }
    //     else
    //     {
    //         this->sm->events.long_button_pressed = true;
    //     }
    //     this->button_timer = 0;
    // }
}

void InputManager::CheckTemperatureRelay()
{
    if (digitalRead(THERMAL_RELAY_PIN) == HIGH)
    {
        this->sm->events.heating_up_done = true;
    }
    else
    {
        this->sm->events.heating_up_done = false;
    }
}