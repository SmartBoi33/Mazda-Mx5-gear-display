#include <Arduino.h>
#include "gear_mappings.h"
#include "gear.h"
#include "display.h"

// CONSTANTS
char default_gear = 'N';
char current_gear = 'N';

// SETUP
void setup() {
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    Serial.begin(9600);
}

// MAIN LOOP
void loop() {
    int sensors[NUM_SENSORS] = {
        analogRead(A0),
        analogRead(A3),
        analogRead(A1),
        analogRead(A2)
    };

    char next_gear = map_sensor_values_to_gear(sensors, gear_mappings);

    if (should_rerender(current_gear, next_gear)) {
        current_gear = next_gear;
        Serial.println(current_gear);
    }

    delay(50);
}
