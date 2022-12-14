#include "Arduino.h"

#include "display.hpp"
#include "exhaust_fan.hpp"
#include "pellet_spiral.hpp"

namespace drivers
{
    class DeviceManager
    {
    public:
        Display display;
        ExhaustFan exhaust_fan;
        PelletSpiral pellet_spiral;
    };
}
