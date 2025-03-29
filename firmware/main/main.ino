#include <Arduino.h>
#include "display.h"
#include "sensors.h"
#include "state.h"
#include "gear_mappings.h"
#include "digital_pin_event.h"
#include "event.h"
#include "storage.h"
#include "update_storage.h"

// GLOBAL VALUES
const int REFRESH_RATE_HZ = 30;
const int DELAY_FOR_REFRESH_RATE_MS = 1000 / REFRESH_RATE_HZ;
const int MAX_MESSAGE_LENGTH_IN_CHARACTERS = 100;

SystemState currentState = {
    GEAR_DETECTION_MODE,
    WAITING,
    ' ',
    empty_mapping(),
    empty_mapping(),
    'N',
    ""
};

// SETUP
void setup() {
    setup_sensors();
    setup_event();
    setup_display();
    if (has_data()) {
        Storage data = load();
        SensorToGearMappings loaded = data.gear_mappings;
        currentState.current_gear_mapping = loaded;
    }
}

// MAIN LOOP
void loop() {
    SensorData sensor_data = read_sensors();
    DigitalPinEvent event = read_event();
    CommandType command = next_command(currentState, event);
    command = auto_finish_calibration(currentState, command); // this will turn the command to FINISH_CALIBRATION when we are in the CALIBRATE state

    update_storage(currentState, command); // this will update the storage if we finish the calibration with a new gear mapping

    currentState = next_state(currentState, command, sensor_data);

    char display_value = to_display_value(currentState);
    display(display_value);

    delay(DELAY_FOR_REFRESH_RATE_MS);
}
