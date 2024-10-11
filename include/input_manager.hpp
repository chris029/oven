#pragma once

#if defined(ARDUINO_ARCH_ESP32)
#define BUTTON_PIN 14
#define THERMAL_RELAY_PIN 19
#else
#define BUTTON_PIN 10
#define THERMAL_RELAY_PIN 5
#endif

#define LONG_BUTTON_PRESS_CNT 5
#define KEY_B_ASCII_SHORT_BUTTON_OVER_SERIAL 98
#define KEY_S_ASCII_SHORT_BUTTON_OVER_SERIAL 115
#define KEY_L_ASCII_SHORT_BUTTON_OVER_SERIAL 108

class StateMachine;

class InputManager
{
    uint8_t button_timer;
    uint8_t button_pressed = false;
    uint8_t button_released = true;
    StateMachine *sm;
    void CheckButton();
    void CheckSerial();
    void CheckTemperatureRelay();
    void SetEventShortButtonPress();
    void SetEventLongButtonPress();

public:
    InputManager(StateMachine *sm);
    void SetupInputManager();
    void CheckInputs();
};
