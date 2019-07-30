## Blinken light demo for STM32L0xx series

A simple test program to test that your (first and foremost)
ST NUCLEO-32 STM32L011K4 evaluation board is up and running.

It is supposed to be used when the built-in programmer of the
evaluation board (STM32F103) is updated with and running the open-source
[BlackMagic dongle](https://github.com/blacksphere/blackmagic).

Can also be used as a start for a bare metal project using any STM32L0xx series.

### What it does
* It blinks the LED of the board with 1 Hz (500 ms on, 500 ms off).
* It sends characters to the USART2 when blinking ("HI").
* It echos characters on the USART2

### Settings
* The USART sends with 115200 N81.