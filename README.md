### Oven

## Dependencies (downloaded via platformIO):
* Adafruit SSD1306
* Adafruit GFX Library
* Adafruit BusIO
* RBDDimmer

## User action prior to compiling

It is necessary to modify RBDdimmer library to save up RAM.

Go to RBDmcuAVR.h and set line no. 84 to:
```c++
static const PROGMEM uint16_t powerBuf[] = {
```

Go to RBDmcuAVR.cpp and set line no. 105 to:
```c++
dimPulseBegin[this->current_num] = pgm_read_word(&(powerBuf[power]));
```
