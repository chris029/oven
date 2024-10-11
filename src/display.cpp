#include "display.hpp"
#include "operators.hpp"

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
    this->top_label = label;
    this->Draw();
}

void Display::DisplayNextState()
{
    display.clearDisplay();

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

    this->UpdateStateLabel();
    this->Draw();
}

void Display::UpdateStateLabel()
{
    this->bot_label = *this->pStateLabels;
}

void Display::Draw()
{
    display.clearDisplay();
    // Normal 1:1 pixel scale
    display.setTextSize(1);
    // Start at top-left corner
    display.setCursor(0, 0);
    display.println("Current: " + this->top_label + "\n");
    // Draw 2X-scale text
    display.setTextSize(2);
    display.print(this->bot_label);
    display.display();
}