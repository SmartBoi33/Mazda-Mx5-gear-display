#include <Arduino.h>

// TYPES
// ============================================================================================= //

enum Gear {
    REVERSE = -1,
    NEUTRAL = 0,
    FIRST = 1,
    SECOND = 2,
    THIRD = 3,
    FOURTH = 4,
    FIFTH = 5
};

struct SensorRange {
    int min;
    int max;
};

// Define the number of sensors
#define NUM_SENSORS 4

struct SensorToGearMapping {
    Gear gear;
    SensorRange sensor_ranges[NUM_SENSORS];  // C-style array for sensor ranges
};

// CONSTANTS
// ============================================================================================= //

Gear current_gear = Gear::NEUTRAL;

// Create a list of mappings for each gear
SensorToGearMapping gear_mappings[] = {
    {Gear::REVERSE, {{400, 450}, {380, 420}, {400, 450}, {370, 410}}},
    {Gear::NEUTRAL, {{530, 540}, {490, 510}, {530, 540}, {500, 520}}},
    {Gear::FIRST, {{90, 110}, {80, 100}, {95, 115}, {100, 120}}},
    {Gear::SECOND, {{190, 210}, {180, 200}, {195, 215}, {200, 220}}},
    {Gear::THIRD, {{290, 310}, {280, 300}, {295, 315}, {300, 320}}},
    {Gear::FOURTH, {{390, 410}, {380, 400}, {395, 415}, {400, 420}}},
    {Gear::FIFTH, {{490, 510}, {480, 500}, {495, 515}, {500, 520}}},
};

// SETUP
// ============================================================================================= //

void setup() {
    pinMode(A0, INPUT);  // Sensor left
    pinMode(A1, INPUT);  // Sensor top
    pinMode(A2, INPUT);  // Sensor right
    pinMode(A3, INPUT);  // Sensor bottom
    Serial.begin(9600);
    // clear display
}

// MAIN LOOP
// ============================================================================================= //

void loop() {
    // Read signals
    int hall_sensor_value_1 = analogRead(A0);  // 0 - 1023
    int hall_sensor_value_2 = analogRead(A3);
    int hall_sensor_value_3 = analogRead(A1);
    int hall_sensor_value_4 = analogRead(A2);

    // Store sensor values in a plain C-style array using NUM_SENSORS
    int sensors[NUM_SENSORS] = {
        hall_sensor_value_1,
        hall_sensor_value_2,
        hall_sensor_value_3,
        hall_sensor_value_4
    };

    Gear next_gear = map_sensor_values_to_gear(sensors, gear_mappings);

    // Update display if needed
    if (should_rerender(current_gear, next_gear)) {
        current_gear = next_gear;
        display_gear(current_gear);
    }

    delay(50);
}

// HELPER / UTILS
// ============================================================================================= //

bool is_within_range(int value, SensorRange range) {
    return value >= range.min && value <= range.max;
}

Gear map_sensor_values_to_gear(int sensor_values[NUM_SENSORS], const SensorToGearMapping mappings[]) {
    for (int i = 0; i < sizeof(gear_mappings) / sizeof(gear_mappings[0]); ++i) {
        const SensorToGearMapping& mapping = gear_mappings[i];
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

    return Gear::NEUTRAL;
}

void display_gear(Gear gear) {
    switch (gear) {
        case Gear::REVERSE:
            Serial.println("R");  // Reverse gear
            break;
        case Gear::FIRST:
            Serial.println("1");  // First gear
            break;
        case Gear::SECOND:
            Serial.println("2");  // Second gear
            break;
        case Gear::THIRD:
            Serial.println("3");  // Third gear
            break;
        case Gear::FOURTH:
            Serial.println("4");  // Fourth gear
            break;
        case Gear::FIFTH:
            Serial.println("5");  // Fifth gear
            break;
        default:
            Serial.println("N");  // Default to Neutral
            break;
    }
}

bool should_rerender(Gear current_gear, Gear next_gear) {
    return current_gear != next_gear;
}
