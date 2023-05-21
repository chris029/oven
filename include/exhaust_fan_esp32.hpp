#pragma once

#include <Arduino.h>
#include <RBDdimmer.h>

const int MAXVALUE = 100;
const int zeroCrossPin = 26;
const int outPin = 25;

// these value were measured with an RPM meter
// when playing with a triac module
enum class RPMValues
{
    RPM_2660,
    RPM_1850,
    RPM_1690,
    RPM_1610,
    RPM_1470,
    RPM_1360,
    RPM_IDLE
};

class ExhaustFan
{
    dimmerLamp fan_driver{outPin, zeroCrossPin};
    int real_RPM;

public:
    void SetupFanDriver();
    void SetRPM(RPMValues rotation_speed);
    int GetRPM();
    void Start();
    void Stop();
};