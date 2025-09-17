# ATmega32 Smart Home Automation System

A microcontroller-based home automation system that allows wireless control of appliances via Bluetooth using an ATmega32 chip.

## Features
- Wireless Bluetooth control from smartphone
- DC and servo motor control
- Relay-based device switching
- Real-time status monitoring
- Secure authentication system

## Hardware Components
- ATmega32 Microcontroller
- HC-05 Bluetooth Module
- Relay Modules (4-channel)
- DC Motors with drivers
- Servo Motors
- LCD Display (16x2)
- Push Buttons
- LEDs for status indication

## Installation

1. Connect components:
   - Bluetooth: PA0(RxD) and PA1(TxD)
   - Relays: PC0-PC3
   - Motors: PD4-PD7
   - LCD: PORTB
   - Buttons: PA2-PA5

2. Program ATmega32 using ISP programmer
3. Install Bluetooth terminal app on phone

## Usage

1. Power on the system
2. Pair with "ATmega32-SmartHome" (PIN: 1234)
3. Send commands:
   - "LOGIN" to access control system
   - "LIGHT ON"/"LIGHT OFF"
   - "FAN ON"/"FAN OFF"
   - "CURTAIN OPEN"/"CURTAIN CLOSE"
   - "STATUS" to check device states

## Technical Specifications
- Microcontroller: ATmega32 (8-bit AVR)
- Clock Speed: 16MHz
- Communication: UART Bluetooth
- Operating Voltage: 5V DC
- Relay Rating: 10A/250V AC


## Safety Notes
- Use proper insulation for high-voltage connections
- Include fuse protection in main power line
- Ensure proper heat dissipation for regulators
- Keep system away from water sources

## Development Tools
- Atmel Studio 7
- Proteus for simulation
- AVRDUDE for programming
- Terminal app for testing

---
*Note: This system demonstrates embedded programming concepts and should be enhanced with proper security measures for production use.*
