#include "Arduino.h"

#include "timer.hpp"
#include "operators.hpp"

// ISR is set for 1kHz -> timerCnt increments every 1ms
volatile int timerCnt = 0;

ISR(TIMER4_COMPA_vect)
{
    timerCnt++;
}

// ISR is set for 1kHz -> timerCnt increments every 1ms
void Timer::SetupTimer()
{
    TCCR4A = 0; // set entire TCCR4A register to 0
    TCCR4B = 0; // same for TCCR4B
    // set compare match register for 1kHz increments
    OCR4A = 15999; // = (16e6) / (1e3) - 1 (must be < 65536)
    // turn on CTC mode
    TCCR4B |= (1 << WGM12);
    // Set CS10 for 1x prescaler
    TCCR4B |= (1 << CS10);
    // enable timer compare interrupt
    TIMSK4 |= (1 << OCIE1A);
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