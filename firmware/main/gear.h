#ifndef GEAR_H
#define GEAR_H

#include "sensor_data.h"
#include "gear_mappings.h"

const char DEFAULT_GEAR = 'N';

char map_sensor_values_to_gear(const int sensor_values[NUMBER_OF_SENSORS], const SensorToGearMapping mappings[NUMBER_OF_GEARS]);

#endif
