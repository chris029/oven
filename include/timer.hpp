#pragma once

namespace timer
{
    class Timer
    {
    public:
        void setup_timer();
        void wait_for_timer();
        int get_counter_val();
    };
}