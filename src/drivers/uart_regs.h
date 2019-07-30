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
 *  UART registers and pins selection templates
 */

/**  @file */

#ifndef UART_REGS_H_INCLUDED
#define UART_REGS_H_INCLUDED

#include "stm32l0xx.h"

/**
 *  @brief enum for UART device selection
 */
enum uart_num_t {
    UART_2,
} ;

template<uart_num_t uart_num>
struct uart_regs_t
{
    typedef struct {
        uint32_t operator=(uint32_t value) {
            RCC->APB1ENR = value;
            return value;
        }
        void operator|=(uint32_t value) {
            RCC->APB1ENR |= value;
        }
        void operator&=(uint32_t value) {
            RCC->APB1ENR &= value;
        }
        operator uint32_t() {
            return RCC->APB1ENR;
        }
    } APBxENR;

    typedef struct {
        uint32_t operator=(uint32_t value) {
            RCC->APB1RSTR = value;
            return value;
        }
        void operator|=(uint32_t value) {
            RCC->APB1RSTR |= value;
        }
        void operator&=(uint32_t value) {
            RCC->APB1RSTR &= value;
        }
        operator uint32_t() {
            return RCC->APB1RSTR;
        }
    } APBxRST;

    typedef struct {
        operator uint32_t() {
            return RCC_APB1ENR_USART2EN;
        }
    } USARTxEN;

    typedef struct {
        operator uint32_t() {
            return RCC_APB1RSTR_USART2RST;
        }
    } USARTxRST;

    typedef struct {
        operator uint32_t() {
            return 32000000;
        }
    } BUS_FREQ;


    typedef struct {
        operator IRQn_Type() {
            return USART2_IRQn;
        }
    } USARTx_IRQn;

};

#endif // UART_REGS_H_INCLUDED
