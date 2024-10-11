#include <Arduino.h>

#include "input_manager.hpp"
#include "state_machine.hpp"
#include "operators.hpp"

InputManager::InputManager(StateMachine *sm)
{
    this->sm = sm;
}

void InputManager::SetupInputManager()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    // pinMode(THERMAL_RELAY_PIN, INPUT_PULLUP);
}

void InputManager::CheckInputs()
{
    this->CheckButton();
    this->CheckSerial();
    // this->CheckTemperatureRelay();
}

void InputManager::CheckButton()
{
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
        if (this->button_timer >= LONG_BUTTON_PRESS_CNT)
        {
            InputManager::SetEventLongButtonPress();
        }
    }

    if (!this->button_pressed && this->button_timer > 0)
    {
        InputManager::SetEventShortButtonPress();
    }
}

void InputManager::CheckSerial()
{
    if (Serial.available())
    {
        byte serialKey = Serial.read();
        Serial << F("Key: ") << serialKey << F("\n");

        if (serialKey == KEY_S_ASCII_SHORT_BUTTON_OVER_SERIAL)
        {
            InputManager::SetEventShortButtonPress();
        }

        if (serialKey == KEY_L_ASCII_SHORT_BUTTON_OVER_SERIAL)
        {
            InputManager::SetEventLongButtonPress();
        }
    }
}

void InputManager::SetEventShortButtonPress()
{
    Serial << F("short button press\n");
    this->sm->events.short_button_pressed = true;
    this->button_pressed = false;
    this->button_timer = 0;
}

void InputManager::SetEventLongButtonPress()
{
    Serial << F("long button press\n");
    // 30 * 100 ms (main timer) = 3 s
    this->sm->events.long_button_pressed = true;
    this->button_timer = 0;
    this->button_released = false;
}

// Checking timing now instead of a thermal relay
//
// void InputManager::CheckTemperatureRelay()
// {
//     if (digitalRead(THERMAL_RELAY_PIN) == HIGH)
//     {
//         this->sm->events.heating_up_done = true;
//     }
//     else
//     {
//         this->sm->events.heating_up_done = false;
//     }
// }