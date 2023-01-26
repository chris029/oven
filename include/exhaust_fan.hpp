#pragma once

#include <Arduino.h>
#include <RBDdimmer.h>

#define PSM_PIN 12
#define ZC_PIN 2
#define MAXVALUE 100

// these value were measured with an RPM meter
// when playing with a triac module
enum class RPMValues
{
    RPM_2660,
    RPM_1850,
    RPM_1690,
    RPM_1610,
    RPM_1470,
    RPM_1360
};

class ExhaustFan
{
    dimmerLamp fan_driver{PSM_PIN};
    int real_RPM;

public:
    void SetupFanDriver();
    void SetRPM(RPMValues rotation_speed);
    int GetRPM();
    void Start();
    void Stop();
};