#pragma once

#if defined(ARDUINO_ARCH_ESP32)
#define BUTTON_PIN 5
#define THERMAL_RELAY_PIN 19
#else
#define BUTTON_PIN 10
#define THERMAL_RELAY_PIN 5
#endif

#define LONG_BUTTON_PRESS_CNT 5

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
