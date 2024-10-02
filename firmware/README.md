# About the Firmware
This directory contains the firmware code, written in C++ using the Arduino framework, which controls the LED Gear Display for the Mazda MX-5. All the code runs on a single microcontroller, which reads sensor data and controls the LED display. The firmware continuously reads the sensor values on each iteration of the main loop, maps the values to the active gear, and updates the display in real-time.

## Requirements
To build and upload the firmware, you will need the following tools installed:

- [Arduino CLI](https://arduino.github.io/arduino-cli/0.35/): Required for compiling and uploading the `.ino` files to the Arduino. Follow the installation guide in the official documentation.
- [Make](https://www.gnu.org/software/make/): Used to automate the build and upload process through the provided Makefile. Refer to the documentation for installation instructions.

Ensure these tools are correctly configured in your system before running the Makefile commands.
