#ifndef DISPLAY_H
#define DISPLAY_H

void setup_display();
void clear_display();
void set_display(char gear);
using Hertz = unsigned int; // 1 .. 120
using Milliseconds = unsigned int;
Milliseconds get_delay_for_refresh_rate(Hertz refresh_rate);

#endif
