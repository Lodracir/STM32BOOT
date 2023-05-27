//
// Created by resca on 19/02/2023.
//

#ifndef INC_001_MAKEFILE_TEST_STM32F3XX_IT_H
#define INC_001_MAKEFILE_TEST_STM32F3XX_IT_H

/***
 * Required Includes
 ***/

//MCU Include
#include "stm32f3xx.h"

//Drivers Include
#include "BOOT.h"

/***
 * Prototype Public Functions
 ***/
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#endif //INC_001_MAKEFILE_TEST_STM32F3XX_IT_H
