#include <string.h>
#include <Arduino.h>
#include "commands.h"

char serialBuffer[COMMAND_BUFFER_SIZE];  // Buffer for incoming Serial data

void setup_communication() {
    Serial.begin(9600); // Serial.begin(115200) for longer messages
}

// Static variable to store the last command
static Command lastCommand = {UNKNOWN_COMMAND, ""};

/**
 * @brief Reads and parses a command from Serial input.
 *
 * If no new command is available, the function returns the last stored command.
 *
 * @return A `Command` struct containing the parsed command.
 */
Command get_command() {
    static char serialBuffer[COMMAND_BUFFER_SIZE];  // Buffer for incoming Serial data

    if (Serial.available() > 0) {
        size_t len = Serial.readBytesUntil('\n', serialBuffer, sizeof(serialBuffer) - 1);
        serialBuffer[len] = '\0';  // Null-terminate

        // **Parse command safely**
        if (strcmp(serialBuffer, "START") == 0) {
            lastCommand.type = START;
            strncpy(lastCommand.message, "Starting calibration...", sizeof(lastCommand.message) - 1);
        } else if (strncmp(serialBuffer, "RECORD_GEAR ", 15) == 0) {
            lastCommand.type = RECORD_GEAR;
            strncpy(lastCommand.message, serialBuffer + 15, sizeof(lastCommand.message) - 1);  // Copy gear info safely
        } else if (strncmp(serialBuffer, "STOP_RECORD", 15) == 0) {
            lastCommand.type = STOP_RECORD;
            strncpy(lastCommand.message, serialBuffer + 15, sizeof(lastCommand.message) - 1);  // Copy gear info safely
        } else if (strcmp(serialBuffer, "FINISH") == 0) {
            lastCommand.type = FINISH;
            strncpy(lastCommand.message, "Calibration finished.", sizeof(lastCommand.message) - 1);
        } else if (strcmp(serialBuffer, "ABORT") == 0) {
            lastCommand.type = ABORT;
            strncpy(lastCommand.message, "Calibration aborted by user.", sizeof(lastCommand.message) - 1);
        }
        // **Unknown command: Don't overwrite last valid command**
    }

    return lastCommand;  // Return last stored command (unchanged if no new input)
}

void send_message(const char* message) {
    char buffer[COMMAND_BUFFER_SIZE];  // Ensure message is within limits
    strncpy(buffer, message, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';  // Ensure null termination
}

void send_error(const char* error_message) {
    char buffer[COMMAND_BUFFER_SIZE];  // Prevent overflow
    strncpy(buffer, error_message, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';  // Ensure null termination
}
