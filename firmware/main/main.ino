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
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    Serial.begin(9600);
    setup_display();
    display_gear(current_gear);
}

// MAIN LOOP
void loop() {
    bool isInCalibraitionMode = digitalRead(A5);
    int sensors[NUM_SENSORS] = {
        analogRead(A1),
        analogRead(A2),
        analogRead(A3),
        analogRead(A4)
    };
    if (isInCalibraitionMode) {
        // calibrate(sensors, gear_mappings);
        Serial.println("C");
    } else { // Gear Detection Mode
        char next_gear = map_sensor_values_to_gear(sensors, gear_mappings);
        bool is_a_match = should_rerender(current_gear, next_gear);
        if (is_a_match) {
            current_gear = next_gear;
            // Serial.println(current_gear);
            display_gear(current_gear); 
        }

        // Serial.print(sensors[0]);
        // Serial.print("  ");
        // Serial.print(sensors[1]);
        // Serial.print("  ");
        // Serial.print(sensors[2]);
        // Serial.print("  ");
        // Serial.print(sensors[3]);
        // Serial.print("  ");
        // Serial.print(300);
        // Serial.print("  ");
        // Serial.println(700);
    }

    delay(delay_for_refresh_rate);
}
