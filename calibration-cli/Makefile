# Define the output binary names
BIN_NAME = calibration-cli
BIN_NAME_WIN = calibration-cli.exe

# Default serial port (change as needed)
PORT = /dev/ttyUSB0

# Detect OS
OS := $(shell uname -s)

# Select correct binary name based on OS
ifeq ($(OS),Windows_NT)
    BIN_OUTPUT = $(BIN_NAME_WIN)
else
    BIN_OUTPUT = $(BIN_NAME)
endif

# Install dependencies
install:
	go mod tidy
	go get -u github.com/tarm/serial

# Run the CLI with default serial port
run:
	go run main.go -port $(PORT)

# Build executable
build:
	go build -o $(BIN_OUTPUT) main.go

# Clean build artifacts
clean:
	rm -f $(BIN_NAME) $(BIN_NAME_WIN)

# Help command to list available tasks
help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Available targets:"
	@echo "  install   - Install dependencies"
	@echo "  run       - Run the CLI (default port: $(PORT))"
	@echo "  build     - Build the CLI executable"
	@echo "  clean     - Remove build artifacts"
