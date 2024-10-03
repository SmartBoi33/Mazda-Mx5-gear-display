#include "gear.h"

bool is_within_range(int value, SensorRange range) {
    return value >= range.min && value <= range.max;
}

char map_sensor_values_to_gear(const int sensor_values[NUM_SENSORS], const SensorToGearMapping mappings[NUM_GEARS]) {
    for (int i = 0; i < NUM_GEARS; ++i) {
        const SensorToGearMapping& mapping = mappings[i];
        bool match = true;
        for (int j = 0; j < NUM_SENSORS; ++j) {
            if (!is_within_range(sensor_values[j], mapping.sensor_ranges[j])) {
                match = false;
                break;
            }
        }
        if (match) {
            return mapping.gear;
        }
    }
    return 'N';
}
