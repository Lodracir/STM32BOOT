//
// Created by lodracir on 23/02/23.
//

#ifndef INC_001_MAKEFILE_TEST_DRV_RCC_H
#define INC_001_MAKEFILE_TEST_DRV_RCC_H

/***
 * Required Includes
 ***/

//MCU Include
#include "stm32f3xx.h"

//ANSI C
#include <stdint.h>

/***
 * Defines
 ***/

#define HSI_CLOCK_SPEED 8000000

#define _DRV_RCC_AHBENR_IOPAEN  (1U << 17)
#define _DRV_RCC_AHBENR_IOPBEN  (1U << 18)
#define _DRV_RCC_AHBENR_IOPCEN  (1U << 19)
#define _DRV_RCC_AHBENR_ADC12EN (1U << 28)

#define _DRV_RCC_APB1ENR_USART2 (1 << 17)

#define _DRV_RCC_APB2ENR_SPI1   (1 << 12)
#define _DRV_RCC_APB1ENR_SPI2   (1 << 14)
#define _DRV_RCC_APB1ENR_SPI3   (1 << 15)

/***
 * MACROS
 ***/

#define _DRV_RCC_GPIOA_CLK_Enable()     (RCC->AHBENR |= _DRV_RCC_AHBENR_IOPAEN)
#define _DRV_RCC_GPIOB_CLK_Enable()     (RCC->AHBENR |= _DRV_RCC_AHBENR_IOPBEN)
#define _DRV_RCC_GPIOC_CLK_Enable()     (RCC->AHBENR |= _DRV_RCC_AHBENR_IOPCEN)
#define _DRV_RCC_ADC12_CLK_Enable()     (RCC->AHBENR |= _DRV_RCC_AHBENR_ADC12EN)

#define _DRV_RCC_USART2_CLK_Enable()    (RCC->APB1ENR |= _DRV_RCC_APB1ENR_USART2)

#define _DRV_RCC_SPI1_CLK_Enable()      (RCC->APB2ENR |= RCC_APB2ENR_SPI1EN)
#define _DRV_RCC_SPI2_CLK_Enable()      (RCC->APB1ENR |= _DRV_RCC_APB1ENR_SPI2)
#define _DRV_RCC_SPI3_CLK_Enable()      (RCC->APB1ENR |= _DRV_RCC_APB1ENR_SPI3)

#endif //INC_001_MAKEFILE_TEST_DRV_RCC_H
