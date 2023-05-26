//
// Created by resca on 19/02/2023.
//

/***
 * Required Includes
 ***/
#include "DRV_GPIO.h"

/***
 * Prototype Functions
 ***/

void DRV_GPIO_Init(Port_t *Port, GPIO_Config_t *Config)
{
    /** Configure GPIOx mode **/
    switch (Config->Mode)
    {
        case GPIO_MODE_INPUT:
            Port->Port->MODER &= ~(1U << (Port->Pin * 2));
            Port->Port->MODER &= ~(1U << ((Port->Pin * 2) + 1));
            break;

        case GPIO_MODE_OUTPUT_PP:
            Port->Port->MODER |= (1U << (Port->Pin * 2));
            Port->Port->MODER &= ~(1U << ((Port->Pin * 2) + 1));
            Port->Port->OTYPER &= ~(1U << Port->Pin);
            break;

        case GPIO_MODE_OUTPUT_OD:
            Port->Port->MODER |= (1U << (Port->Pin * 2));
            Port->Port->MODER &= ~(1U << ((Port->Pin * 2) + 1));
            Port->Port->OTYPER |= (1U << Port->Pin);
            break;

        case GPIO_MODE_ALT_FCN_PP:
            Port->Port->MODER &= ~(1U << (Port->Pin * 2));
            Port->Port->MODER |= (1U << ((Port->Pin * 2) + 1));
            Port->Port->OTYPER &= ~(1U << Port->Pin);
            break;

        case GPIO_MODE_ALT_FCN_OD:
            Port->Port->MODER &= ~(1U << (Port->Pin * 2));
            Port->Port->MODER |= (1U << ((Port->Pin * 2) + 1));
            Port->Port->OTYPER |= (1U << Port->Pin);
            break;

        case GPIO_MODE_ANALOG:
            Port->Port->MODER |= (1U << (Port->Pin * 2));
            Port->Port->MODER |= (1U << ((Port->Pin * 2) + 1));
            break;

        default:
            return;
            break;
    }

    /** Configure GPIOX Speed **/
    switch (Config->Speed)
    {
        case GPIO_SPEED_LOW:
            Port->Port->OSPEEDR &= ~(1U << (Port->Pin * 2));
            Port->Port->OSPEEDR &= ~(1U << ((Port->Pin * 2) + 1));
            break;

        case GPIO_SPEED_MEDIUM:
            Port->Port->OSPEEDR |= (1U << (Port->Pin * 2));
            Port->Port->OSPEEDR &= ~(1U << ((Port->Pin * 2) + 1));
            break;

        case GPIO_SPEED_HIGH:
            Port->Port->OSPEEDR |= (1U << (Port->Pin * 2));
            Port->Port->OSPEEDR |= (1U << ((Port->Pin * 2) + 1));
            break;

        default:
            return;
            break;
    }

    /** Configure GPIOx pull **/
    switch (Config->Pull)
    {
        case GPIO_PULL_NO:
            Port->Port->PUPDR &= ~(1U << (Port->Pin * 2));
            Port->Port->PUPDR &= ~((Port->Pin * 2) + 1);
            break;

        case GPIO_PULL_UP:
            Port->Port->PUPDR &= ~(1U << (Port->Pin * 2));
            Port->Port->PUPDR &= ~((Port->Pin * 2) + 1);
            break;

        case GPIO_PULL_DOWN:
            Port->Port->PUPDR &= ~(1U << (Port->Pin * 2));
            Port->Port->PUPDR &= ~((Port->Pin * 2) + 1);
            break;

        default:
            return;
            break;
    }

    /** Configure GPIO Alternative function **/
    if(Port->Pin <= 7)
    {
        Port->Port->AFR[0] |= (Config->AltFun << (Port->Pin * 4) );
    }
    if(Port->Pin > 7)
    {
        Port->Port->AFR[1] |= (Config->AltFun << ( (Port->Pin - 8) * 4) );
    }

}

void DRV_GPIO_WritePin(Port_t *Port, gpio_state_t state)
{
    switch (state)
    {
        case GPIO_PIN_SET:
            Port->Port->BSRR |= (1U << Port->Pin);
            break;

        case GPIO_PIN_RESET:
            Port->Port->BRR |= (1U << Port->Pin);
            break;

        default:
            break;
    }
}

void DRV_GPIO_TogglePin(Port_t *Port)
{
    Port->Port->ODR ^= (1U << Port->Pin);
}

bool DRV_GPIO_ReadPin(Port_t *Port)
{
    /** Check IDR register **/
    if( Port->Port->IDR & (1U << Port->Pin))
    {
        return true;
    }

    return false;
}