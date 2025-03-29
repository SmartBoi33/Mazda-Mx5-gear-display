#ifndef COMMAND_TYPE_H
#define COMMAND_TYPE_H

// Define command types for the state machine
enum CommandType {
    UNKNOWN_COMMAND,     // Unrecognized command
    START_CALIBRATION,   // Set to calibration mode
    RECORD_GEAR_1,       // Start recording (Waiting → Recording)
    RECORD_GEAR_2,
    RECORD_GEAR_3,
    RECORD_GEAR_4,
    RECORD_GEAR_5,
    RECORD_GEAR_R,
    RECORD_GEAR_N,
    STOP_GEAR_RECORDING, // Stop recording (Recording → Waiting)
    FINISH_CALIBRATION,  // Complete recording (Waiting → Calibrate)
    ABORT_CALIBRATION    // Abort calibration (Any active state → Initial)
};

#endif // COMMAND_TYPE_H
