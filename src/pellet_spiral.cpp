#include <Arduino.h>

#include "pellet_spiral.hpp"
#include "operators.hpp"

PelletSpiral::PelletSpiral()
{
    pinMode(PELLET_SPIRAL_RELAY, OUTPUT);
    // HIGH turns off a relay
    digitalWrite(PELLET_SPIRAL_RELAY, HIGH);
}

void PelletSpiral::Start()
{
    digitalWrite(PELLET_SPIRAL_RELAY, LOW);
}

void PelletSpiral::Stop()
{
    digitalWrite(PELLET_SPIRAL_RELAY, HIGH);
}