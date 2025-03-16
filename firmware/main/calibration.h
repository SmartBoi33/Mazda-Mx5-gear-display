#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "sensors.h"
#include "gear_mappings.h"

/**
 * @brief Stores calibration data for each gear.
 *
 * This struct holds the lower and upper sensor value bounds for each gear.
 * During calibration, these values are updated dynamically based on sensor readings.
 *
 * - `lower_bounds[NUM_GEARS][NUM_SENSORS]`: Minimum sensor values recorded for each gear.
 * - `upper_bounds[NUM_GEARS][NUM_SENSORS]`: Maximum sensor values recorded for each gear.
 */
struct CalibrationData {
    int lower_bounds[NUM_GEARS][NUM_SENSORS];
    int upper_bounds[NUM_GEARS][NUM_SENSORS];
};

/**
 * @brief Defines the possible states of the calibration process.
 *
 * - `INITIAL`: No calibration has started.
 * - `WAITING`: Ready to receive commands; used before and between gear recordings.
 * - `RECORDING`: Capturing sensor values for the current gear.
 * - `CALIBRATE`: Evaluating recorded values for overlaps & consistency.
 * - `ERROR`: Calibration failed due to invalid data.
 */
enum CalibrationStateType {
    INITIAL,    // No calibration started
    WAITING,    // Ready for input; used before and between recordings
    RECORDING,  // Capturing sensor values for the current gear
    CALIBRATE,  // Evaluating recorded values for validity
    ERROR,      // Calibration failed (e.g., sensor overlaps)
};

/**
 * @brief Represents the current state of the calibration process.
 *
 * This struct tracks the progress of calibration and holds the recorded data.
 *
 * - `state`: The current phase of calibration (see `CalibrationStateType`).
 * - `gear`: The gear currently being recorded.
 *   - `<` (N-Left): Left side of neutral position.
 *   - `N` (Neutral): The middle position.
 *   - `>` (N-Right): Right side of neutral position.
 *   - `1-5`: Forward gears.
 *   - `R`: Reverse gear.
 * - `data`: Stores sensor calibration values.
 * - `error_message[100]`: Holds a human-readable error message if an error occurs.
 */
struct CalibrationState {
    CalibrationStateType state;
    char gear; // '<', 'N', '>', '1', '2', '3', '4', '5', 'R'
    CalibrationData data;
    char error_message[100];  // Stores any errors that occur during calibration
};

/**
 * @brief Runs the calibration process.
 *
 * This function is called when calibration is initiated. It collects sensor values,
 * updates the calibration state, and ensures that bounds for each gear are set correctly.
 * The function should be called continuously within the main loop until calibration is completed.
 */
void calibrate();

#endif
