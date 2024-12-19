# STM32 Bare Metal Programming Journey

This repository documents my journey in learning and implementing STM32 bare-metal programming. Starting from the basics of LED blinking to complex integrations like sending data to the cloud using ESP-01, each project builds upon the previous one, showcasing a structured progression of my understanding.

---

## Table of Contents

1. [LED Blinking](./blink)
2. [UART Programming](./UART_F401RE)
3. [GPIO Interrupts](./gpio_interrupt)
4. [Using SysTick for Delays](./delay)
5. [Task Scheduler](./task_scheduler)
6. [Fault Handling](./faults)
7. [Analog-to-Digital Conversion (ADC)](./adc)
8. [LCD Interfacing](./lcd)
9. [Pulse Width Modulation (PWM)](./pwm)
10. [I2C with ADXL345](./i2c)
11. [SPI with ADXL345](./spi)
12. [Controlling Relays with HC-05](./hc05_relays)
13. [Sending Data to the Cloud using ESP-01](./esp01_AT)

---

## Highlights

### Early Stages: Magic Numbers and Macros
Initially, I relied heavily on magic numbers and macros to define the addresses of the necessary registers. This approach provided a foundational understanding of STM32's hardware-level programming by interacting directly with memory-mapped registers.

### Transition to Using `stm32f4xx.h`
During my exploration, I came across the `stm32f4xx.h` file in the [Drivers](./Drivers) directory. This header file provided predefined register addresses, structures, and peripheral definitions, which significantly streamlined the development process. After this discovery, I incorporated it into my projects to simplify code and enhance maintainability.

---

## Overview

1. **LED Blinking**: My first project focused on understanding GPIO by toggling an LED.
2. **UART Programming**: Introduced UART communication to interact with external devices.
3. **GPIO Interrupts**: Explored interrupt-driven programming for efficient GPIO handling.
4. **SysTick Delays**: Used the SysTick timer to generate precise delays for task management.
5. **Task Scheduler**: Built a basic task scheduler to manage multiple concurrent processes.
6. **Fault Handling**: Learned fault diagnostics and handling for robust applications.
7. **ADC**: Explored Analog-to-Digital Conversion for sensor integration.
8. **LCD Interfacing**: Worked on interfacing an LCD for displaying data.
9. **PWM**: Implemented Pulse Width Modulation to control motors and LEDs.
10. **I2C and SPI**: Communicated with the ADXL345 sensor using both I2C and SPI protocols.
11. **HC-05 Relays**: Controlled relays using Bluetooth communication.
12. **ESP-01**: Sent sensor data to the cloud via ESP-01 and AT commands, integrating with ThingSpeak.

---

## How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/Jjateen/stm32-bare-metal.git
   ```
2. Navigate to the project of interest and follow the code or comments provided for guidance.

---

## Future Goals

- Expand upon advanced STM32 peripherals and interfaces.
- Explore RTOS-based development for multi-tasking applications.
- Build more robust IoT and embedded systems.
