# About the Firmware
This directory contains the firmware code, written in C++ using the Arduino framework, which controls the LED Gear Display for the Mazda MX-5. All the code runs on a single microcontroller, which reads sensor data and controls the LED display. The firmware continuously reads the sensor values on each iteration of the main loop, maps the values to the active gear, and updates the display in real-time.

## Requirements
To build and upload the firmware, you will need the following tools installed:

- [Arduino CLI](https://arduino.github.io/arduino-cli/0.35/): Required for compiling and uploading the `.ino` files to the Arduino. Follow the installation guide in the official documentation.
- [Make](https://www.gnu.org/software/make/): Used to automate the build and upload process through the provided Makefile. Refer to the documentation for installation instructions.

Ensure these tools are correctly configured in your system before running the Makefile commands.

## Firmware Setup

Once you have the Arduino CLI installed, follow these steps to set up the environment and prepare for compiling and uploading the firmware.

### 1. Initialize and Configure Arduino CLI
First, initialize the Arduino CLI environment:

```bash
arduino-cli config init
```

This will create a configuration file in your home directory.

### 2. Update the Core Index
To ensure that the CLI has the latest information about available boards, run:

```bash
arduino-cli core update-index
```

### 3. Install the Required Core for Arduino Nano
If you are using an **Arduino Nano** board, you'll need to install the `arduino:avr` core. Run the following command:

```bash
arduino-cli core install arduino:avr
```

This step is only necessary if your board is a Nano. If you're using a different board, refer to its specific core installation instructions.

### 4. Find Your Board's FQBN (Fully Qualified Board Name)
To compile and upload the firmware, you'll need the FQBN for your specific board. You can list all supported boards with this command:

```bash
arduino-cli board listall
```


Once you have the correct FQBN (for example, `arduino:avr:nano`), you can proceed with compiling and uploading the firmware.
