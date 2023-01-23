#pragma once

#include <Arduino.h>

struct StateLabels
{
    String idle = "IDLE...";
    String start_up = "START UP";
    String program_1 = "PROGRAM 1";
    String program_2 = "PROGRAM 2";
    String program_3 = "PROGRAM 3";
    String program_4 = "PROGRAM 4";
    String program_5 = "PROGRAM 5";
    String cleaning = "CLEANING";
    String turn_off = "TRUN OFF";
};

class Display
{
public:
    const StateLabels kStateLabel;

    void SetupDisplay();
    void DisplayState(String label);
};
