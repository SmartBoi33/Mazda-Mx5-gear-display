#ifndef SENSORS_H
#define SENSORS_H

#define NUM_SENSORS 4

void setup_sensors();

bool is_calibration_mode();

typedef struct {
    int values[NUM_SENSORS];
} SensorData;

SensorData read_sensors();

#endif
