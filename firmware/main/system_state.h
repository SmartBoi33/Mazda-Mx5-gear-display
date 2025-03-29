#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include "gear_mappings.h"

// Define system states
enum ModeStateType {
    GEAR_DETECTION_MODE,
    CALIBRATION_MODE,
    ERROR,
};

enum CalibrationModeStateType {
    WAITING,
    RECORDING,
    CALIBRATE,
};

#define MAX_ERROR_LENGTH 80 // 80 character == one terminal line

// Struct representing the entire system state
struct SystemState {
    ModeStateType mode;  // Main mode state

    // Calibration-related state
    CalibrationModeStateType calibration;
    char recording_gear;  // '1', '2', '3', '4', '5', 'R', 'N'
    SensorToGearMappings recording_data;

    // Gear detection-related state
    SensorToGearMappings current_gear_mapping;
    char current_gear;  // '1', '2', '3', '4', '5', 'R', 'N'

    // Error-related state
    char error_message[MAX_ERROR_LENGTH];
};

#endif // SYSTEM_STATE_H
