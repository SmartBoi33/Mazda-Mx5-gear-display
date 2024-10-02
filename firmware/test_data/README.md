# Test Data Directory

## Overview
This directory contains the test data used for unit testing the firmware code that controls the LED Gear Display for the Mazda MX-5. The test data includes sensor values and expected outputs for detecting the current gear, as well as the transitions between gears. These tests ensure that the firmware accurately reads sensor data and correctly updates the display based on gear shifts.

## Test Cases

### 1. Single Gear Detection
- **R (Reverse)** → Expected: Reverse
- **1 (First Gear)** → Expected: Gear 1
- **2 (Second Gear)** → Expected: Gear 2
- **3 (Third Gear)** → Expected: Gear 3
- **4 (Fourth Gear)** → Expected: Gear 4
- **5 (Fifth Gear)** → Expected: Gear 5

### 2. Gear-to-Gear Transitions
- **R** → 1: Expected: Gear 1
- **R** → 2: Expected: Gear 2
- **R** → 3: Expected: Gear 3
- **R** → 4: Expected: Gear 4
- **R** → 5: Expected: Gear 5
- **1** → R: Expected: Reverse
- **1** → 2: Expected: Gear 2
- **1** → 3: Expected: Gear 3
- **1** → 4: Expected: Gear 4
- **1** → 5: Expected: Gear 5
- **2** → R: Expected: Reverse
- **2** → 1: Expected: Gear 1
- **2** → 3: Expected: Gear 3
- **2** → 4: Expected: Gear 4
- **2** → 5: Expected: Gear 5
- **3** → R: Expected: Reverse
- **3** → 1: Expected: Gear 1
- **3** → 2: Expected: Gear 2
- **3** → 4: Expected: Gear 4
- **3** → 5: Expected: Gear 5
- **4** → R: Expected: Reverse
- **4** → 1: Expected: Gear 1
- **4** → 2: Expected: Gear 2
- **4** → 3: Expected: Gear 3
- **4** → 5: Expected: Gear 5
- **5** → R: Expected: Reverse
- **5** → 1: Expected: Gear 1
- **5** → 2: Expected: Gear 2
- **5** → 3: Expected: Gear 3
- **5** → 4: Expected: Gear 4

These test cases will be used to validate the correct operation of the firmware’s gear detection and transition logic.
