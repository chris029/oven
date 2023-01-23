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
    // Serial << F("Button: checking button...\n");

    if (digitalRead(BUTTON_PIN) == LOW)
    {
        this->button_pressed = true;
    }
    else
    {
        this->button_pressed = false;
        this->button_released = true;
    }

    if (this->button_pressed && this->button_released)
    {
        this->button_timer++;
        // Serial << F("Button: held for ") << this->button_timer << F("00 ms\n");
        if (this->button_timer >= 30)
        {
            // 30 * 100 ms (main timer) = 3 s
            this->sm->events.long_button_pressed = true;
            // Serial << F("Event: long press\n");
            this->button_timer = 0;
            this->button_released = false;
        }
    }

    if (!this->button_pressed && this->button_timer > 0)
    {
        this->sm->events.short_button_pressed = true;
        // Serial << F("Event: short press\n");
        this->button_pressed = false;
        this->button_timer = 0;
    }
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