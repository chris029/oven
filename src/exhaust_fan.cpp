#include <Arduino.h>

#include "exhaust_fan.hpp"
#include "operators.hpp"

void ExhaustFan::SetRPM(int rotation_speed)
{
    ExhaustFan::rpm = rotation_speed;
}

int ExhaustFan::GetRPM()
{
    return ExhaustFan::rpm;
}

void ExhaustFan::Start()
{
    // TODO: triac board handling
    Serial << "Fan rotates at RPM: " << rpm << "\n";
}

void ExhaustFan::Stop()
{
    // TODO: triac board handling
}