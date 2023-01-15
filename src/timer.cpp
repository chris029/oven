#include "Arduino.h"

#include "timer.hpp"
#include "operators.hpp"

// ISR is set for 1kHz -> timerCnt increments every 1ms
#define EXECUTION_WINDOW 100 // [ms]

volatile int timerCnt = 0;

ISR(TIMER1_COMPA_vect)
{
    timerCnt++;
}

void Timer::SetupTimer()
{
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    // set compare match register for 1kHz increments
    OCR1A = 15999; // = (16e6) / (1e3) - 1 (must be < 65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS10 for 1x prescaler
    TCCR1B |= (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
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

    while (timerCnt < 1000)
    {
        // wait 1000ms
    }

    timerCnt = 0;
}