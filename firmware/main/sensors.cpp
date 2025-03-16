#include <Arduino.h>
#include "sensors.h"

void setup_sensors() {
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
}

bool is_calibration_mode() {
    return digitalRead(A5);
}

SensorData read_sensors() {
    SensorData data = {
        .values = {
            analogRead(A1),
            analogRead(A2),
            analogRead(A3),
            analogRead(A4)
        }
    };

    return data;
}
