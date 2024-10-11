#include "device_manager.hpp"

void DeviceManager::SetupDevices()
{
    DeviceManager::display.SetupDisplay();
    DeviceManager::exhaust_fan.SetupFanDriver();
    DeviceManager::pellet_spiral.SetupSpiral();
    DeviceManager::cartridge_heater.SetupHeater();
}