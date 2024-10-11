#pragma once

#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>

// 0.91'' = 128x32dpi;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// I2C address : 0x3C
// Pins in use (default) :
//  Arduino Nano: A4(SDA), A5(SCL)
//  ESP32: GPIO21(SDA), GPIO22(SCL)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

struct StateLabels
{
    String idle = "IDLE...";
    String start_up = "START UP";
    String program_1 = "PROGRAM 1";
    String program_2 = "PROGRAM 2";
    String program_3 = "PROGRAM 3";
    String program_4 = "PROGRAM 4";
    String program_5 = "PROGRAM 5";
    String cleaning = "CLEANING";
    String turn_off = "TRUN OFF";
};

class Display
{
public:
    const StateLabels kStateLabel;
    const String *pStateLabels = &kStateLabel.idle;
    int8_t label_switch_cnt = 0;
    String top_label = kStateLabel.idle;
    String bot_label = kStateLabel.idle;

    void SetupDisplay();
    void DisplayState(String label);
    void DisplayNextState();
    void Draw();
    void UpdateStateLabel();
};
