# Button Triggered Buzzer Interrupt

## About
This STM32 firmware sounds an active buzzer when a button triggers an interrupt.

### Wiring
PC13 -> internally wired to B1 button
PA12 -> buzzer positive
GND -> buzzer GND

### Requirements
Hardware
Software

### Design
This projects consists of the following peripherals:
- GPIO pin for button
- GPIO pin for active buzzer

The button triggers an interrupt when pressed, then in its ISR,
the buzzer's control flag is switched on. In the while loop,
the flag's value is read and the buzzer's pin is toggled, followeg
by resetting the flag's value. Only the flag is switched on in the
ISR to prevent it from blocking. 