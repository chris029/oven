#pragma once

#include <Arduino.h>

namespace drivers
{
    class ExhaustFan
    {
        int rpm = 1691;

    public:
        void apply_rpm(int);
    };
}