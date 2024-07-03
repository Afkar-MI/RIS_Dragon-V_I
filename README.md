
# RIS_Dragon-V_I
This project involves designing and implementing a control board for a Reconfigurable Intelligent Surface (RIS). RIS_Dragon-V_I is a MSP430F5529 MCU based control board to  manage and control the output to a RIS board. The control board is designed to provide 520 output.

<img src="/Printed Final Product/Printed_Control board.jpg" width="1500" height="400">

## Table of Contents

- [Hardware Overview](#hardware-overview)
  - [Control Board Architecture](#control-board-architecture)
  - [MOSFET Circuit](#mosfet-circuit)
  - [Power Supply](#power-supply)
- [Pattern Generation](#pattern-generation)
- [Data Transmission Workflow](#data-transmission-workflow)
  - [Master MCU Workflow](#master-mcu-workflow)
  - [Slave MCU Workflow](#slave-mcu-workflow)
- [Acknowledgements](#acknowledgements)

## Hardware Overview

### Control Board Architecture

The control board consists of 11 MSP430F5529 MCUs: 1 Master MCU and 10 Slave MCUs. The architecture is designed as follows:
- **Master MCU**: Manages communication with the PC and coordinates data transmission to the Slave MCUs.
- **Slave MCUs**: Each manages a subset of the output pins connected to the RIS board.

The board forms a total of 520 output pins by soldering a P-channel MOSFET circuit to the GPIO pins of the Master and Slave MCUs:
- Master MCU: 20 GPIO pins
- Each Slave MCU: 50 GPIO pins

### MOSFET Circuit

Each GPIO pin is connected to a MOSFET circuit comprising:
- 1 PMOS transistor
- 2 resistors

The circuit operates as follows:
- Triggered by negative voltage values.
- Outputs 1 (3.3V) when input from MCU is 0.
- Outputs 0 (0V) when input from MCU is 1.

### Power Supply

The control board is powered by 26 single dc power lines and a USB providing 5V. In each DC power lines a linear voltage regulator (AZ1117I) converts the 5V input to 3.3V providing maximum current of 1.35A. Every 10 MOSFET circuits are powered by a single DC power lines and the all the 11 MCUs are powered from mini USB.

## Pattern Generation

Pattern generation is crucial for controlling the RIS. Each unit cell on the RIS board has 4 states (0, 1, 2, and 3), corresponding to different configurations of the PIN diodes:
- State 0: All 3 PIN diodes are off.
- State 1: Only PIN diode 1 is on.
- State 2: Only PIN diode 2 is on.
- State 3: Only PIN diode 3 is on.

A MATLAB algorithm generates a 10×10 array of patch states for the RIS, which has 100 patches. The states are mapped to control board pins in an Excel sheet. The states (1 for "OFF", 0 for "ON") are then used to generate a 65-byte binary file, which is converted to hexadecimal and saved in a text file.

## Data Transmission Workflow

### Master MCU Workflow

1. **Power Up**: Establishes a connection with the PC via USB and forms a UART connection for data transmission.
2. **Data Reception**: Receives 65 bytes of control signal data in hexadecimal format from the PC.
3. **Validation**: Validates the received data by verifying the header and length.
4. **Data Preparation**: Extracts and prepares data for each Slave MCU.
5. **SPI Transmission**: Connects to each Slave MCU in sequence and transmits the packed data.
6. **GPIO Configuration**: Configures its GPIO pins based on the received data.

### Slave MCU Workflow

1. **Data Reception**: Receives 11 bytes of pattern data from the Master MCU.
2. **Validation**: Verifies the header and length of the received data.
3. **GPIO Configuration**: Assigns the output for its GPIO pins based on the data.
4. **PMOS Triggering**: Operates the PIN diodes as per the input from the MCU.

## Acknowledgements

This project was made possible by the contributions of dedicated team members and the support of the development community.

---

Feel free to reach out for any questions or further information about this project.
