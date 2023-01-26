#include "exhaust_fan.hpp"
#include "operators.hpp"

void ExhaustFan::SetupFanDriver()
{
    ExhaustFan::fan_driver.begin(NORMAL_MODE, ON);
}

void ExhaustFan::SetRPM(RPMValues rotation_speed)
{
    // pick 'power' output value - it's an index of a matrix
    // that contains timing for firing triac's gate...

    switch (rotation_speed)
    {
    case RPMValues::RPM_2660:
        ExhaustFan::real_RPM = 2660;
        ExhaustFan::fan_driver.setPower(70);
        break;
    case RPMValues::RPM_1850:
        ExhaustFan::real_RPM = 1850;
        ExhaustFan::fan_driver.setPower(40);
        break;
    case RPMValues::RPM_1690:
        ExhaustFan::real_RPM = 1690;
        ExhaustFan::fan_driver.setPower(38);
    case RPMValues::RPM_1610:
        ExhaustFan::real_RPM = 1610;
        ExhaustFan::fan_driver.setPower(37);
    case RPMValues::RPM_1470:
        ExhaustFan::real_RPM = 1470;
        ExhaustFan::fan_driver.setPower(36);
    case RPMValues::RPM_1360:
        ExhaustFan::real_RPM = 1360;
        ExhaustFan::fan_driver.setPower(35);
    }
}

int ExhaustFan::GetRPM()
{
    return ExhaustFan::real_RPM;
}

void ExhaustFan::Start()
{
    ExhaustFan::fan_driver.setState(ON);
}

void ExhaustFan::Stop()
{
    ExhaustFan::fan_driver.setState(OFF);
}