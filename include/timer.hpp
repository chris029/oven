#pragma once

#define EXECUTION_WINDOW 100 // ms

class Timer
{
#if defined(ARDUINO_ARCH_ESP32)
    hw_timer_t *Timer0_Cfg = NULL;
#endif

public:
    void SetupTimer();
    void WaitForTimer();
    int GetCurrentVal();
};