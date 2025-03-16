#include <string.h>
#include <Arduino.h>
#include "commands.h"
#include "sensors.h"
#include "calibration.h"
#include "gear_mappings.h"

CalibrationState init_calibration() {
    CalibrationState calibrationState;
    calibrationState.state = INITIAL;
    calibrationState.gear = 'N';  // "Initial" state

    // Initialize bounds with extreme values
    for (int g = 0; g < NUM_GEARS; g++) {
        for (int s = 0; s < NUM_SENSORS; s++) {
            calibrationState.data.lower_bounds[g][s] = 1023;  // Max ADC value
            calibrationState.data.upper_bounds[g][s] = 0;     // Min ADC value
        }
    }

    strcpy(calibrationState.error_message, "");  // Clear error message
    return calibrationState;
};

void record_gear(CalibrationState calibrationState, SensorData sensors) {
    int gearIndex = calibrationState.gear - '0'; // Convert char to int

    if (gearIndex >= 0 && gearIndex < NUM_GEARS) {
        for (int i = 0; i < NUM_SENSORS; i++) {
            int value = sensors.values[i];

            // Update lower bound
            if (value < calibrationState.data.lower_bounds[gearIndex][i]) {
                calibrationState.data.lower_bounds[gearIndex][i] = value;
            }

            // Update upper bound
            if (value > calibrationState.data.upper_bounds[gearIndex][i]) {
                calibrationState.data.upper_bounds[gearIndex][i] = value;
            }
        }
    }
};

#define CONFIDENCE_THRESHOLD 0.8  // Minimum distinct confidence (80%)

bool validate_calibration(CalibrationState calibrationState) {
    for (int g = 0; g < NUM_GEARS - 1; g++) {
        for (int s = 0; s < NUM_SENSORS; s++) {
            int upper_g = calibrationState.data.upper_bounds[g][s];
            int lower_next_g = calibrationState.data.lower_bounds[g + 1][s];

            int range_g = upper_g - calibrationState.data.lower_bounds[g][s];
            int range_next_g = calibrationState.data.upper_bounds[g + 1][s] - lower_next_g;

            // Ensure valid ranges (prevent division by zero)
            if (range_g == 0 || range_next_g == 0) {
                return false;
            }

            // Calculate separation confidence
            float gap = lower_next_g - upper_g;  // Space between the two gear ranges
            float required_gap = CONFIDENCE_THRESHOLD * (range_g + range_next_g) / 2.0;  // Thresholded gap

            if (gap < required_gap) {
                return false;  // Not distinct enough
            }
        }
    }
    return true;  // No overlap or acceptable confidence level
};

SensorToGearMappings state_to_gear_mappings(CalibrationState calibrationState) {
    SensorToGearMappings mappings;

    // Define gear order to match `CalibrationState`
    const char gear_order[NUM_GEARS] = {'<', 'N', '>', '1', '2', '3', '4', '5', 'R'};

    for (int g = 0; g < NUM_GEARS; g++) {
        mappings.mappings[g].gear = gear_order[g];

        for (int s = 0; s < NUM_SENSORS; s++) {
            mappings.mappings[g].sensor_ranges[s].min = calibrationState.data.lower_bounds[g][s];
            mappings.mappings[g].sensor_ranges[s].max = calibrationState.data.upper_bounds[g][s];
        }
    }

    return mappings;
}

// Global calibration state
CalibrationState calibrationState = init_calibration();

void calibrate() {
    Command command = get_command();
    SensorData sensors = read_sensors();

    switch (command.type) {
        case START:
            calibrationState = init_calibration();
            calibrationState.state = WAITING;
            break;

        case RECORD_GEAR:
            switch (calibrationState.state) {
                case WAITING:
                    calibrationState.state = RECORDING;
                    break;

                case RECORDING: {
                    SensorData data = read_sensors();
                    record_gear(calibrationState, data);
                    break;
                }

                default:
                    break;
            }
            break;

        case STOP_RECORD:
            switch (calibrationState.state) {
                case RECORDING:
                    calibrationState.state = WAITING;
                    break;

                default:
                    break;
            }
            break;

        case ABORT:
            switch (calibrationState.state) {
                case WAITING:
                case RECORDING:
                case CALIBRATE:
                case ERROR:
                    calibrationState = init_calibration();
                    break;
                default:
                    break;
            }
            break;

        case FINISH:
            switch (calibrationState.state) {
                case WAITING:
                    calibrationState.state = CALIBRATE;
                    break;

                case CALIBRATE: {
                    if (validate_calibration(calibrationState)) {
                        send_message("Calibration successful.");
                        gear_mappings = state_to_gear_mappings(calibrationState);
                        calibrationState = init_calibration();  // Reset calibration state
                    } else {
                        send_error("Calibration failed: Gears are too close.");
                        calibrationState.state = ERROR;
                    }
                    break;
                }

                default:
                    break;
            }
            break;

        default:
            break;
    }
}
