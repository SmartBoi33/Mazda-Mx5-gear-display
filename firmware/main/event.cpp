#include <Arduino.h>
#include "event.h"

#define PIN 3
#define ON 0
#define OFF 1

void setup_event() {
    pinMode(3, INPUT_PULLUP); // assumes active LOW (0 = ON)
}

DigitalPinEvent read_event() {
    if (digitalRead(PIN) == ON) {
        unsigned long start = millis();

        // Wait for release or timeout
        while (digitalRead(PIN) == ON) {
            if (millis() - start > 5000) break; // safety timeout at 5 sec
        }

        unsigned long duration = millis() - start;
        if (duration >= 2500) { // for events longer than 2.5 sec we return LONG
            return LONG;
        } else {
            return SHORT;
        }
    }

    return NONE;
}
