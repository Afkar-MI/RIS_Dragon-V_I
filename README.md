
# RIS Dragon V-I
This project involves designing and implementing a control board for a Reconfigurable Intelligent Surface (RIS). RIS Dragon V-I is a MSP430F5529 MCU based control board to  manage and control the output to a RIS board. The control board is designed to provide 520 output. The following figure shows the RIS Dragon V-I board.

<img src="/Printed Final Product/Printed_Control board.jpg" width="946" height="302">

## Table of Contents

- [Hardware Overview](#hardware-overview)
  - [Control Board Architecture](#control-board-architecture)
  - [MOSFET Circuit](#mosfet-circuit)
  - [Power Supply](#power-supply)
  - [Software](#software)
- [Firmware Development](#firmware-development)
  - [Master MCU Workflow](#master-mcu-workflow)
  - [Slave MCU Workflow](#slave-mcu-workflow)
  - [Software](#software-1)
- [Acknowledgements](#acknowledgements)

## Hardware Overview

### Control Board Architecture

The control board consists of 11 MSP430F5529 MCUs: 1 Master MCU and 10 Slave MCUs. The architecture is designed as follows:
- **Master MCU**: Manages communication with the PC via UART communication protocol and coordinates data transmission to the Slave MCUs via SPI communication protocol.
- **Slave MCUs**: Each manages a subset of the output pins connected to the RIS board.

The board forms a total of 520 output pins by soldering a P-channel MOSFET circuit to each GPIO pins of the Master and Slave MCUs:
- Master MCU: 20 GPIO pins
- Each Slave MCU: 50 GPIO pins

Each MCU has 9 output ports which give 63 independent GPIO pins. Out of 63 GPIO pins, only 50 pins were used to establish the outputs for the control board. 
<img src="/CB Architecture/CB Architecture.JPG" width="730" height="407">

### MOSFET Circuit

Each GPIO pin is connected to a MOSFET circuit comprising:
- 1 PMOS transistor
- 2 resistors

The circuit operates as follows:
- Triggered by negative voltage values.
- Outputs 1 (3.3V) when input from MCU is 0.
- Outputs 0 (0V) when input from MCU is 1.

<img src="/CB Architecture/PMOS.JPG" width="139" height="214">

### Power Supply

The control board is powered by 26 single dc power lines and a USB providing 5V. In each DC power lines a linear voltage regulator (AZ1117I) converts the 5V input to 3.3V providing maximum current of 1.35A. Every 10 MOSFET circuits are powered by a single DC power lines and the all the 11 MCUs are powered from mini USB.

### Software
RIS Dragon V-I control board PCB was designed using [Altium Designer](https://www.altium.com/altium-designer)

## Firmware Development
Upon powering up, the Master MCU established a connection with a PC via USB and formed a UART connection for data transmission. The Master MCU received a control signal data of 67 bytes, in hexadecimal format, from the PC. It then validated the received data by verifying the header and length flag. Subsequently, the Master MCU extracted the relevant data and packed it for each Slave MCU. Using the SPI transmission protocol, the Master MCU established a connection with the first Slave MCU and sent the packed data to it. Once the data transfer was complete, the Master MCU disconnected from the first Slave MCU. This process was repeated for the remaining Slave MCUs. Following the data transmission, the Master MCU configured the output for its GPIO pins. 

After establishing the connection with the Master MCU, each Slave MCU received the pattern data of 11 bytes from the Master MCU. The Slave MCU then authenticated the received data by verifying the header and length. Afterwards, the Slave MCU assigned the output for its GPIO pins. Then the PMOS was triggered as per the input from the MCU, and the PIN diodes were operated.

```
Master MCU Receive Data 67 bytes = [Header(1 bytes)]+[Lenght Flag (1 Byte)]+[520 bits/8 (65 Bytes)]
Slave MCU Data 11 Bytes  = [Header(1 bytes)]+[Lenght Flag (1 Byte)]+[9 ports (9 bytes)]
```
### Master MCU Workflow

1. **Power Up**: Establishes a connection with the PC via USB and forms a UART connection for data transmission.
2. **Data Reception**: Receives 65 bytes of control signal data in hexadecimal format from the PC.
3. **Validation**: Validates the received data by verifying the header and length.
4. **Data Preparation**: Extracts and prepares data for each Slave MCU.
5. **SPI Transmission**: Connects to each Slave MCU in sequence and transmits the packed data.
6. **GPIO Configuration**: Configures its GPIO pins based on the received data.


<img src="/Flow Chart/Flow_Chart_Master_MCU.JPG" width="306" height="806">

### Slave MCU Workflow

1. **Data Reception**: Receives 11 bytes of pattern data from the Master MCU.
2. **Validation**: Verifies the header and length of the received data.
3. **GPIO Configuration**: Assigns the output for its GPIO pins based on the data.
4. **PMOS Triggering**: Operates the PIN diodes as per the input from the MCU.

<img src="/Flow Chart/Flow_Chart_Slave_MCU.jpg" width="296" height="585">

### Software
The firmaware was developed on the Texas Intruments IDE [Code Composer Studio](https://www.ti.com/tool/CCSTUDIO#gui) 

## Acknowledgements

This project was made possible by the contributions of my supervisor Dr Zhao Yufei(Research Fellow, Nanyang Technological University, Singapore) and Dr Feng Yuan (Research Fellow, National University of Singapore)

---

Feel free to reach out for any questions or further information about this project.
