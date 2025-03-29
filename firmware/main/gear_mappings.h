#ifndef GEAR_MAPPINGS_H
#define GEAR_MAPPINGS_H

#include <limits.h>
#include "number_of_sensors.h"
#include "number_of_gears.h"

struct SensorRange {
    int min;
    int max;
};

struct SensorToGearMapping {
    char gear;
    SensorRange sensor_ranges[NUMBER_OF_SENSORS];
};

struct SensorToGearMappings {
    SensorToGearMapping mappings[NUMBER_OF_GEARS];
};

SensorToGearMappings empty_mapping();

#endif
