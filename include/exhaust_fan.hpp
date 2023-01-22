#pragma once

#include <Arduino.h>
#include <RBDdimmer.h>

#define PSM_PIN 12
#define ZC_PIN 2
#define MAXVALUE 100

class ExhaustFan
{
    dimmerLamp fan_driver{PSM_PIN};
    int rpm = 0;

public:
    void SetupFanDriver();
    void SetRPM(int rotation_speed);
    int GetRPM();
    void Start();
    void Stop();
};