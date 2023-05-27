//
// Created by resca on 19/02/2023.
//

#ifndef INC_001_MAKEFILE_TEST_DRV_UART_H
#define INC_001_MAKEFILE_TEST_DRV_UART_H

/***
 * Required Includes
 ***/

//MCU Include
#include "stm32f3xx.h"

//ANSI C
#include <stdint.h>
#include <stdbool.h>

/***
 * Prototype Public Functions
 ***/

void DRV_UART_Transmit(USART_TypeDef *USARTx, uint8_t *pData, uint32_t Size);
void DRV_UART_Receive(USART_TypeDef *USARTx, uint8_t *pData, uint32_t Size);

void DRV_UART_Print(USART_TypeDef *USARTx, char *pChar);

#endif //INC_001_MAKEFILE_TEST_DRV_UART_H
