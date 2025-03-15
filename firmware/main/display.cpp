#include <Arduino.h>
#include <LedControl.h>
#include "display.h"

char initial_state = 'N';
char display_state = initial_state;

LedControl lc = LedControl(
  4, // DIN pin
  6, // CLK pin
  5, // CS pin
  1 // number of devices
);

const byte characters[8][8] = {
    {
      0b01000010,
      0b01100010,
      0b01010010,
      0b01010010,
      0b01001010,
      0b01001010,
      0b01000110,
      0b01000010
    }, // 'N'
    {
      0b00001000,
      0b00011000,
      0b00001000,
      0b00001000,
      0b00001000,
      0b00001000,
      0b00001000,
      0b00011100
    }, // '1'
    {
      0b00111100,
      0b01000010,
      0b00000010,
      0b00000010,
      0b00011100,
      0b00100000,
      0b01000000,
      0b01111110
    }, // '2'
    {
      0b00111100,
      0b01000010,
      0b00000010,
      0b00011100,
      0b00000010,
      0b00000010,
      0b01000010,
      0b00111100
    }, // '3'
    {
      0b00000100,
      0b00001100,
      0b00010100,
      0b00100100,
      0b01000100,
      0b01111110,
      0b00000100,
      0b00000100
    }, // '4'
    {
      0b01111110,
      0b01000000,
      0b01000000,
      0b01111100,
      0b00000010,
      0b00000010,
      0b01000010,
      0b00111100
    }, // '5'
    {
      0b01111100,
      0b01000010,
      0b01000010,
      0b01111100,
      0b01010000,
      0b01001000,
      0b01000100,
      0b01000010
    },  // 'R'
    {
      0b00111100,
      0b01000010,
      0b10000001,
      0b10000000,
      0b10000000,
      0b10000001,
      0b01000010,
      0b00111100
    }  // 'C'
};

void display_pattern(byte pattern[8]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, pattern[row]);
  }
}

int map_character_to_map_index(char character) {
  switch (character) {
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case 'R': return 6;
    case 'C': return 7;
    default: return 0; // N
  };
}

void display_character(char character){
  display_pattern(characters[map_character_to_map_index(character)]);
}

bool should_rerender(char current_gear, char next_gear) {
    return current_gear != next_gear;
}

Milliseconds get_delay_for_refresh_rate(Hertz refresh_rate) {
    return 1000 / refresh_rate; // ms / Hz
}

void clear_display() {
  lc.clearDisplay(0);
}

void setup_display(){
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  display_character(display_state);
}

void set_display(char value) {
  if (should_rerender(display_state, value)) {
      display_state = value;
      clear_display();
      display_character(display_state);
  }
}
