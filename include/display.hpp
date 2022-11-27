#pragma once

#include <Arduino.h>

namespace drivers
{
    class Display
    {
        String disp_str = "example_text";

    public:
        void display_text();
    };
}