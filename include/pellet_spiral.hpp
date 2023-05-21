#pragma once

#if defined(ARDUINO_ARCH_ESP32)
#define PELLET_SPIRAL_RELAY 13
#else
#define PELLET_SPIRAL_RELAY 8
#endif

class PelletSpiral
{

public:
    PelletSpiral();
    void Start();
    void Stop();
};