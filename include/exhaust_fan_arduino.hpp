#pragma once

#include <Arduino.h>
#include <RBDdimmer.h>

#if defined(ARDUINO_ARCH_ESP32)
#define PSM_PIN 33
#define ZC_PIN 25
#else
#define PSM_PIN 12
#define ZC_PIN 2
#endif

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
    RPM_1360,
    RPM_IDLE
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