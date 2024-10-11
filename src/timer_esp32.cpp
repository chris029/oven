#include "Arduino.h"

#include "timer.hpp"
#include "operators.hpp"

// ISR is set for 1kHz -> timerCnt increments every 1ms
volatile int timerCnt = 0;

void IRAM_ATTR Timer0_ISR()
{
    timerCnt++;
}

// ISR is set for 1kHz -> timerCnt increments every 1ms
void Timer::SetupTimer()
{
    Timer0_Cfg = timerBegin(1, 80, true);
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
    timerAlarmWrite(Timer0_Cfg, 1000, true);
    timerAlarmEnable(Timer0_Cfg);
}

int Timer::GetCurrentVal()
{
    return timerCnt;
}

void Timer::WaitForTimer()
{
    if (timerCnt > EXECUTION_WINDOW)
    {
        Serial << "=== ERROR: code execution longer than " << EXECUTION_WINDOW << "ms ===\n";
    }

    while (timerCnt < EXECUTION_WINDOW)
    {
    }

    timerCnt = 0;
}