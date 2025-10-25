#include "SPIComm.h"

void SPIComm::begin(int sck, int miso, int mosi, int cs, uint32_t hz,
                    BitOrder order, uint8_t mode)
{
    _cs = cs;
    pinMode(_cs, OUTPUT);
    digitalWrite(_cs, HIGH);

    SPI.begin(sck, miso, mosi, cs);
    SPI.beginTransaction(SPISettings(hz, order, mode));
    delay(20);
    Serial.println("[SPI] ready");
}

uint8_t SPIComm::readReg(uint8_t reg, uint8_t readBitMask)
{
    digitalWrite(_cs, LOW);
    SPI.transfer(reg | readBitMask); // many chips use MSB=1 for read
    uint8_t v = SPI.transfer(0x00);
    digitalWrite(_cs, HIGH);
    return v;
}

void SPIComm::writeReg(uint8_t reg, uint8_t val)
{
    digitalWrite(_cs, LOW);
    SPI.transfer(reg & 0x7F); // many chips use MSB=0 for write
    SPI.transfer(val);
    digitalWrite(_cs, HIGH);
}