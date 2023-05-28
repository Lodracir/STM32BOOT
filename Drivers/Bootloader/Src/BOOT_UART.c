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

void BOOT_USART_TXPortConfig( Port_t *Port, boot_gpio_alt_fcn_t AltFun )
{
    //Config Mode Type (Alternate Function)
    Port->Port->MODER &= ~(1U << (Port->Pin * 2));
    Port->Port->MODER |= (1U << ((Port->Pin * 2) + 1));

    //Configure Ouput Type (Pull Push)
    Port->Port->OTYPER &= ~(1U << Port->Pin);

    //Configure Speed (HIGH SPEED)
    Port->Port->OSPEEDR |= (1U << (Port->Pin * 2));
    Port->Port->OSPEEDR |= (1U << ((Port->Pin * 2) + 1));

    //Configure Pull (NO PULL)
    Port->Port->PUPDR &= ~(1U << (Port->Pin * 2));
    Port->Port->PUPDR &= ~((Port->Pin * 2) + 1);

    //Configure Alternative Function
    if(Port->Pin <= 7)
    {
        Port->Port->AFR[0] |= (AltFun << (Port->Pin * 4) );
    }
    if(Port->Pin > 7) {
        Port->Port->AFR[1] |= (AltFun << ((Port->Pin - 8) * 4));
    }
}

void BOOT_USART_RXPortConfig( Port_t *Port, boot_gpio_alt_fcn_t AltFun )
{
    //Config Mode Type (Alternate Function)
    Port->Port->MODER &= ~(1U << (Port->Pin * 2));
    Port->Port->MODER |= (1U << ((Port->Pin * 2) + 1));

    //Configure Ouput Type (Pull Push)
    Port->Port->OTYPER &= ~(1U << Port->Pin);

    //Configure Speed (HIGH SPEED)
    Port->Port->OSPEEDR |= (1U << (Port->Pin * 2));
    Port->Port->OSPEEDR |= (1U << ((Port->Pin * 2) + 1));

    //Configure Pull (NO PULL)
    Port->Port->PUPDR &= ~(1U << (Port->Pin * 2));
    Port->Port->PUPDR &= ~((Port->Pin * 2) + 1);

    //Configure Alternative Function
    if(Port->Pin <= 7)
    {
        Port->Port->AFR[0] |= (AltFun << (Port->Pin * 4) );
    }
    if(Port->Pin > 7) {
        Port->Port->AFR[1] |= (AltFun << ((Port->Pin - 8) * 4));
    }
}

void BOOT_USART_Init(USART_TypeDef *USARTx, uint32_t Baudrate)
{
    /** Disable USART2 **/
    USART2->CR1 &= ~(1 << 0);

    /** Configure baudrate **/
    USART2->BRR = (BOOT_HSI_CLOCK_SPEED/Baudrate);

    /** Enable TX and RX **/
    USART2->CR1 |= (1 << 2);
    USART2->CR1 |= (1 << 3);

    /** USART2 CR1 Configuration **/
    USART2->CR1 &= ~(1 << 15); //Oversampling by 16
    USART2->CR1 &= ~(1 << 10); //Disable Parity
    USART2->CR1 &= ~(1 << 28); //8-bit wordlength
    USART2->CR1 &= ~(1 << 12); //8-bit wordlenght

    /** USART2 CR2 Configuration **/
    USART2->CR2 &= ~(1 << 12); //Stop bits 1
    USART2->CR2 &= ~(1 << 13); //Stop bits 1

    /** Enable USART2 **/
    USART2->CR1 |= (1 << 0);
}

void BOOT_UART_DeInit(USART_TypeDef *UARTx)
{
    /** Disable USART2 **/
    USART2->CR1 &= ~(1 << 0);
}

void BOOT_UART_Transmit(USART_TypeDef *USARTx, uint8_t *pData, uint32_t Size)
{
    while( Size != 0 )
    {
        /** Wait until TX is empty **/
        while( !(USARTx->ISR & (1 << 7)) );

        /** Transfer data **/
        USARTx->TDR = ( (*pData) & 0xFF );

        /** Set next location and decrease size **/
        pData++;
        Size--;
    }
}

void BOOT_UART_Receive(USART_TypeDef *USARTx, uint8_t *pData, uint32_t Size)
{
    while( Size != 0 )
    {
        /** Wait until RX is empty **/
        while ( !(USARTx->ISR & (1 << 5)) );

        /** Store received data **/
        (*pData) = USARTx->RDR;

        /** Set next location and decrease size **/
        pData++;
        Size--;
    }
}

void BOOT_UART_Print(USART_TypeDef *USARTx, char *pChar)
{
    while( (*pChar) != '\0' )
    {
        BOOT_UART_Transmit(USARTx, (uint8_t *)pChar, 1);
        pChar++;
    }
}