#include <Arduino.h>

#include "timer.hpp"
#include "state_machine.hpp"
#include "input_manager.hpp"
#include "operators.hpp"

AvailableStates available_states;
StateMachine state_machine(&available_states);
Timer main_timer;
InputManager input_manager(&state_machine);

int FreeRAM(void);

void setup()
{
  Serial.begin(115200);
  main_timer.SetupTimer();
  state_machine.SetupStateMachine();
  input_manager.SetupInputManager();
}

void loop()
{
  main_timer.WaitForTimer();
  input_manager.CheckInputs();
  state_machine.Run();

  Serial << F("[memCheck] : ") << FreeRAM() << F("\n");
}

int FreeRAM()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}