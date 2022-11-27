#pragma once

#include <Arduino.h>

template <typename T>
Print &operator<<(Print &printer, T value)
{
    printer.print(value);
    return printer;
}