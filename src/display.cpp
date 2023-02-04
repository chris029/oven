#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "display.hpp"
#include "operators.hpp"

// 0.91'' = 128x32dpi;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// I2C address : 0x3C
// Pins in use (default) : A4(SDA), A5(SCL)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void testdrawstyles(void);

void Display::SetupDisplay()
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

    display.setTextColor(SSD1306_WHITE);
    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(1000);
}

void Display::DisplayState(String label)
{
    display.clearDisplay();

    // Normal 1:1 pixel scale
    display.setTextSize(1);
    // Start at top-left corner
    display.setCursor(0, 0);
    display.println(F("State:\n"));
    // Draw 2X-scale text
    display.setTextSize(2);
    display.print(label);
    display.display();
}

void Display::DisplayNextState()
{
    display.clearDisplay();

    // Normal 1:1 pixel scale
    display.setTextSize(1);
    // Start at top-left corner
    display.setCursor(0, 0);
    display.println(F("State:\n"));
    // Draw 2X-scale text
    display.setTextSize(2);
    display.print(*this->pStateLabels);
    display.display();

    if (this->label_switch_cnt < 4)
    {
        this->pStateLabels++;
        this->label_switch_cnt++;
    }
    else
    {
        this->pStateLabels = &kStateLabel.program_1;
        this->label_switch_cnt = 0;
    }
}