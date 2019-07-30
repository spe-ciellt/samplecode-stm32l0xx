/**
 * linker script for STM32L011K4 Devices
 */ 

MEMORY
{
	FLASH (rx)	: ORIGIN = 0x08000000, LENGTH = 8K
	RAM (xrw)	: ORIGIN = 0x20000000, LENGTH = 2K
}

INCLUDE "stm32.ld"
