.PHONY: compile tests tests-in-docker binary board-list upload clear

FQBN=arduino:avr:nano
SKETCH_DIR=$(PWD)/main
BUILD_DIR=$(PWD)/.build
BOARD_PORT=/dev/ttyUSB0

compile:
	arduino-cli compile --fqbn $(FQBN) $(SKETCH_DIR)

# About the Tests
# you need to have GoogleTest for c++ tests installed to compile and run the tests
# you can just run the docker command to build and run the tests in docker
./tests/%.o: ./main/%.cpp
	g++ -c $< -o $@

./tests/%.h: ./main/%.h
	cp $< $@

All_TEST_OBJECT_FILES := $(patsubst ./main/%.cpp, ./tests/%.o, $(wildcard ./main/*.cpp))

All_H_FILES := $(patsubst ./main/%.h, ./tests/%.h, $(wildcard ./main/*.h))

gear_tests: $(All_TEST_OBJECT_FILES) $(All_H_FILES)
	g++ -o gear_tests ./tests/test_gear.cpp ./tests/gear.o ./tests/gear_mappings.o -lgtest -lgtest_main -pthread

display_tests: $(All_TEST_OBJECT_FILES) $(All_H_FILES)
	g++ -o display_tests ./tests/test_display.cpp ./tests/display.o -lgtest -lgtest_main -pthread

tests: gear_tests display_tests
	./gear_tests
	./display_tests
	rm -f gear_tests display_tests

tests-in-docker:
	docker build --no-cache -t gtest-image -f tests.Dockerfile .
	docker run --rm gtest-image

binary:
	mkdir -p $(BUILD_DIR)
	arduino-cli compile --fqbn $(FQBN) --output-dir $(BUILD_DIR) $(SKETCH_DIR)

board-list:
	arduino-cli board list

upload:
	arduino-cli upload -p $(BOARD_PORT) --fqbn $(FQBN) $(SKETCH_DIR)

clear:
	rm -rf $(BUILD_DIR)
