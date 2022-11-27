#pragma once

#include <Arduino.h>

enum Dosing
{
    level_1,
    level_2
};

namespace drivers
{
    class PelletSpiral
    {
        Dosing dosing = level_1;

    public:
        void rotate_spiral();
    };
}