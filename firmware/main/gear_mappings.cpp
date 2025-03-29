#include "gear_mappings.h"

SensorToGearMappings empty_mapping() {
    return SensorToGearMappings {
        {
            {'1', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'2', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'3', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'4', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'5', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}},
            {'R', {{INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}, {INT_MAX, INT_MIN}}}
        }
    };
}
