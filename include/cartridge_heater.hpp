#pragma once

#if defined(ARDUINO_ARCH_ESP32)
#define CARTRIDGE_HEATER_RELAY 32
#else
#define CARTRIDGE_HEATER_RELAY 9
#endif

class CartridgeHeater
{
public:
    void SetupHeater();
    void Start();
    void Stop();
};