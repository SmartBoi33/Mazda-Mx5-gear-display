# LED Gear Display for Mazda MX-5

## Overview
This project aims to build an **LED Gear Display** for a Mazda MX-5, allowing real-time gear information to be displayed on a small LED screen.

## Features
- Real-time gear detection and display
- Bright, visible LED display for easy gear status reading
- Low-latency, responsive updates based on the car's gear shifts
- Modular and easy to install in the Mazda MX-5
- ...

## Compatibility
- Current construction and testing on the **5 Speed** Gearbox with an **IL-Motorsport Shortshifter**
- Possible addition of standart 5 and 6 Speed compatibility in the future

## Project Structure
The project is split into **hardware** and **software** components.

```plaintext
LED-Gear-Display/
│
├── hardware/
│   ├── schematics/       # Circuit diagrams, PCB designs
│   ├── components/       # Component specs and datasheets
│   ├── assembly/         # Photos and instructions for building the setup
├── firmware/
│   ├── src/              # Microcontroller code (e.g., Arduino)
│   ├── lib/              # Libraries used in the firmware
│   ├── tests/            # Tests related to firmware performance
│
├── docs/                 # Documentation for users and developers
│   ├── user_manual.md    # Setup and usage instructions
│   ├── development.md    # Development documentation
│
├── LICENSE               # License information
└── README.md             # This file
```

### Assembly Instructions
For detailed assembly instructions, refer to the [ASSEMBLY.md](repo/ASSEMBLY.md) file in the repository.

## Installation
For a detailed installation guide, refer to the [INSTALLATION.md](repo/INSTALLATION.md) file in the repository.

## Contributions
Feel free to contribute to this project by:
- Suggesting new features
- Reporting bugs
- Submitting pull requests for code or documentation improvements

## License
This project is licensed under the Apache 2.0 License - see the [LICENSE](LICENSE) file for details.
