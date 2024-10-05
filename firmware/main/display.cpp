#include "display.h"

bool should_rerender(char current_gear, char next_gear) {
    return current_gear != next_gear;
}

Milliseconds get_delay_for_refresh_rate(Hertz refresh_rate) {
    return 1000 / refresh_rate; // ms / Hz
};
