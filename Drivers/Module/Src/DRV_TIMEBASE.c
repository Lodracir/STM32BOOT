//
// Created by lodracir on 24/02/23.
//

/***
 * Required Includes
 ***/
#include "DRV_TIMEBASE.h"

/***
 * Local Variables
 ***/
static volatile uint32_t TickValue = 0;

/***
 * Prototype Functions
 ***/

void DRV_TIMEBASE_Init(void)
{
    /** Disable Interrupts **/
    __disable_irq();

    /** Configure Systyck **/
    SysTick->LOAD = SYSTICK_LOAD_VALUE;

    /** Clear systick current value register **/
    SysTick->VAL = 0;

    /** Enable systick and select internal clk src **/
    SysTick->CTRL = SYSTICK_CTRL_CLKSRC;

    /** Enable interrupt and enable Systick **/
    SysTick->CTRL |= SYSTICK_CTRL_TICKINT;
    SysTick->CTRL |= SYSTICK_CTRL_ENABLE;

    /** Enable global interrupts **/
    __enable_irq();
}

void DRV_TIMEBASE_IncTick(void)
{
    TickValue++;
}

uint32_t DRV_TIMEBASE_GetTick(void)
{
    return TickValue;
}

void Delay_ms(uint32_t delay)
{
    /** Local variables **/
    uint32_t TickStart = DRV_TIMEBASE_GetTick();

    while( (DRV_TIMEBASE_GetTick() - TickStart) < delay );
}