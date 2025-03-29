#include "update_storage.h"
#include "gear_mappings.h"
#include "storage.h"

void update_storage(const SystemState& state, CommandType command) {
    if (state.mode != CALIBRATION_MODE) return;
    if (state.calibration != CALIBRATE) return;
    if (command != FINISH_CALIBRATION) return;

    Storage current_data = Storage {
        .gear_mappings = empty_mapping()
    };

    if (has_data()) {
        current_data = load();
    }

    SensorToGearMappings new_data = state.recording_data;
    current_data.gear_mappings = new_data;

    save(current_data);
}
