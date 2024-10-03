#ifndef GEAR_H
#define GEAR_H

struct SensorRange {
    int min;
    int max;
};

#define NUM_SENSORS 4
#define NUM_GEARS 9

struct SensorToGearMapping {
    char gear;
    SensorRange sensor_ranges[NUM_SENSORS];
};

char map_sensor_values_to_gear(const int sensor_values[NUM_SENSORS], const SensorToGearMapping mappings[NUM_GEARS]);
bool is_within_range(int value, SensorRange range);

#endif
