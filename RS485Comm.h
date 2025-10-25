#pragma once
#include <Arduino.h>
#include "utils.h"

class RS485Comm
{
public:
    void begin(int rxPin, int txPin, int dePin, uint32_t baud = 9600);
    void sendBytes(const uint8_t *data, size_t len);
    void sendLine(const String &s); // adds CRLF
    void service();                 // call in loop()

private:
    int _de{-1};
    String _line;
    inline void _txMode(bool en) { digitalWrite(_de, en ? HIGH : LOW); }
};