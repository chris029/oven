#include <Arduino.h>

#include "pellet_spiral.hpp"
#include "operators.hpp"

void PelletSpiral::SetupSpiral()
{
    pinMode(PELLET_SPIRAL_RELAY, OUTPUT);
    // HIGH turns off a relay
    digitalWrite(PELLET_SPIRAL_RELAY, HIGH);
}

void PelletSpiral::Start()
{
    digitalWrite(PELLET_SPIRAL_RELAY, LOW);
    Serial << F("PELLET_SPIRAL PIN: ") << PELLET_SPIRAL_RELAY << F("\n");
}

void PelletSpiral::Stop()
{
    digitalWrite(PELLET_SPIRAL_RELAY, HIGH);
}