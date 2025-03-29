#ifndef DISPLAY_PATTERNS_H
#define DISPLAY_PATTERNS_H

#include <stdint.h>  // Standard header for uint8_t

#define NUM_PATTERNS 11  // Explicitly set the number of character patterns

// Define special patterns
const uint8_t Empty[8] = {  // All LEDs off
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

const uint8_t Full[8] = {  // All LEDs on
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111
};

// Define a struct to map characters to their 8x8 binary patterns
struct CharacterPattern {
    char character;
    const uint8_t* pattern;
};

// Mapping of characters to their corresponding LED patterns
const CharacterPattern character_map[NUM_PATTERNS] = {
    {'N', (const uint8_t[8]){
        0b01000010,
        0b01100010,
        0b01010010,
        0b01010010,
        0b01001010,
        0b01001010,
        0b01000110,
        0b01000010
    }},
    {'1', (const uint8_t[8]){
        0b00001000,
        0b00011000,
        0b00001000,
        0b00001000,
        0b00001000,
        0b00001000,
        0b00001000,
        0b00011100
    }},
    {'2', (const uint8_t[8]){
        0b00111100,
        0b01000010,
        0b00000010,
        0b00000010,
        0b00011100,
        0b00100000,
        0b01000000,
        0b01111110
    }},
    {'3', (const uint8_t[8]){
        0b00111100,
        0b01000010,
        0b00000010,
        0b00011100,
        0b00000010,
        0b00000010,
        0b01000010,
        0b00111100
    }},
    {'4', (const uint8_t[8]){
        0b00000100,
        0b00001100,
        0b00010100,
        0b00100100,
        0b01000100,
        0b01111110,
        0b00000100,
        0b00000100
    }},
    {'5', (const uint8_t[8]){
        0b01111110,
        0b01000000,
        0b01000000,
        0b01111100,
        0b00000010,
        0b00000010,
        0b01000010,
        0b00111100
    }},
    {'R', (const uint8_t[8]){
        0b01111100,
        0b01000010,
        0b01000010,
        0b01111100,
        0b01010000,
        0b01001000,
        0b01000100,
        0b01000010
    }},
    {'C', (const uint8_t[8]){
        0b00111100,
        0b01000010,
        0b01000000,
        0b01000000,
        0b01000000,
        0b01000000,
        0b01000010,
        0b00111100
    }},
    {'E', (const uint8_t[8]){
        0b11111111,
        0b10000000,
        0b10000000,
        0b11111110,
        0b10000000,
        0b10000000,
        0b10000000,
        0b11111111
    }},
    {' ', Empty},  // Now referencing Empty
    {'#', Full}    // New entry for Full (All LEDs On)
};

#endif // DISPLAY_PATTERNS_H
