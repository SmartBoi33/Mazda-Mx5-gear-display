#include "display.h"

bool should_rerender(char current_gear, char next_gear) {
    return current_gear != next_gear;
}
