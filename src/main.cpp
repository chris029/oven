#include <Arduino.h>

#include "operators.hpp"

#include "timer.hpp"
#include "device_manager.hpp"
#include "state_machine.hpp"

AvailableStates availableStates;
StateMachine state_machine(&availableStates);
drivers::DeviceManager device_manager;
timer::Timer timer1;

void setup()
{
  pinMode(13, OUTPUT);
  timer1.setup_timer();
  Serial.begin(115200);
}

void loop()
{
  timer1.wait_for_timer();

  state_machine.run();
  device_manager.display.display_text();
  device_manager.exhaust_fan.apply_rpm(2692);
  device_manager.pellet_spiral.rotate_spiral();
}