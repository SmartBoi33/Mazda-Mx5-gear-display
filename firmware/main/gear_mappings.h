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

struct SensorToGearMappings {
    SensorToGearMapping mappings[NUM_GEARS];
};

// Gear sensor mappings
extern SensorToGearMappings gear_mappings;

#endif
