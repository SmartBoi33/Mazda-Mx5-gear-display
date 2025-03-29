#include <stdio.h>  // Needed for snprintf
#include "state.h"
#include "command_type.h"
#include "gear_mappings.h"
#include "gear.h"

int to_min(int a, int b) {
    return (a < b) ? a : b;
}

int to_max(int a, int b) {
    return (a > b) ? a : b;
}

void update_recording_data(char gear, SensorData sensor_data, SensorToGearMappings &recording_data) {
    for (int i = 0; i < NUMBER_OF_GEARS; i++) {
        if (recording_data.mappings[i].gear == gear) {
            for (int j = 0; j < NUMBER_OF_SENSORS; j++) {
                recording_data.mappings[i].sensor_ranges[j].min = to_min(recording_data.mappings[i].sensor_ranges[j].min, sensor_data.values[j]);
                recording_data.mappings[i].sensor_ranges[j].max = to_max(recording_data.mappings[i].sensor_ranges[j].max, sensor_data.values[j]);
            }
            return;
        }
    }
}

char detect_gear(SensorData sensor_data, SensorToGearMappings &recording_data) {
    return map_sensor_values_to_gear(sensor_data.values, recording_data.mappings);
}

SystemState next_state(SystemState state, CommandType command, SensorData sensor_data) {
    SystemState new_state = state;

    switch (state.mode) {
        case GEAR_DETECTION_MODE:
            switch (command) {
                case START_CALIBRATION: {
                    new_state.mode = CALIBRATION_MODE;
                    new_state.calibration = WAITING;
                    new_state.recording_gear = ' ';
                    return new_state;
                }
                default: {
                    new_state.current_gear = detect_gear(sensor_data, new_state.current_gear_mapping);
                    return new_state;
                }
            }
        case CALIBRATION_MODE:
            switch (state.calibration) {
                case WAITING: {
                    switch (command) {
                        case RECORD_GEAR_1: {
                            new_state.calibration = RECORDING;
                            new_state.recording_gear = '1';
                            return new_state;
                        }
                        case RECORD_GEAR_2: {
                            new_state.calibration = RECORDING;
                            new_state.recording_gear = '2';
                            return new_state;
                        }
                        case RECORD_GEAR_3: {
                            new_state.calibration = RECORDING;
                            new_state.recording_gear = '3';
                            return new_state;
                        }
                        case RECORD_GEAR_4: {
                            new_state.calibration = RECORDING;
                            new_state.recording_gear = '4';
                            return new_state;
                        }
                        case RECORD_GEAR_5: {
                            new_state.calibration = RECORDING;
                            new_state.recording_gear = '5';
                            return new_state;
                        }
                        case RECORD_GEAR_N: {
                            new_state.calibration = RECORDING;
                            new_state.recording_gear = 'N';
                            return new_state;
                        }
                        case RECORD_GEAR_R: {
                            new_state.calibration = RECORDING;
                            new_state.recording_gear = 'R';
                            return new_state;
                        }
                        case ABORT_CALIBRATION: {
                            new_state.mode = GEAR_DETECTION_MODE;
                            new_state.calibration = WAITING;
                            new_state.recording_gear = ' ';
                            new_state.current_gear = detect_gear(sensor_data, new_state.current_gear_mapping);
                            return new_state;
                        }
                        default:
                            break;
                    }
                }
                case RECORDING: {
                    switch (command) {
                        case STOP_GEAR_RECORDING: {
                            new_state.calibration = WAITING;
                            // new_state.recording_gear = ' ';
                            return new_state;
                        }
                        case ABORT_CALIBRATION: {
                            new_state.mode = GEAR_DETECTION_MODE;
                            new_state.calibration = WAITING;
                            new_state.recording_gear = ' ';
                            new_state.current_gear = detect_gear(sensor_data, new_state.current_gear_mapping);
                            return new_state;
                        }
                        case FINISH_CALIBRATION: {
                            new_state.calibration = CALIBRATE;
                            new_state.recording_gear = ' ';
                            new_state.current_gear_mapping = new_state.recording_data;
                            return new_state;
                        }
                        default: {
                            update_recording_data(new_state.recording_gear, sensor_data, new_state.recording_data);
                            return new_state;
                        }
                    }
                }
                case CALIBRATE: {
                    switch (command) {
                        case ABORT_CALIBRATION: {
                            new_state.mode = GEAR_DETECTION_MODE;
                            new_state.calibration = WAITING;
                            new_state.recording_gear = ' ';
                            new_state.current_gear = detect_gear(sensor_data, new_state.current_gear_mapping);
                            return new_state;
                        }
                        case FINISH_CALIBRATION: {
                            new_state.mode = GEAR_DETECTION_MODE;
                            new_state.calibration = WAITING;
                            new_state.recording_gear = ' ';
                            new_state.recording_data = empty_mapping();
                            new_state.current_gear = detect_gear(sensor_data, new_state.current_gear_mapping);
                            return new_state;
                        }
                        default:
                            break;
                    }
                }
                default:
                    break;
            }
        default:
            break;
    }
    return state;
}

