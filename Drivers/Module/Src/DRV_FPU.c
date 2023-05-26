//
// Created by resca on 18/02/2023.
//

/***
 * Required Includes
 ***/
#include "DRV_FPU.h"

/***
 * Public Functions
 ***/

void DRV_FPU_Enable(void)
{
    /** Enable floating point unit: Enable CP10 and CP11 full access **/
    SCB->CPACR |= (1 << 20);
    SCB->CPACR |= (1 << 21);
    SCB->CPACR |= (1 << 22);
    SCB->CPACR |= (1 << 23);
}