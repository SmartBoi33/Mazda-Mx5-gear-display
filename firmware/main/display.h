#ifndef DISPLAY_H
#define DISPLAY_H

void display_gear(char gear);
bool should_rerender(char current_gear, char next_gear);
using Hertz = unsigned int; // 1 .. 120
using Milliseconds = unsigned int;
Milliseconds get_delay_for_refresh_rate(Hertz refresh_rate);

#endif
