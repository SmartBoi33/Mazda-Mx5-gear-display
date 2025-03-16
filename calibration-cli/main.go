package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strings"
	"time"

	"github.com/tarm/serial"
)

// Calibration states (matches Arduino)
type State int

const (
	Initial State = iota
	Waiting
	Recording
	Calibrate
	ErrorState
)

// Valid gear names
var validGears = map[string]bool{
	"<": true, "N": true, ">": true,
	"1": true, "2": true, "3": true, "4": true, "5": true, "R": true,
}

// Command mappings
var keyToCommand = map[string]string{
	"s": "START\n",
	"t": "STOP_RECORD\n",
	"f": "FINISH\n",
	"a": "ABORT\n",
}

var stateNames = map[State]string{
	Initial:    "Initial",
	Waiting:    "Waiting",
	Recording:  "Recording",
	Calibrate:  "Calibrate",
	ErrorState: "Error",
}

// Current state
var currentState State = Initial

func main() {
	// Parse the serial port flag
	portFlag := flag.String("port", "", "Serial port for Arduino (e.g., /dev/ttyUSB0, COM3)")
	flag.Parse()

	// Ensure the user provides a port
	if *portFlag == "" {
		fmt.Println("\n[ERROR] No serial port specified!")
		fmt.Println("🔌 Please provide a port using `-port` flag:")
		fmt.Println("  macOS/Linux: go run main.go -port /dev/ttyUSB0")
		fmt.Println("  Windows:     go run main.go -port COM3")
		fmt.Println("\n🔁 Restart the CLI with the correct port.")
		return
	}

	// Open serial connection
	config := &serial.Config{Name: *portFlag, Baud: 115200, ReadTimeout: time.Second * 2}
	port, err := serial.OpenPort(config)
	if err != nil {
		fmt.Println("\n[ERROR] Failed to open serial port:", *portFlag)
		fmt.Println("🔌 Please check:")
		fmt.Println("  ✅ Is the Arduino plugged into your laptop?")
		fmt.Println("  ✅ Is the correct serial port used? (try `ls /dev/tty*` or check Device Manager on Windows)")
		fmt.Println("  ✅ Do you have the necessary permissions?")
		fmt.Println("\n🔁 Restart the CLI after fixing the issue.")
		return
	}
	defer port.Close()

	fmt.Println("Calibration CLI started. Press:")
	fmt.Println("  [S] - Start Calibration")
	fmt.Println("  [R] - Record Gear (you'll be asked for the gear name)")
	fmt.Println("  [T] - Stop Recording Gear")
	fmt.Println("  [F] - Finish Calibration")
	fmt.Println("  [A] - Abort Calibration")
	fmt.Println("  [Q] - Quit")

	// Start reader goroutine to receive Arduino messages
	go readArduino(port)

	// Keyboard input loop
	reader := bufio.NewReader(os.Stdin)
	for {
		fmt.Print("\n> ")
		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(strings.ToLower(input))

		if input == "q" {
			fmt.Println("Exiting CLI...")
			break
		}

		if input == "r" {
			// Prompt user for the gear name
			fmt.Print("Enter gear to calibrate (<, N, >, 1, 2, 3, 4, 5, R): ")
			gearInput, _ := reader.ReadString('\n')
			gearInput = strings.TrimSpace(strings.ToUpper(gearInput))

			if validGears[gearInput] {
				command := fmt.Sprintf("RECORD_GEAR %s\n", gearInput)
				port.Write([]byte(command)) // Send gear name to Arduino
				fmt.Println("📡 Sent:", command)
				updateState(input)
			} else {
				fmt.Println("❌ Invalid gear name. Must be one of: <, N, >, 1, 2, 3, 4, 5, R")
			}
			continue
		}

		if command, exists := keyToCommand[input]; exists {
			port.Write([]byte(command)) // Send command to Arduino
			updateState(input)
		} else {
			fmt.Println("Invalid command. Press [S, R, T, F, A, Q].")
		}
	}
}

// Reads messages from the Arduino
func readArduino(port *serial.Port) {
	buf := make([]byte, 128)
	for {
		n, err := port.Read(buf)
		if err != nil {
			fmt.Println("Error reading from Arduino:", err)
			return
		}
		if n > 0 {
			fmt.Println("\n[ARDUINO]:", string(buf[:n]))
		}
	}
}

// Updates the state machine based on user input
func updateState(input string) {
	switch input {
	case "s":
		if currentState == Initial {
			currentState = Waiting
		}
	case "r":
		if currentState == Waiting {
			currentState = Recording
		}
	case "t":
		if currentState == Recording {
			currentState = Waiting
		}
	case "f":
		if currentState == Waiting {
			currentState = Calibrate
		}
	case "a":
		currentState = Initial
	}

	fmt.Println("Current State:", stateNames[currentState])
}
