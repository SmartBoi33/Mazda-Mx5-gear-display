.PHONY: install compile tests tests-in-docker binary board-list upload clear

FQBN=arduino:avr:nano
SKETCH_DIR=$(PWD)/main
BUILD_DIR=$(PWD)/.build
TEST_DIR=$(PWD)/tests
TMP_DIR=$(PWD)/tmp
TESTS_DOCKER_IMAGE=gtest-image
TESTS_DOCKER_IMAGE_FILE=$(PWD)/$(TESTS_DOCKER_IMAGE).tar
INTEGRATION_TESTS_DOCKER_IMAGE=simavr-image
INTEGRATION_TESTS_DOCKER_IMAGE_FILE=$(PWD)/$(INTEGRATION_TESTS_DOCKER_IMAGE).tar
BOARD_PORT=/dev/cu.usbserial-10

$(TMP_DIR):
	mkdir -p tmp

# GoogleTest paths from Homebrew
# you may need to run brew install googletest first if you have googletest not installed
GTEST_DIR=$(shell brew --prefix googletest)

LIBRARIES = LedControl

install:
	@for lib in $(LIBRARIES); do \
		arduino-cli lib install "$$lib"; \
	done

# get a list of connected boards and their ports
boards:
	arduino-cli board list

compile:
	arduino-cli compile --fqbn $(FQBN) --output-dir $(BUILD_DIR) $(SKETCH_DIR)

# About the Tests
# you need to have GoogleTest for c++ tests installed to compile and run the tests
# you can just run the docker command to build and run the tests in docker
CXX_FLAGS=-std=c++14 -Wall -I$(SKETCH_DIR)
CXX_TEST_FLAGS=$(CXX_FLAGS) -I$(GTEST_DIR)/include
LDFLAGS=-L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread

# Compile source files into object files
$(SKETCH_DIR)/%.o: $(SKETCH_DIR)/%.cpp
	g++ $(CXX_FLAGS) -c $< -o $@

# Compile test files into object files
$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	g++ $(CXX_TEST_FLAGS) -c $< -o $@

# Link test binary correctly
$(TMP_DIR)/map_sensor_values_to_gear_tests: $(TMP_DIR) $(SKETCH_DIR)/gear.o $(TEST_DIR)/test_map_sensor_values_to_gear.o
	g++ -I$(SKETCH_DIR) $(TEST_DIR)/test_map_sensor_values_to_gear.o $(SKETCH_DIR)/gear.o -o $(TMP_DIR)/map_sensor_values_to_gear_tests $(LDFLAGS)

$(TMP_DIR)/next_state_tests: $(TMP_DIR) $(SKETCH_DIR)/gear_mappings.o $(SKETCH_DIR)/gear.o $(SKETCH_DIR)/state.o $(TEST_DIR)/test_next_state.o
	g++ -I$(SKETCH_DIR) $(TEST_DIR)/test_next_state.o $(SKETCH_DIR)/gear_mappings.o $(SKETCH_DIR)/gear.o $(SKETCH_DIR)/state.o -o $(TMP_DIR)/next_state_tests $(LDFLAGS)

$(TMP_DIR)/integration_of_next_state_to_display_value_tests: $(TMP_DIR) $(SKETCH_DIR)/gear_mappings.o $(SKETCH_DIR)/gear.o $(SKETCH_DIR)/state.o $(TEST_DIR)/test_integration_of_next_state_to_display_value.o
	g++ -I$(SKETCH_DIR) $(TEST_DIR)/test_integration_of_next_state_to_display_value.o $(SKETCH_DIR)/gear_mappings.o $(SKETCH_DIR)/gear.o $(SKETCH_DIR)/state.o -o $(TMP_DIR)/integration_of_next_state_to_display_value_tests $(LDFLAGS)

foo: $(TMP_DIR)/next_state_tests
	$(TMP_DIR)/next_state_tests

$(TMP_DIR)/to_display_value_tests: $(TMP_DIR)
	echo "$(TMP_DIR)/to_display_value_tests is not yet implemented"

# $(TMP_DIR)/to_display_value_tests: $(All_TEST_OBJECT_FILES) $(All_H_FILES) $(TEST_DIR)/test_to_display_value.o
# 	$(GCC_TEST) -o to_display_value_tests $(TEST_DIR)/test_to_display_value.cpp $(TEST_DIR)/state.o

tests: $(TMP_DIR)/map_sensor_values_to_gear_tests $(TMP_DIR)/next_state_tests $(TMP_DIR)/to_display_value_tests $(TMP_DIR)/integration_of_next_state_to_display_value_tests
	$(TMP_DIR)/map_sensor_values_to_gear_tests
	$(TMP_DIR)/next_state_tests
	$(TMP_DIR)/integration_of_next_state_to_display_value_tests
	$(MAKE) clear

# Build and save the Docker image only when needed
$(TESTS_DOCKER_IMAGE_FILE):
	docker build --no-cache -t $(TESTS_DOCKER_IMAGE) -f $(TESTS_DOCKER_IMAGE_FILE) .
	docker save -o $(TESTS_DOCKER_IMAGE_FILE) $(TESTS_DOCKER_IMAGE);

# Load and run the container from the pre-built image
tests-in-docker: $(TESTS_DOCKER_IMAGE_FILE)
	docker load -i $(TESTS_DOCKER_IMAGE_FILE)
	docker run --rm $(TESTS_DOCKER_IMAGE)

debug-tests-in-docker:
	docker load -i $(TESTS_DOCKER_IMAGE_FILE)
	docker run --rm -it $(TESTS_DOCKER_IMAGE) bash

$(INTEGRATION_TESTS_DOCKER_IMAGE_FILE):
	docker build --no-cache -t $(INTEGRATION_TESTS_DOCKER_IMAGE) -f $(INTEGRATION_TESTS_DOCKER_IMAGE_FILE) .
	docker save -o $(INTEGRATION_TESTS_DOCKER_IMAGE_FILE) $(INTEGRATION_TESTS_DOCKER_IMAGE);

integration-tests-in-docker: $(INTEGRATION_TESTS_DOCKER_IMAGE_FILE)
	docker load -i $(INTEGRATION_TESTS_DOCKER_IMAGE_FILE)
	docker run --rm $(INTEGRATION_TESTS_DOCKER_IMAGE)

binary:
	mkdir -p $(BUILD_DIR)
	arduino-cli compile --fqbn $(FQBN) --output-dir $(BUILD_DIR) $(SKETCH_DIR)

board-list:
	arduino-cli board list

upload:
	arduino-cli upload -p $(BOARD_PORT) --fqbn $(FQBN) $(SKETCH_DIR)

run: compile upload

clear:
	rm -rf $(BUILD_DIR) $(TMP_DIR) $(SKETCH_DIR)/*.o $(TEST_DIR)/*.o $(TEST_DIR)/*.h $(DOCKER_IMAGE_FILE)
