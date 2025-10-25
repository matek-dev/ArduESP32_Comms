#pragma once
#include <Arduino.h>
#include "utils.h"

class UartComm
{
public:
    // Keep it simple: call begin() once, then service() in loop().
    void begin(int rxPin, int txPin, uint32_t baud = 115200);
    void service();

private:
    String _line;
};