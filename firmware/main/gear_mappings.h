#ifndef GEAR_MAPPINGS_H
#define GEAR_MAPPINGS_H

#include "sensors.h"

#define NUM_GEARS 9

struct SensorRange {
    int min;
    int max;
};

struct SensorToGearMapping {
    char gear;
    SensorRange sensor_ranges[NUM_SENSORS];
};

// Gear sensor mappings
extern SensorToGearMapping gear_mappings[NUM_GEARS];

#endif
