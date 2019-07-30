/*
  Copyright (c) 2019, Stefan Petersen/Ciellt AB

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/**
 * \mainpage
 * Test program for testing connections and functions of
 *  ST NUCLEO-32 STM32L011K4 evaluation board.
 */

/** @file */

#include "stm32l0xx.h"
#include "pin.h"
#include "uart.h"

// Pin mappings
using pin_led = Pin<'B', 3>;
using pin_debug = Pin<'B', 4>;
using pin_usart_tx = Pin<'A', 2>;
using pin_usart_rx = Pin<'A', 15>;

// SysTick register timing definitions
static constexpr std::uint32_t SYSTICKFREQ = UINT32_C(32000000);
static constexpr std::uint32_t SYSTICKINTRATE = UINT32_C(1000);

// Delays
static volatile std::uint32_t down_counter = 0;
static constexpr std::uint32_t DELAY_MS = UINT32_C(500);

using uart_t = dbg_uart_t<UART_2, 115200>;

int
main(void)
{
    pin_debug::Off();
    pin_led::Direct(OUTPUT);
    pin_debug::Off();
    pin_debug::Direct(OUTPUT);

    pin_usart_tx::Direct(ALT_OUTPUT);
    pin_usart_tx::Alternate(ALT_FUNC_4);
    pin_usart_rx::Direct(ALT_INPUT);
    pin_usart_rx::Alternate(ALT_FUNC_4);

    uart_t uart;
    uart.enable_rx_irq(4);

    // Systick register setup
    if (SysTick_Config(SYSTICKFREQ / SYSTICKINTRATE))
    {
        ;//FAIL
    }

    while (true)
    {
        uart.putch('H');
        pin_led::Off();
        down_counter = DELAY_MS;
        while (down_counter);
        uart.putch('I');
        pin_led::On();
        down_counter = DELAY_MS;
        while (down_counter);
    }
}

extern "C" void SysTick_Handler(void)
{
    pin_debug::Cpl();
    if (down_counter > 0) {
        --down_counter;
    }
} // SysTick_Handler

extern "C" void USART2_IRQHandler(void)
{
    volatile uint32_t status = USART2->ISR;
    if (status & USART_ISR_RXNE) {
        char key = USART2->RDR;
        USART2->TDR = key;
    }
} // USART2_IRQHandler
