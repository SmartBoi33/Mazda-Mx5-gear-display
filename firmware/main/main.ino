#include <Arduino.h>
#include "gear_mappings.h"
#include "gear.h"
#include "display.h"

// CONSTANTS
char default_gear = 'N';
// GLOBAL VARIABLES
char current_gear = 'N';
int delay_for_refresh_rate = get_delay_for_refresh_rate(30);

// SETUP
void setup() {
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    Serial.begin(9600);
    Serial.println(current_gear);
}

// MAIN LOOP
void loop() {
    bool isInCalibraitionMode = digitalRead(A4);
    int sensors[NUM_SENSORS] = {
        analogRead(A0),
        analogRead(A3),
        analogRead(A1),
        analogRead(A2)
    };
    if (isInCalibraitionMode) {
        // calibrate(sensors, gear_mappings);
        Serial.println("C");
    } else { // Gear Detection Mode
        char next_gear = map_sensor_values_to_gear(sensors, gear_mappings);

        if (should_rerender(current_gear, next_gear)) {
            current_gear = next_gear;
            Serial.println(current_gear);
        }
    }

    delay(delay_for_refresh_rate);
}
