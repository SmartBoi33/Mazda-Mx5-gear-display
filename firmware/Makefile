.PHONY: compile binary board-list upload clear

FQBN=arduino:avr:nano
SKETCH_DIR=$(PWD)/main
BUILD_DIR=$(PWD)/.build
BOARD_PORT=/dev/ttyUSB0

compile:
	arduino-cli compile --fqbn $(FQBN) $(SKETCH_DIR)

binary:
	mkdir -p $(BUILD_DIR)
	arduino-cli compile --fqbn $(FQBN) --output-dir $(BUILD_DIR) $(SKETCH_DIR)

board-list:
	arduino-cli board list

upload:
	arduino-cli upload -p $(BOARD_PORT) --fqbn $(FQBN) $(SKETCH_DIR)

clear:
	rm -rf $(BUILD_DIR)
