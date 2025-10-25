// NanoESP32_Comms.ino
// Board: Arduino Nano ESP32 (ESP32‑S3)
// Keep Serial (USB) for logs. Map pins below to your wiring.

#include <Arduino.h>
#include "UartComm.h"
#include "I2CComm.h"
#include "SPIComm.h"
#include "RS485Comm.h"

// === SELECT ONE DEMO TO RUN ===
#define RUN_UART_DEMO 0
#define RUN_I2C_DEMO 0
#define RUN_SPI_DEMO 0
#define RUN_RS485_DEMO 1

// === PIN CONFIG: change to your setup ===
// UART (plain) or RS‑485 both use Serial1 with these pins
static constexpr int PIN_UART_RX = 5; // from device TX (or RS‑485 RO)
static constexpr int PIN_UART_TX = 4; // to device RX (or RS‑485 DI)
static constexpr int PIN_RS485_DE = 2; // DE+RE tied together (HIGH=TX)

// I2C
static constexpr int PIN_I2C_SDA = 6;
static constexpr int PIN_I2C_SCL = 7;

// SPI
static constexpr int PIN_SPI_SCK = 10;
static constexpr int PIN_SPI_MISO = 9;
static constexpr int PIN_SPI_MOSI = 8;
static constexpr int PIN_SPI_CS = 3;

// Instances (kept global for simplicity)
UartComm uart;
I2CComm i2c;
SPIComm spi;
RS485Comm rs485;

void setup() {
Serial.begin(115200);
while (!Serial && millis() < 2000) {}
Serial.println("
=== Nano ESP32 Communications (multi‑file) ===");

#if RUN_UART_DEMO
uart.begin(PIN_UART_RX, PIN_UART_TX, 115200);
Serial.println("[main] UART demo ready – type in Serial Monitor.");
#endif
#if RUN_I2C_DEMO
i2c.begin(PIN_I2C_SDA, PIN_I2C_SCL, 400000); // 100k or 400k
i2c.scanBus();
// Example: try reading WHOAMI (0x75) at address 0x68 if you have an IMU
uint8_t who = 0;
if (i2c.readReg8(0x68, 0x75, who)) {
Serial.printf("[main] I2C 0x68 WHOAMI=0x%02X
", who);
} else {
Serial.println("[main] I2C example read failed (device may be absent)");
}
#endif
#if RUN_SPI_DEMO
spi.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI, PIN_SPI_CS, 8000000 /*8MHz*/);
// Example: device‑specific; read a WHOAMI register (0x0F) as a sanity check
uint8_t id = spi.readReg(0x0F, /*readBitMask=*/0x80); // many chips use MSB=1 for read
Serial.printf("[main] SPI WHOAMI=0x%02X (0x00/0xFF => check wiring)
", id);
#endif
#if RUN_RS485_DEMO
rs485.begin(PIN_UART_RX, PIN_UART_TX, PIN_RS485_DE, 9600);
rs485.sendLine("Hello RS‑485 peer!");
Serial.println("[main] RS‑485 demo listening...");
#endif
}

void loop() {
#if RUN_UART_DEMO
uart.service();
#endif
#if RUN_I2C_DEMO
// put sensor polling here; keep it light
delay(250);
#endif
#if RUN_SPI_DEMO
// poll or transfer as needed
delay(250);
#endif
}