#include <Arduino.h>

#include "timer.hpp"
#include "operators.hpp"
#include "device_manager.hpp"

drivers::DeviceManager driver_manager;
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

  driver_manager.display.display_text();
  driver_manager.exhaust_fan.apply_rpm(2692);
  driver_manager.pellet_spiral.rotate_spiral();
}