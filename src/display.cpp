#include "display.hpp"
#include "operators.hpp"

void drivers::Display::display_text()
{
    Serial << "Display text: " << disp_str << "\n";
}
