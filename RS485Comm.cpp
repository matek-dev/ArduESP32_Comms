#include "RS485Comm.h"

void RS485Comm::begin(int rxPin, int txPin, int dePin, uint32_t baud)
{
    _de = dePin;
    pinMode(_de, OUTPUT);
    _txMode(false); // start in RX mode

    Serial1.begin(baud, SERIAL_8N1, rxPin, txPin);
    delay(20);
    Serial.println("[RS485] ready");
}

void RS485Comm::sendBytes(const uint8_t *data, size_t len)
{
    _txMode(true);
    Serial1.write(data, len);
    Serial1.flush(); // make sure TX FIFO is empty before switching back
    _txMode(false);
}

void RS485Comm::sendLine(const String &s)
{
    String out = s;
    out += " ";
    sendBytes((const uint8_t *)out.c_str(), out.length());
}

void RS485Comm::service()
{
    // Print anything received as a line to USB Serial
    while (Serial1.available())
    {
        char c = (char)Serial1.read();
        if (c == ' ')
        {
            util::rstrip(_line);
            if (_line.length())
            {
                Serial.print("[RS485] ");
                Serial.println(_line);
            }
            _line = "";
        }
        else
        {
            _line += c;
        }
    }

    // Optional: let user type into Serial Monitor to send over RS‑485
    if (Serial.available())
    {
        String line = Serial.readStringUntil('');
        sendLine(line);
    }
}