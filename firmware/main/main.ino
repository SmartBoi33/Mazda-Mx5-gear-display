#include <Arduino.h>
#include "gear_mappings.h"
#include "gear.h"
#include "display.h"
#include "sensors.h"
#include "commands.h"

// GLOBAL VALUES
int delay_for_refresh_rate = get_delay_for_refresh_rate(30);

// SETUP
void setup() {
    setup_communication();
    setup_sensors();
    setup_display();
}

// MAIN LOOP
void loop() {
    if (is_calibration_mode()) {
        // calibrate(sensors, gear_mappings);
        set_display('C');
    } else { // Gear Detection Mode
        SensorData data = read_sensors();
        char gear = get_gear(data.values);
        set_display(gear);

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
