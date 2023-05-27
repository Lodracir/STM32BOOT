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
 * Public Functions
 *
 ***************************************************************************/

/***************************************************************************
 *
 * Public Functions
 *
 ***************************************************************************/

void BOOT_InitOutputPin(Port_t *Port, boot_gpio_state_t DefaultState)
{
    if(Port == NULL)
    {
        return;
    }

    //Configure Output Mode
    Port->Port->MODER |= (1U << (Port->Pin * 2));
    Port->Port->MODER &= ~(1U << ((Port->Pin * 2) + 1));
    Port->Port->OTYPER &= ~(1U << Port->Pin);

    //Configure Speed (Low Speed)
    Port->Port->OSPEEDR &= ~(1U << (Port->Pin * 2));
    Port->Port->OSPEEDR &= ~(1U << ((Port->Pin * 2) + 1));

    //Configure Pull (No Pull)
    Port->Port->PUPDR &= ~(1U << (Port->Pin * 2));
    Port->Port->PUPDR &= ~((Port->Pin * 2) + 1);

    //Set Default Pin state
    BOOT_WritePin(Port, DefaultState);

}

void BOOT_WritePin(Port_t *Port, boot_gpio_state_t state)
{
    switch (state)
    {
        case BOOT_GPIO_SET:
            Port->Port->BSRR |= (1U << Port->Pin);
            break;

        case BOOT_GPIO_RESET:
            Port->Port->BRR |= (1U << Port->Pin);
            break;

        default:
            break;
    }
}

void BOOT_TogglePin(Port_t *Port)
{
    Port->Port->ODR ^= (1U << Port->Pin);
}

