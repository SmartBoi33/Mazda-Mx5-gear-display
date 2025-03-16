#ifndef COMMANDS_H
#define COMMANDS_H

#define COMMAND_BUFFER_SIZE 50

void setup_communication();

enum CommandType {
    UNKNOWN_COMMAND,   // Unrecognized command
    START,            // Begin calibration (Initial → Waiting)
    RECORD_GEAR,      // Start recording (Waiting → Recording)
    STOP_RECORD,      // Stop recording (Recording → Waiting)
    FINISH,           // Complete recording (Waiting → Calibrate)
    ABORT             // Abort calibration (Any active state → Initial)
};

struct Command {
    CommandType type;
    char message[COMMAND_BUFFER_SIZE];
};

Command get_command();

void send_message(const char* message);
void send_error(const char* error_message);

#endif
