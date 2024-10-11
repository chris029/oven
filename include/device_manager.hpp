#include "display.hpp"
#if defined(ARDUINO_ARCH_ESP32)
#include "exhaust_fan_esp32.hpp"
#else
#include "exhaust_fan_arduino.hpp"
#endif
#include "pellet_spiral.hpp"
#include "cartridge_heater.hpp"

class DeviceManager
{
public:
    Display display;
    ExhaustFan exhaust_fan;
    PelletSpiral pellet_spiral;
    CartridgeHeater cartridge_heater;

    void SetupDevices();
};
