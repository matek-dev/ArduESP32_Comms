#pragma once
#include <Arduino.h>
#include <Wire.h>

class I2CComm
{
public:
    void begin(int sdaPin, int sclPin, uint32_t freq = 400000);
    void scanBus();

    // Minimal 8‑bit register helpers –
    bool writeReg8(uint8_t addr, uint8_t reg, uint8_t val);
    bool readReg8(uint8_t addr, uint8_t reg, uint8_t &val);
    bool readBurst(uint8_t addr, uint8_t reg, uint8_t *buf, size_t len);
};