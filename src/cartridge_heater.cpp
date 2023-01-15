#include <Arduino.h>

#include "cartridge_heater.hpp"

#define CARTRIDGE_HEATER_RELAY 9

CartridgeHeater::CartridgeHeater()
{
    pinMode(CARTRIDGE_HEATER_RELAY, OUTPUT);
    // HIGH turns off a relay
    digitalWrite(CARTRIDGE_HEATER_RELAY, HIGH);
}

void CartridgeHeater::Start()
{
    digitalWrite(CARTRIDGE_HEATER_RELAY, LOW);
}

void CartridgeHeater::Stop()
{
    digitalWrite(CARTRIDGE_HEATER_RELAY, HIGH);
}