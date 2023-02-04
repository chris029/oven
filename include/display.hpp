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
    const String *pStateLabels = &kStateLabel.program_1;
    uint8_t label_switch_cnt = 0;

    void SetupDisplay();
    void DisplayState(String label);
    void DisplayNextState();
};