CommandType next_command(const SystemState& state, DigitalPinEvent event) {
    switch (event) {
        case SHORT: {
            switch (state.mode) {
                case CALIBRATION_MODE: {
                    switch (state.calibration) {
                        case WAITING:
                            switch (state.recording_gear) {
                                case ' ':
                                    return RECORD_GEAR_1;
                                case '1':
                                    return RECORD_GEAR_2;
                                case '2':
                                    return RECORD_GEAR_3;
                                case '3':
                                    return RECORD_GEAR_4;
                                case '4':
                                    return RECORD_GEAR_5;
                                case '5':
                                    return RECORD_GEAR_R;
                                case 'R':
                                    return FINISH_CALIBRATION;
                            }
                        case RECORDING:
                            return STOP_GEAR_RECORDING;
                        case CALIBRATE:
                            return FINISH_CALIBRATION;
                        default:
                            break;
                    }
                }
                default:
                    break;
            }
        }
        case LONG: {
            switch (state.mode) {
                case GEAR_DETECTION_MODE: {
                    return START_CALIBRATION;
                }
                case CALIBRATION_MODE: {
                    return ABORT_CALIBRATION;
                }
                default:
                    break;
            }
        }
        default: // NONE
            break;
    }

    return UNKNOWN_COMMAND;
}

char to_display_value(const SystemState& state) {
    switch (state.mode) {
        case GEAR_DETECTION_MODE:
            return state.current_gear;
        case CALIBRATION_MODE:
            switch (state.calibration) {
                case RECORDING:
                    return state.recording_gear;
                default:
                    return 'C';
            }
        default:
            return 'E';
    }
}

void to_serial_print_message(const SystemState& state, char* buffer, size_t buffer_size) {
    const char* mode_str;
    const char* calibration_str = "";

    // Map mode to string
    switch (state.mode) {
        case GEAR_DETECTION_MODE:
            mode_str = "Gear Detection";
            break;
        case CALIBRATION_MODE:
            mode_str = "Calibration Mode";
            switch (state.calibration) {
                case WAITING: calibration_str = "Waiting"; break;
                case RECORDING: calibration_str = "Recording"; break;
                case CALIBRATE: calibration_str = "Calibrating"; break;
            }
            break;
        case ERROR:
            mode_str = "Error";
            break;
        default:
            mode_str = "Unknown";
    }

    // Format message into the provided buffer
    snprintf(buffer, buffer_size, "Mode: %s, Calibration: %s, Gear: %c, Error: %s",
             mode_str, calibration_str, state.current_gear, state.error_message);
}

CommandType auto_finish_calibration(const SystemState& state, CommandType command) {
    if (state.mode != CALIBRATION_MODE) return command;
    if (state.calibration != CALIBRATE) return command;
    return FINISH_CALIBRATION;
}
