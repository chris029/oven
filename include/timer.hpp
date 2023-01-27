#pragma once

#define EXECUTION_WINDOW 100 // ms

class Timer
{
public:
    void SetupTimer();
    void WaitForTimer();
    int GetCurrentVal();
};