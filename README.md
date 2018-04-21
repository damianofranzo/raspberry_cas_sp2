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
 
Moreover, in order to check the results of the project, there are additional devices, such as:
 - Oscilloscope
 - Signal Generator
 
The delay time between raise up and raise down of the output signal is to set to 50ms. In order to change it, the variable is associated to that value, which has to be changed.
Make sure to clone the repository, which is available in:
https://github.com/damianofranzo/raspberry_cas_sp2
### Connections
If you want to test the result, you should have an oscilloscope and a signal generator. In every solution the Input GPIO is GPIO7 and the Output GPIO is GPIO12, so make sure that the Raspberry GPIO and other devices are connected in this way:
{second.jpg}
Otherwise, providing a square wave with GPIO21 this should be the configuration.
{first.jpg}
# RPi library, User-level ISR
In the folder pythonuserinterrupt there is a Python program that creates an Interrupt Handler. This is a very high level of ISR, in fact, the performance is low compared with the kernel module solution.
For running the program just execute in the shell
```sh
$./interrupt_handler.py
```
Then press Enter to stop the program.
# Wiring Pi library, another User-level ISR
### Compile
To compile the program is just necessary to move in the folder cuserinterrupt and execute
```sh
$sudo make
```
### Execute
To execute the code press
```sh
$./interrupt_handler.o
```
# LKM(Loadable Kernel Module), a real ISR
There are several ways to add the kernel module.
Our suggestion is to use RPi-Soure, which is the kernel-headers Raspbian package.
### Install RPi-source
RPi-Source install the kernel source code, and make possible to add the kernel modules.
To install the package follow the steps provided in the github page of the package https://github.com/notro/rpi-source/wiki
### Compile and execution
Through the RPi-Source is possible to add kernel modules without recompiling the entire kernel. So, first it's necessary to compile the kernel module in order to add it in the kernel.
To compile the code, open the shell in the folder of lkminterrupt and execute
```sh
$sudo make
```
### Execution
If the compilation process has been successful, you have to load the module in the kernel, to do that you have to execute
```sh
$sudo insmod ISRgpiointerrupts.ko
```
To check if the interrupt line is active, execute in the shell
```sh
$cat /proc/interrupts
```
If the previous operation has been successful, the entry "gpiointerrupts" should be in the output
Now you have loaded the module in the kernel, so when the signal in the Input-GPIO will raise up, the Output-GPIO will raise up, wait for the delay-time and then the it will go down

### Remove the module
To remove the module you have to execute:
```sh
$sudo rmmod ISRgpiointerrupts.ko
```

# Additional informations and further documentations

