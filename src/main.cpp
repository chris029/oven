#include <Arduino.h>

#include "timer.hpp"
#include "state_machine.hpp"

AvailableStates available_states;
StateMachine state_machine(&available_states);
Timer main_timer;

void setup()
{
  Serial.begin(115200);
  main_timer.SetupTimer();
  state_machine.SetupStateMachine();
}

void loop()
{
  main_timer.WaitForTimer();
  state_machine.Run();
}