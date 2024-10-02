.PHONY: compile binary upload clear

FQBN=arduino:avr:nano
SKETCH_DIR=$(PWD)/main
BUILD_DIR=$(PWD)/.build

compile:
	arduino-cli compile --fqbn $(FQBN) $(SKETCH_DIR)

binary:
	mkdir -p $(BUILD_DIR)
	arduino-cli compile --fqbn $(FQBN) --output-dir $(BUILD_DIR) $(SKETCH_DIR)

upload:
	arduino-cli upload -p /dev/ttyUSB0 --fqbn $(FQBN) $(SKETCH_DIR)

clear:
	rm -rf $(BUILD_DIR)
