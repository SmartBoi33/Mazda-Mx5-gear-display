#ifndef GEAR_H
#define GEAR_H

#include "gear_mappings.h"

char map_sensor_values_to_gear(const int sensor_values[NUM_SENSORS], const SensorToGearMapping mappings[NUM_GEARS]);
bool is_within_range(int value, SensorRange range);

#endif
