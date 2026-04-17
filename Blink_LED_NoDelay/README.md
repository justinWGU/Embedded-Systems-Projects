# Blink Link LED Without Delay

### About
This STM32 was developed to blink an LED every second without blocking (using HAL_Delay).


### Requirements

Hardware
- Nucleo-F401RE development board
- connecting wires
- PC
- Usb cable

Software
- C
- HAL library
- STM32CubeIDE


### Design
Here I will describe the software design in this application. 
The software consists of the following peripherals:
- basic timer for counting to 1 second
- GPIO pin to control LED
The timer generates an interrupt every second, switching the toggleLED flag on.
Then in the while loop, the LED is toggled depending on this flag. If the LED is switched on, the
toggleLED flag is switched off again, until the next interrupt.
