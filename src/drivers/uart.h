/*
 *  Copyright (c) 2011-2012 by Anton Gusev aka AHTOXA
 *  Copyright (c) 2019, Stefan Petersen/Ciellt AB
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */

/**
 * Driver for UART in STM32L0 series of microcontrollers.
 */

/**  @file */

#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

#include "uart_regs.h"

/**
 *  @brief UART template class.
 *  @param uart_num: select which UART peripheral to use.
 *  @param baud: select UART speed.
 */
template<uart_num_t uart_num, uint32_t baud = 115200>
class dbg_uart_t;

template<uart_num_t uart_num, uint32_t baud>
class dbg_uart_t
{
private:
    typedef uart_regs_t<uart_num> uart_regs;
    typename uart_regs::APBxENR APBxENR;
    typename uart_regs::APBxRST APBxRST;
    typename uart_regs::USARTxEN USARTxEN;
    typename uart_regs::USARTxRST USARTxRST;
    typename uart_regs::BUS_FREQ BUS_FREQ;
    typename uart_regs::USARTx_IRQn USARTx_IRQn;
public:
    static struct
    {
        USART_TypeDef* operator-> ()
        {
            return USART2;
        }
    } USARTx;

    INLINE dbg_uart_t()
    {
        // If not enabled, reset and enable module
        if ((APBxENR & USARTxEN) == 0) {
            APBxRST |= USARTxRST;
            APBxRST &= ~USARTxRST;
            APBxENR |= USARTxEN;
        }

        // Configure speed and format
        USARTx->CR1 = USART_CR1_RE | USART_CR1_TE;
        USARTx->CR2 = 0; // 1 stop
        USARTx->CR3 = 0; // no flow control
        USARTx->BRR = BUS_FREQ / baud;  // 9 - PLL multiplier
        USARTx->CR1 |= USART_CR1_UE;
    }
    void enable_rx_irq(uint8_t priority)
    {
        USARTx->CR1 |= USART_CR1_RXNEIE;
        NVIC_ClearPendingIRQ(USARTx_IRQn);
        NVIC_SetPriority(USARTx_IRQn, priority);
        NVIC_EnableIRQ(USARTx_IRQn);
    }
    void putch(char ch);
};

template<uart_num_t uart_num, uint32_t baud>
void dbg_uart_t<uart_num, baud>::putch(char ch)
{
    while (!(USARTx->ISR & USART_ISR_TXE)) ;
    USARTx->TDR = ch;
}

#endif // UART_H_INCLUDED
