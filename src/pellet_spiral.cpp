#include <Arduino.h>

#include "pellet_spiral.hpp"
#include "operators.hpp"

#define PELLET_SPIRAL_RELAY 8

PelletSpiral::PelletSpiral()
{
    // pinMode(PELLET_SPIRAL_RELAY, OUTPUT);
}

void PelletSpiral::SetDosingMode(DosingTimes dosing)
{
    PelletSpiral::dosing_mode = dosing;
}

float PelletSpiral::GetRotationTime()
{
    return PelletSpiral::dosing_mode.rotation_time_s;
}

float PelletSpiral::GetWaitingTime()
{
    return PelletSpiral::dosing_mode.waiting_time_s;
}

void PelletSpiral::Rotate()
{
    Serial
        << "Pellet spiral spins for: "
        << PelletSpiral::dosing_mode.rotation_time_s
        << "\n";

    // TODO:
    // how to handle time measurement inside a state machine

    // usage: turn on/off relays (GPIO) for defined amount of time
    // e.g. digitalWrite(PELLET_SPIRAL_RELAY, LOW);
}