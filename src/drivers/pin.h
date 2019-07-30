/*
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
 *
 *  file         : pin.h
 *  description  : GPIO pin manipulation class template for STM32 series.
 *
 */

/** @file */

#ifndef STM32_PIN_H_INCLUDED
#define STM32_PIN_H_INCLUDED

#if (defined STM32F2XX) || (defined STM32F4XX) || (defined STM32F40_41xxx) || (defined STM32F427_437xx) || (defined STM32F429_439xx) || (defined STM32F401xx)
#  include "pin_stm32F4xx.h"
#elif (defined STM32L051xx) || (defined STM32L052xx) || (defined STM32L053xx) || (defined STM32L061xx) || (defined STM32L062xx) || (defined STM32L063xx)
#  include "pin_stm32L0xx.h"
#elif (defined STM32L011xx)
#  include "pin_stm32L0xx.h"
#elif (defined STM32L1XX_MD) || (defined STM32L1XX_MDP) || (defined STM32L1XX_MDP) || (defined STM32L1XX_HD) || (defined STM32L1XX_XL)
#  include "pin_stm32L1xx.h"
#else
#error "Undefined STM32 version."
#endif

#endif // STM32_PIN_H_INCLUDED
