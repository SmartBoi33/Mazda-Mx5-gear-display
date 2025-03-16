# Calibration CLI for Arduino Gear Display

This CLI tool **interacts with the Arduino gear shifter calibration system** via USB. It sends **commands** to the Arduino and receives **real-time feedback**, allowing users to control the calibration process.

---

## **📌 How It Works**
The CLI follows a **state machine** that mirrors the calibration process on the Arduino. Users trigger events using keyboard shortcuts to record sensor values and finalize calibration.

---

## **📌 How to Use**
### **1️⃣ Navigate to the CLI Directory**
Since this is part of a **monorepo**, go to the **CLI folder**:
```sh
cd calibration-cli
```

### **2️⃣ Install Dependencies**
Ensure Go modules are set up:
```sh
go mod tidy
```
If dependencies are missing, install:
```sh
go get github.com/tarm/serial
```

### **3️⃣ Connect the Arduino**
#### **🔹 macOS/Linux**
Plug in your **Arduino via USB** and check the serial port:
```sh
ls /dev/tty.*
```
On Linux, it might be `/dev/ttyUSB0`. On macOS, it might be `/dev/tty.usbserial-XXXXX`.

#### **🔹 Windows**
1. **Find the COM port**:
   - Open **Device Manager** (`Win + X → Device Manager`).
   - Expand **Ports (COM & LPT)**.
   - Look for something like **"Arduino Uno (COM3)"**.
   - **Note the COM number** (e.g., `COM3`).

---

## **4️⃣ Run the CLI**
### **🔹 macOS/Linux**
```sh
go run main.go
```
or **build an executable**:
```sh
go build -o calibration-cli
./calibration-cli
```

### **🔹 Windows**
```sh
go run main.go -port COM3
```
or **build an executable**:
```sh
go build -o calibration-cli.exe
calibration-cli.exe -port COM3
```
Replace `COM3` with your actual port.

---

## **🎮 Keyboard Controls**
| Key | Command Sent | State Transition |
|----|--------------|------------------|
| `S` | `START` | `Initial` → `Waiting` |
| `R` | `RECORD_GEAR` | `Waiting` → `Recording` |
| `T` | `STOP_RECORD` | `Recording` → `Waiting` |
| `F` | `FINISH` | `Waiting` → `Calibrate` |
| `A` | `ABORT` | Resets to `Initial` |
| `Q` | Quit CLI | Exit program |

---

## **🖥️ Example Usage**
```
Calibration CLI started. Press:
  [S] - Start Calibration
  [R] - Record Gear
  [T] - Stop Recording Gear
  [F] - Finish Calibration
  [A] - Abort Calibration
  [Q] - Quit

> S
Current State: Waiting
> R
Current State: Recording
> T
Current State: Waiting
> F
Current State: Calibrate
> A
Current State: Initial
```

---

## **⚠️ Troubleshooting**
### **🔹 CLI fails to open serial port?**
- **macOS/Linux:**
  - Ensure Arduino is plugged in.
  - Run: `ls /dev/tty*` to find the correct port.
  - Check permissions: `sudo chmod 666 /dev/ttyUSB0`.

- **Windows:**
  - Check **Device Manager** (`Win + X → Device Manager`).
  - Ensure drivers for **Arduino USB-to-Serial** are installed.
  - Try another port, e.g., `-port COM4`.

### **🔹 Go module error?**
- Run: `go mod tidy`
- Ensure **Go 1.23+** is installed.
