//
// Created by lodracir on 24/02/23.
//

#ifndef INC_001_MAKEFILE_TEST_DRV_TIMEBASE_H
#define INC_001_MAKEFILE_TEST_DRV_TIMEBASE_H

/***
 * Required Includes
 ***/

//MCU Include
#include "stm32f3xx.h"

//Drivers
#include "DRV_RCC.h"

//ANSI C
#include <stdint.h>

#define SYSTICK_LOAD_VALUE  8000
#define SYSTICK_CTRL_ENABLE     (1U << 0)
#define SYSTICK_CTRL_TICKINT    (1U << 1)
#define SYSTICK_CTRL_CLKSRC     (1U << 2)
#define SYSTICK_CTRL_COUNTFLAG  (1U << 16)
#define DRV_MAX_DELAY   0xFFFFFFFUL

void DRV_TIMEBASE_Init(void);

void DRV_TIMEBASE_IncTick(void);
uint32_t DRV_TIMEBASE_GetTick(void);

void Delay_ms(uint32_t delay);

#endif //INC_001_MAKEFILE_TEST_DRV_TIMEBASE_H
