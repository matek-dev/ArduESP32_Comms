#include "I2CComm.h"

void I2CComm::begin(int sdaPin, int sclPin, uint32_t freq)
{
    Wire.begin(sdaPin, sclPin, freq);
    delay(20);
    Serial.println("[I2C] ready");
}

void I2CComm::scanBus()
{
    Serial.println("[I2C] scanning...");
    uint8_t found = 0;
    for (uint8_t a = 1; a < 127; ++a)
    {
        Wire.beginTransmission(a);
        if (Wire.endTransmission() == 0)
        {
            Serial.printf(" found 0x%02X", a);
            ++found;
        }
        delay(2);
    }
    if (!found)
        Serial.println(" no devices found");
}

bool I2CComm::writeReg8(uint8_t addr, uint8_t reg, uint8_t val)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(val);
    return Wire.endTransmission() == 0;
}

bool I2CComm::readReg8(uint8_t addr, uint8_t reg, uint8_t &val)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0)
        return false; // repeated start
    if (Wire.requestFrom((int)addr, 1) != 1)
        return false;
    val = Wire.read();
    return true;
}

bool I2CComm::readBurst(uint8_t addr, uint8_t reg, uint8_t *buf, size_t len)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0)
        return false;
    if (Wire.requestFrom((int)addr, (int)len) != (int)len)
        return false;
    for (size_t i = 0; i < len; ++i)
        buf[i] = Wire.read();
    return true;
}