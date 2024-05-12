# PIC18F4620 Drivers

This repository contains drivers for various peripherals and components for the PIC18F4620 microcontroller, organized into two layers: the MCAL (Microcontroller Abstraction Layer) and the ECU (Embedded Control Unit) layer. Additionally, an application layer is provided to facilitate easy implementation of user applications using the provided drivers.

## MCAL Layer

The MCAL layer includes drivers for the following peripherals:

- **USART**
  - `usart.c`
  - `usart.h`
- **Timer3**
  - `timer3.c`
  - `timer3.h`
- **Timer2**
  - `timer2.c`
  - `timer2.h`
- **Timer1**
  - `timer1.c`
  - `timer1.h`
- **Timer0**
  - `timer0.c`
  - `timer0.h`
- **SPI**
  - `spi.c`
  - `spi.h`
- **Interrupt**
  - `interrupt.c`
  - `interrupt.h`
- **I2C**
  - `i2c.c`
  - `i2c.h`
- **GPIO**
  - `gpio.c`
  - `gpio.h`
- **EEPROM**
  - `eeprom.c`
  - `eeprom.h`
- **ADC**
  - `adc.c`
  - `adc.h`

## ECU Layer

The ECU layer includes drivers for the following components:

- **Relay**
  - `relay.c`
  - `relay.h`
- **LM35**
  - `lm35.c`
  - `lm35.h`
- **LED**
  - `led.c`
  - `led.h`
- **KeyPad**
  - `keypad.c`
  - `keypad.h`
- **DC Motor**
  - `dc_motor.c`
  - `dc_motor.h`
- **Chr_LCD**
  - `chr_lcd.c`
  - `chr_lcd.h`
- **PUSH_BUTTON**
  - `button.c`
  - `button.h`
- **7 Segment**
  - `7_segment.c`
  - `7_segment.h`

## Application Layer

The application layer provides an `application.c` and `application.h` file, which contain a main function and other necessary functions to implement your application directly. These files utilize the documented drivers from both the MCAL and ECU layers, allowing you to easily interface with various peripherals and components without needing to implement them from scratch.

## Usage

To use the provided drivers and application layer:

1. Include the necessary `.h` files in your project.
2. Implement your application logic in the `application.c` file.
3. Utilize the functions provided in the `application.h` file to interact with the drivers.

## Documentation

Each driver is documented within its respective `.c` and `.h` files to provide clear usage instructions and descriptions of functionality.

## Contributing

Contributions to improve existing drivers or add support for additional peripherals/components are welcome. Please follow the contribution guidelines outlined in the repository.


