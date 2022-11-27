#include "exhaust_fan.hpp"
#include "operators.hpp"

void drivers::ExhaustFan::apply_rpm(int new_rpm)
{
    rpm = new_rpm;
    Serial << "New rpm value = " << rpm << "\n";
}