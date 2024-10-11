#pragma once

#if defined(ARDUINO_ARCH_ESP32)
#define PELLET_SPIRAL_RELAY 26
#else
#define PELLET_SPIRAL_RELAY 8
#endif

class PelletSpiral
{

public:
    void SetupSpiral();
    void Start();
    void Stop();
};