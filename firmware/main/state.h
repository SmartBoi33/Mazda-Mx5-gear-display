#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include "command_type.h"
#include "digital_pin_event.h"
#include "sensor_data.h"
#include "gear_mappings.h"
#include "system_state.h"

// Function prototypes
CommandType next_command(const SystemState& state, DigitalPinEvent event);
CommandType auto_finish_calibration(const SystemState& state, CommandType command);
SystemState next_state(SystemState state, CommandType command, SensorData sensor_data);
char to_display_value(const SystemState& state);
void to_serial_print_message(const SystemState& state, char* buffer, size_t buffer_size);

#endif // STATE_H
