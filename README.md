# raspberry_cas_sp2

Proposal _Computation of interrupt delay of a Raspberry PI 3 using Raspbian. A signal generator must be used to input a periodic square wave on a pin of the GPIO port. An interrupt must be raised by the signal. The interrupt handler routine must put at 1 another pin of the GPIO port, switching on an LED. An oscilloscope must visualize the output signal and compare input and output timings, in order to compute the delay introduced by the use of the operating system in managing the hardware interrupt. What happens if additional load is given to the Cortex A-53, given the four cores in the Raspberry? How much the mean and standard deviation of the latency is affected by the launch of other programs or by additional interrupts as the ones produced by the mouse?_

# Introduction

In order to test the code on your Raspberry Pi 3 you should have:
 - Raspberry Pi 3 with Raspbian installed
 - SD card
 - Power supply(min 2 Ampere, 5V)
 - HDMI Cable
 - Keyboard
 - Mouse
 - Board
 - Wires for connections
 - LEDs
