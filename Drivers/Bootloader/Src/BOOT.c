//
// Created by resca on 27/05/2023.
//

/***************************************************************************
 *
 * Required Includes
 *
 ***************************************************************************/

//ANSI C
#include <stdlib.h>

//Boot loader
#include "BOOT.h"

/***************************************************************************
 *
 * Local Variables
 *
 ***************************************************************************/

static volatile uint32_t TickValue = 0;

/***************************************************************************
 *
 * Public Functions
 *
 ***************************************************************************/

void BOOT_Init(void)
{
    //Init SysTick Timer
    /** Disable Interrupts **/
    __disable_irq();

    /** Configure Systyck **/
    SysTick->LOAD = BOOT_SYSTICK_LOAD_VALUE;

    /** Clear systick current value register **/
    SysTick->VAL = 0;

    /** Enable systick and select internal clk src **/
    SysTick->CTRL = BOOT_SYSTICK_CTRL_CLKSRC;

    /** Enable interrupt and enable Systick **/
    SysTick->CTRL |= BOOT_SYSTICK_CTRL_TICKINT;
    SysTick->CTRL |= BOOT_SYSTICK_CTRL_ENABLE;

    /** Enable global interrupts **/
    __enable_irq();

}

void BOOT_IntTick(void)
{
    TickValue++;
}

uint32_t BOOT_GetTick(void)
{
    return TickValue;
}

void Delay_ms(uint32_t delay)
{
    /** Local variables **/
    uint32_t TickStart = TickValue;

    while( (TickValue - TickStart) < delay )
    {

    }
}