#include "UartComm.h"

void UartComm::begin(int rxPin, int txPin, uint32_t baud)
{
    Serial1.begin(baud, SERIAL_8N1, rxPin, txPin);
    delay(20);
    Serial.println("[UART] ready");
}

void UartComm::service()
{
    // USB Serial -> UART passthrough (handy during bring‑up)
    while (Serial.available())
        Serial1.write(Serial.read());

    // Read a line from UART and print it back to USB Serial
    while (Serial1.available())
    {
        char c = (char)Serial1.read();
        if (c == '')
        {
            util::rstrip(_line);
            if (_line.length())
            {
                Serial.print("[UART] ");
                Serial.println(_line);
            }
            _line = ""; // reset for next line
        }
        else
        {
            _line += c;
        }
    }
}