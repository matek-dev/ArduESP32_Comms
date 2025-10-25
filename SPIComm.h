#pragma once
#include <Arduino.h>
#include <SPI.h>

class SPIComm
{
public:
    void begin(int sck, int miso, int mosi, int cs, uint32_t hz = 8000000,
               BitOrder order = MSBFIRST, uint8_t mode = SPI_MODE0);

    // Very basic register helpers – adjust for your device’s protocol
    uint8_t readReg(uint8_t reg, uint8_t readBitMask = 0x80);
    void writeReg(uint8_t reg, uint8_t val);

private:
    int _cs{-1};
};