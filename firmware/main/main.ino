#include <Arduino.h>

// TYPES
// ============================================================================================= //

struct SensorRange {
    int min;
    int max;
};

// Define the number of sensors
#define NUM_SENSORS 4
#define REVERSE_GEAR 1
#define NUM_NEUTRAL_STATES 3
#define NUM_GEARS (REVERSE_GEAR + NUM_NEUTRAL_STATES + 5)
// Define the structure for sensor range mapping
struct SensorToGearMapping {
    char gear;  // Gear as a char ('R', 'N', '1', etc.)
    SensorRange sensor_ranges[NUM_SENSORS];  // Array of sensor ranges for each gear
};

// CONSTANTS
// ============================================================================================= //

char default_gear = 'N';
char current_gear = 'N';

// Define sensor ranges for each gear
SensorToGearMapping gear_mappings[NUM_GEARS] = {
    // Reverse (R)
    {'R', {
        {520, 535},  // sensor1
        {500, 512},  // sensor2
        {560, 575},  // sensor3
        {490, 505}   // sensor4
    }},

    // Neutral - Center (N-Center)
    {'N', {
        {530, 545},  // sensor1
        {495, 505},  // sensor2
        {530, 545},  // sensor3
        {505, 520}   // sensor4
    }},

    // Neutral - Left (N-Left)
    {'N', {
        {527, 537},  // sensor1
        {500, 510},  // sensor2
        {530, 540},  // sensor3
        {503, 513}   // sensor4
    }},

    // Neutral - Right (N-Right)
    {'N', {
        {530, 542},  // sensor1
        {490, 500},  // sensor2
        {530, 545},  // sensor3
        {510, 520}   // sensor4
    }},

    // First Gear (1)
    {'1', {
        {545, 560},  // sensor1
        {485, 495},  // sensor2
        {520, 535},  // sensor3
        {510, 525}   // sensor4
    }},

    // Second Gear (2)
    {'2', {
        {520, 535},  // sensor1
        {500, 515},  // sensor2
        {515, 530},  // sensor3
        {465, 475}   // sensor4
    }},

    // Third Gear (3)
    {'3', {
        {545, 560},  // sensor1
        {570, 590},  // sensor2
        {520, 535},  // sensor3
        {510, 530}   // sensor4
    }},

    // Fourth Gear (4)
    {'4', {
        {520, 535},  // sensor1
        {500, 515},  // sensor2
        {555, 570},  // sensor3
        {480, 490}   // sensor4
    }},

    // Fifth Gear (5)
    {'5', {
        {545, 560},  // sensor1
        {450, 465},  // sensor2
        {520, 535},  // sensor3
        {510, 525}   // sensor4
    }},
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

    char next_gear = map_sensor_values_to_gear(sensors, gear_mappings);

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

char map_sensor_values_to_gear(int sensor_values[NUM_SENSORS], const SensorToGearMapping mappings[NUM_GEARS]) {
    for (int i = 0; i < NUM_GEARS; ++i) {
        const SensorToGearMapping& mapping = mappings[i];
        bool match = true;
        for (int j = 0; j < NUM_SENSORS; ++j) {
            if (sensor_values[j] < mapping.sensor_ranges[j].min || sensor_values[j] > mapping.sensor_ranges[j].max) {
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

void display_gear(char gear) {
    Serial.println(gear);
}

bool should_rerender(char current_gear, char next_gear) {
    return current_gear != next_gear;
}
