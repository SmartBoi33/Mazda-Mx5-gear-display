#ifndef STORAGE_H
#define STORAGE_H

#include "gear_mappings.h"

struct Storage {
    SensorToGearMappings gear_mappings;
};

bool has_data();
Storage load();
void save(Storage &data);
void clear();

#endif // STORAGE_H
