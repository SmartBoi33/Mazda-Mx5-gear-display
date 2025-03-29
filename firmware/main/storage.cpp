#include <EEPROM.h>
#include <stdint.h>
#include "storage.h"

const int STORAGE_ADDR = 0;
const uint8_t VALID_MARKER = 0x42;

bool has_data() {
    return EEPROM.read(STORAGE_ADDR) == VALID_MARKER;
}

Storage load() {
    Storage data;
    EEPROM.get(STORAGE_ADDR + 1, data);
    return data;
}

void save(Storage &data) {
    EEPROM.write(STORAGE_ADDR, VALID_MARKER);
    EEPROM.put(STORAGE_ADDR + 1, data);
}

void clear() {
    EEPROM.write(STORAGE_ADDR, 0x00); // Overwrite the valid marker to invalidate data
}
