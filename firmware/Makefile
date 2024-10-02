.PHONY: compile binary

FQBN=arduino:avr:nano

compile:
	arduino-cli compile --fqbn $(FQBN) $(PWD)/main

binary:
	arduino-cli compile --fqbn $(FQBN) --output-dir $(PWD)/.build $(PWD)/main
