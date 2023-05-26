//
// Created by resca on 19/02/2023.
//

/***
 * Required Includes
 ***/
#include "stm32f3xx_it.h"

/***
 *  Public Functions
 ***/

void NMI_Handler(void)
{

}

void HardFault_Handler(void)
{
    //Disable all interrupts
    __disable_irq();

    while(1)
    {

    }
}

void SVC_Handler(void)
{

}

void PendSV_Handler(void)
{

}

/** SysTick Timer **/
void SysTick_Handler(void)
{
    DRV_TIMEBASE_IncTick();
}