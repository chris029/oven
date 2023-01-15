#include <Arduino.h>

#include "operators.hpp"

#include "timer.hpp"
#include "device_manager.hpp"
#include "state_machine.hpp"

AvailableStates available_states;
StateMachine state_machine(&available_states);
DeviceManager device_manager;
Timer main_timer;

void setup()
{
  main_timer.SetupTimer();
  device_manager.display.SetupDisplay();
  Serial.begin(115200);
}

void loop()
{
  main_timer.WaitForTimer();

  state_machine.Run();

  device_manager.display.DisplayState(
      device_manager.display.kStateLabel.idle);
  device_manager.pellet_spiral.Rotate();
  device_manager.pellet_spiral.SetDosingMode(
      device_manager.pellet_spiral.kAvailableDosingModes.start_up);
  device_manager.exhaust_fan.SetRPM(6969);
  device_manager.exhaust_fan.Start();
  device_manager.cartridge_heater.Start();
}