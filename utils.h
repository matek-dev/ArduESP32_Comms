#pragma once
#include <Arduino.h>

namespace util {
// Remove trailing CR/LF so prints look clean
inline void rstrip(String &s) {
while (s.length() && (s.endsWith("
") || s.endsWith("
"))) {
s.remove(s.length() - 1);
}
}

// Tiny hex dump – good enough for field debugging
inline void hexDump(const uint8_t* buf, size_t len) {
for (size_t i = 0; i < len; ++i) {
if (i && (i % 16 == 0)) Serial.println();
if (buf[i] < 16) Serial.print('0');
Serial.print(buf[i], HEX);
Serial.print(' ');
}
Serial.println();
}
}