#include <LedControl.h>
#include "display.h"
#include "display_patterns.h"

LedControl lc = LedControl(
  4, // DIN pin
  6, // CLK pin
  5, // CS pin
  1 // number of devices
);

void display_pattern(const uint8_t* pattern) {
    // lc.clearDisplay(0);
    for (int row = 0; row < 8; row++) {
        lc.setRow(0, row, pattern[row]);
    }
}

const uint8_t* get_pattern_for_character(char character) {
    for (int i = 0; i < NUM_PATTERNS; i++) {
        if (character_map[i].character == character) {
            return character_map[i].pattern;  // Return pointer to the pattern
        }
    }
    return Empty;  // Default to Empty pattern
}

void display_character(char character){
  display_pattern(get_pattern_for_character(character));
}

void clear_display() {
  lc.clearDisplay(0);
}

void setup_display(){
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

void display(char value) {
    display_character(value);
}
