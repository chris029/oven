#include "exhaust_fan.hpp"
#include "operators.hpp"

void ExhaustFan::SetupFanDriver()
{
    ExhaustFan::fan_driver.begin(NORMAL_MODE, ON);
}

void ExhaustFan::SetRPM(int rotation_speed)
{
    ExhaustFan::rpm = rotation_speed;

    // calculate rpm to 'power' output value - it's not in Watts...
    int power = rpm / 10;

    ExhaustFan::fan_driver.setPower(power);
}

int ExhaustFan::GetRPM()
{
    return ExhaustFan::rpm;
}

void ExhaustFan::Start()
{
    // TODO: triac board handling
    int power = fan_driver.getPower();
    Serial << "Fan rotates at RPM: " << rpm << "\n";
    Serial << "Fan driver outputs: " << power << "\n";
}

void ExhaustFan::Stop()
{
    ExhaustFan::fan_driver.setState(OFF);
}