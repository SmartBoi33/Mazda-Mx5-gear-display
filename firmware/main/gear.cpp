#include "gear.h"

bool is_within_range(int value, SensorRange range) {
    return value >= range.min && value <= range.max;
}

char map_sensor_values_to_gear(const int sensor_values[NUMBER_OF_SENSORS], const SensorToGearMapping mappings[NUMBER_OF_GEARS]) {
    for (int i = 0; i < NUMBER_OF_GEARS; ++i) {
        const SensorToGearMapping& mapping = mappings[i];

        // Ensure gear is valid
        if (mapping.gear == ' ' || mapping.gear == '\0') {
            continue; // Skip empty mappings
        }

        bool match = true;
        for (int j = 0; j < NUMBER_OF_SENSORS; ++j) {
            if (!is_within_range(sensor_values[j], mapping.sensor_ranges[j])) {
                match = false;
                break;
            }
        }
        if (match) {
            return mapping.gear; // Return first matched gear
        }
    }

    return DEFAULT_GEAR; // If no match is found, return 'N'
}
