# Pin Interface Declaration

This document outlines the pin interface between hardware and software for the **Mazda MX-5 LED Gear Display**. It defines the purpose, value ranges, and behavior of each pin.

## Pin Definitions

| Pin Number | Function        | Value Range           | Description                                                                 |
|------------|-----------------|-----------------------|-----------------------------------------------------------------------------|
| A0         | Left Sensor      | 0 to 1023 (int)       | Reads analog values for the left hall sensor, used for gear detection.       |
| A1         | Top Sensor       | 0 to 1023 (int)       | Reads analog values for the top hall sensor, used for gear detection.        |
| A2         | Right Sensor     | 0 to 1023 (int)       | Reads analog values for the right hall sensor, used for gear detection.      |
| A3         | Bottom Sensor    | 0 to 1023 (int)       | Reads analog values for the bottom hall sensor, used for gear detection.     |
| D2         | LED Control 1    | 0 or 1 (digital)      | Controls the LED display for first gear. `0`: Off, `1`: On.                  |
| D3         | LED Control 2    | 0 or 1 (digital)      | Controls the LED display for second gear. `0`: Off, `1`: On.                 |
| D4         | Calibration Pin  | 0 or 1 (digital)      | Triggers calibration mode. `1`: Calibration active, `0`: Calibration inactive.|

## Value Interpretation

- **Analog Sensor Pins (A0-A3):** These pins read integer values ranging from 0 to 1023, which represent the signals from the hall sensors for gear detection.
- **Digital Control Pins (D2-D4):** These pins control binary states (0 or 1) for simple on/off behavior, such as activating LEDs or triggering calibration mode.
