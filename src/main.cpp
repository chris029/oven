#include <Arduino.h>

#include "timer.hpp"
#include "state_machine.hpp"
#include "input_manager.hpp"
#include "operators.hpp"

StateMachine state_machine;
Timer main_timer;
InputManager input_manager(&state_machine);

void setup()
{
#if defined(ARDUINO_ARCH_ESP32)
  Serial.begin(921600);
#else
  Serial.begin(115200);
#endif
  main_timer.SetupTimer();
  state_machine.SetupStateMachine();
  input_manager.SetupInputManager();
}

void loop()
{
  main_timer.WaitForTimer();
  input_manager.CheckInputs();
  state_machine.Run();
}