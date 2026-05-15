# LPC2129 Access Control System

# Overview
An embedded access control system developed using ARM7 LPC2129 microcontroller with keypad-based password authentication and OTP verification.

The project demonstrates low-level peripheral interfacing, modular embedded firmware design, EEPROM-based credential storage, UART communication, I2C protocol handling, LCD interfacing, and motor control.

# Features
- 4-digit keypad password authentication
- OTP verification system
- EEPROM credential storage using I2C
- LCD-based user interface
- UART communication support
- DC motor-based access control
- LED indication during motor operation
- Modular driver-based firmware architecture

# Hardware Used
- ARM7 LPC2129 Microcontroller
- 4x4 Matrix Keypad
- 16x2 LCD
- EEPROM
- GSM Module
- L293D Motor Driver
- DC Motor
- LEDs
- 
# Communication Protocols
- UART
- I2C

# Software Used
- Keil uVision
- Proteus Professional



## Project Architecture

### Application Layer
- Password authentication
- OTP verification
- Access control logic

### Driver Layer
- UART Driver
- LCD Driver
- Keypad Driver
- I2C Driver
- EEPROM Driver
- Motor Driver
- Delay Driver

### Hardware Layer
- LPC2129 peripherals
- EEPROM
- LCD
- Keypad
- Motor driver


# Proteus Simulation

<img src="images/proteus_simulation.png" width="700">



# Future Improvements
- Interrupt-based UART communication
- Password encryption
- RTOS-based task scheduling
- RFID authentication
- Biometric authentication
- PWM motor speed control
