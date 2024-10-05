# Gear Shift Detection using Two Gyroscopes

## Overview of the Approach

Detecting gear shifts using two gyroscopes involves measuring angular velocity on different axes. In this approach:
- One gyroscope is mounted to monitor the **car's angular position** (reference).
- The second gyroscope is attached to the **gear shifter** to detect its movement relative to the car.

By subtracting the car’s position from the gear shifter’s position, you can determine the exact **x-y position** of the shifter, relative to the car's frame. This relative motion can be mapped to gear shifts, as each gear has a distinct position pattern.

### Features of this Approach:
- **Relative Movement Tracking**: Using two gyroscopes allows accurate tracking of the gear shift by measuring how much the gear stick moves relative to the car's frame.
- **Minimal Intrusion**: This method doesn’t require complex mechanical setups like shift sensors. It relies on movement data.
- **Low-latency Detection**: Gyroscopes provide real-time angular velocity, meaning gear shifts can be detected quickly.

### Challenges:
- **Gyroscope Drift**: Over time, the gyroscopes may introduce drift, causing inaccuracies in detecting gear shifts.
- **Vibration and Noise**: In a car, vibrations from the engine or road surface can add noise to the sensor data, complicating detection.
- **Initial Calibration**: The system needs an initial reference for the car’s and shifter's "zero" positions. Calibration may be required regularly.
- **Multiple Axes Calculation**: Gear shifting involves complex movement in more than one axis (x, y, z), which makes the computation and mapping more challenging.

## The MPU-6050 on the GY-521 Board

The **MPU-6050** on the GY-521 board combines a **3-axis gyroscope** and a **3-axis accelerometer**. This allows it to detect both **angular velocity** and **linear acceleration** on all axes.

- **Pins**: The GY-521 uses **I²C** communication to send data. It has **VCC, GND, SCL (clock), SDA (data)** pins for communication and power.
- **Data**: The gyroscope provides angular velocity values for the X, Y, and Z axes. The accelerometer provides linear acceleration for these axes.

### I²C Communication
The GY-521 communicates over the **I²C protocol**, which uses two wires (SDA and SCL) to transfer data between devices. You can read sensor values by requesting data over I²C from the MPU-6050’s registers.

## Software Prototype for Gear Detection

### First Prototype
A simple software prototype would read data from the two GY-521 boards via I²C. This prototype would:
1. **Initialize I²C communication** with both sensors.
2. **Read angular velocity** values from both boards (car gyroscope and gear shifter gyroscope).
3. **Subtract** the car’s position (first board) from the gear shifter’s position (second board).
4. **Map** the resulting values to known gear positions (e.g., forward position = first gear, etc.).
5. **Detect and output the gear** based on the x-y position of the shifter relative to the car.

### Example Workflow
1. **Initialize** I²C communication.
2. **Collect data** from both boards at regular intervals (e.g., every 50 ms).
3. **Apply mapping** logic to detect which gear corresponds to the current shifter position.
4. **Output gear** on an LED display or via a serial monitor.

## Further Optimizations

### 1. **Complementary Filter**
A complementary filter could be used to combine **gyroscope** and **accelerometer** data for a more accurate result. The accelerometer can help with long-term stability (e.g., reducing drift), while the gyroscope handles quick, short-term shifts.

### 2. **Kalman Filter**
A **Kalman filter** is more computationally expensive but can provide a more accurate and robust way of tracking movement by predicting the next position based on previous data. It reduces noise and compensates for drift effectively.

### 3. **Calibration**
Automatic or manual calibration routines could be built into the system to set the initial reference point for the car and gear shifter positions. This could also account for sensor inaccuracies and environmental factors like vibration.

### 4. **Noise Reduction**
Given the harsh automotive environment, implementing noise reduction techniques like **low-pass filtering** or **sensor fusion** would improve the accuracy of gear shift detection.

## Conclusion

Using two gyroscopes along with an accelerometer is a promising method to detect gear shifts in a vehicle. The MPU-6050 on the GY-521 board provides both gyroscope and accelerometer data, which can be leveraged for precise gear detection. By improving the system with filters and calibration, a robust and accurate gear detection system can be created for the Mazda MX-5.
