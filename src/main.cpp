#include <Arduino.h>

#include "timer.hpp"
#include "operators.hpp"
#include "device_manager.hpp"

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

  device_manager.display.display_text();
  device_manager.exhaust_fan.apply_rpm(2692);
  device_manager.pellet_spiral.rotate_spiral();
}