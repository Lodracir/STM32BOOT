//
// Created by resca on 19/02/2023.
//

/***
 * Required Includes
 ***/
#include "DRV_UART.h"

/***
 * Local typedef struct
 ***/

typedef struct
{
    bool Init;
    bool inUse;

    uint32_t Baudrate;

} uart_driver_t;

/***
 * Prototype Public Functions
 ***/

void DRV_UART_Transmit(USART_TypeDef *USARTx, uint8_t *pData, uint32_t Size)
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

void DRV_UART_Receive(USART_TypeDef *USARTx, uint8_t *pData, uint32_t Size)
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

void DRV_UART_Print(USART_TypeDef *USARTx, char *pChar)
{
    while( (*pChar) != '\0' )
    {
        DRV_UART_Transmit(USARTx, (uint8_t *)pChar, 1);
        pChar++;
    }
}