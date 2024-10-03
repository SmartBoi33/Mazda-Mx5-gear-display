# Firmware for Mazda MX-5 LED Gear Display

This directory contains the firmware for the Mazda MX-5 LED Gear Display, written in C++ using the Arduino framework. The firmware reads sensor data and updates the LED display to show the current gear. All code runs on a single microcontroller.

## Setup

Before building or uploading the firmware, ensure the following tools are installed:

- [Arduino CLI](https://arduino.github.io/arduino-cli/0.35/): For compiling and uploading firmware.
- [GNU Make](https://www.gnu.org/software/make/): To automate the build and upload process via the provided Makefile.

### Install Arduino CLI

1. Install the Arduino CLI by following the [official installation guide](https://arduino.github.io/arduino-cli/0.35/installation/).
2. Initialize the Arduino CLI environment:

   ```bash
   arduino-cli config init
   ```

   This will create the configuration file in your home directory.

3. Update the core index to get the latest board information:

   ```bash
   arduino-cli core update-index
   ```

4. Install the required core for **Arduino Nano** (or any other board you are using). For example, for Arduino Nano:

   ```bash
   arduino-cli core install arduino:avr
   ```

### Find Your Board’s FQBN

To compile and upload the firmware, you need the Fully Qualified Board Name (FQBN) for your board. To list all supported boards, run:

```bash
arduino-cli board listall
```

Use the appropriate FQBN in the commands or Makefile.

For more detailed information on using the Arduino CLI, refer to the [Arduino CLI documentation](https://arduino.github.io/arduino-cli/0.35/).

---

## Development Processes

This section explains how to compile and upload the firmware using the Makefile, which automates the process.

### 1. Compile the Firmware

To compile the firmware for the specified board using the Makefile:

```bash
make compile
```

This will compile the firmware located in the `$(SKETCH_DIR)` (default: `main`).

### 2. Compile and Generate Binary

To compile the firmware and store the binary in `$(BUILD_DIR)` (default: `.build`):

```bash
make binary
```

This generates a binary file in `.build`.

### 3. List Connected Boards

To identify which port your board is connected to, use the following command:

```bash
make board-list
```

This will list all available boards and their ports.

### 4. Upload the Firmware

After compiling, upload the firmware to the board connected to `$(BOARD_PORT)`:

```bash
make upload
```

This will upload the compiled firmware to the board.

### 5. Clean Build Artifacts

To remove all build artifacts and clean the `$(BUILD_DIR)`:

```bash
make clear
```

This will delete the contents of `.build`.
