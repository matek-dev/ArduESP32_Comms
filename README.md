# Arduino Nano ESP32 Communication Templates

This repository contains simple, functional C++ templates for common communication protocols used in embedded systems. The code is written for the **Arduino Nano ESP32 (ESP32-S3)** and focuses on clarity, structure, and reusability.

Each protocol is implemented in its own file with clear comments and minimal abstraction - meant to serve as a foundation for real applications and as a reference for how these interfaces work at a low level.

---

## Overview
This project provides clean, working examples for:

- **UART (Serial1)** – basic RX/TX echo and line-based reading
- **I2C (Wire)** – bus scanning and simple register read/write helpers
- **SPI (SPIClass)** – master mode transfers with chip-select control
- **RS-485 (UART half-duplex)** – DE/RE control for direction-safe communication

The intent is to keep these examples short and easy to follow, while still covering the essential setup and handling for each interface.

---

## Project Structure
```
NanoESP32_Comms/
├── NanoESP32_Comms.ino // Main entry point – select which demo to run
├── UartComm.h / .cpp // UART communication template
├── I2CComm.h / .cpp // I2C communication template
├── SPIComm.h / .cpp // SPI communication template
├── RS485Comm.h / .cpp // RS-485 communication template
└── utils.h // Small helper functions (trim, hex dump)
```

---

## Getting Started

### 1. Clone or copy the project
Place this folder in your Arduino sketch directory (typically `~/Documents/Arduino/`).

### 2. Open the sketch
Open **NanoESP32_Comms.ino** in the Arduino IDE.

### 3. Select the board
- **Board:** Arduino Nano ESP32 (ESP32-S3)
- **Port:** whichever port the board enumerates as

### 4. Choose a demo
In `NanoESP32_Comms.ino`, set exactly one of the demo flags to `1`:
```cpp
#define RUN_UART_DEMO 1
#define RUN_I2C_DEMO 0
#define RUN_SPI_DEMO 0
#define RUN_RS485_DEMO 0
```

### 5. Configure pins
Edit the pin definitions at the top of the `.ino` file to match your hardware wiring:
```cpp
static constexpr int PIN_UART_RX = 5;
static constexpr int PIN_UART_TX = 4;
```

### 6. Upload and test
Upload the code and open the Serial Monitor at **115200 baud** to see logs.

---

## Demos

### UART
A basic Serial1 echo. Anything typed in the Serial Monitor is sent to Serial1, and received lines are printed back to the terminal.

### I2C
Scans the bus for connected devices and reads a sample register (WHOAMI at 0x75 on address 0x68) if present. Useful for quickly verifying connections.

### SPI
Performs a simple register read/write using SPI master mode with configurable chip select. Designed to be adapted for common SPI sensors and devices.

### RS-485
Implements half-duplex communication using UART with a DE/RE pin. Sends periodic packets and echoes any received messages. Useful for Modbus RTU or general serial bus applications.

---

## Customization
- Adjust pin assignments and communication speeds as needed.
- Use these templates as a starting point for your own sensor or peripheral drivers.
- The code is portable across ESP32 boards with minimal pin remapping.

---

## Dependencies
All dependencies come from the **Arduino Core for ESP32**:
- `Arduino.h`
- `Wire.h`
- `SPI.h`

No external libraries are required.
