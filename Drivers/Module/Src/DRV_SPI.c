//
// Created by resca on 05/03/2023.
//

/****************************************************************
 *                                                              *
 *                     Required Includes                        *
 *                                                              *
 ****************************************************************/

//Module
#include "DRV_SPI.h"

/****************************************************************
 *                                                              *
 *                     Required Includes                        *
 *                                                              *
 ****************************************************************/
void DRV_SPI_Init(SPI_HandleTypeDef *hspi) {

    /** First lets configure SPI_CR1 register **/
    CLEAR_BIT(hspi->Instance->CR1, SPI_CR1_SPE);

    /** 1.- Configure the device mode **/
    switch (hspi->Init.DeviceMode) {
        case SPI_DEVICE_MODE_SLAVE:
            hspi->Instance->CR1 &= ~SPI_CR1_MSTR;
            break;

        case SPI_DEVICE_MODE_MASTER:
            hspi->Instance->CR1 |= SPI_CR1_MSTR;
            break;

        default:
            return;
    }

    /** 2.- Configure the bus config **/
    switch (hspi->Init.BusConfig) {
        case SPI_BUS_CONFIG_FULL_DUPLEX:
            hspi->Instance->CR1 &= ~SPI_CR1_BIDIMODE;
            break;

        case SPI_BUS_CONFIG_HALF_DUPLEX:
            hspi->Instance->CR1 |= SPI_CR1_BIDIMODE;
            break;

        case SPI_BUS_CONFIG_TX_ONLY:
            break;

        case SPI_BUS_CONFIG_RX_ONLY:
            hspi->Instance->CR1 &= ~SPI_CR1_BIDIMODE;
            hspi->Instance->CR1 |= SPI_CR1_RXONLY;
            break;

        default:
            return;
    }

    /** 3.- Configure the clock speed **/
    switch (hspi->Init.SclkSpeed) {
        case SPI_SPEED_DIV_2:
            hspi->Instance->CR1 |= (SPI_SPEED_DIV_2 << 3);
            break;

        case SPI_SPEED_DIV_4:
            hspi->Instance->CR1 |= (SPI_SPEED_DIV_4 << 3);
            break;

        case SPI_SPEED_DIV_8:
            hspi->Instance->CR1 |= (SPI_SPEED_DIV_8 << 3);
            break;

        case SPI_SPEED_DIV_16:
            hspi->Instance->CR1 |= (SPI_SPEED_DIV_16 << 3);
            break;

        case SPI_SPEED_DIV_32:
            hspi->Instance->CR1 |= (SPI_SPEED_DIV_32 << 3);
            break;

        case SPI_SPEED_DIV_64:
            hspi->Instance->CR1 |= (SPI_SPEED_DIV_64 << 3);
            break;

        case SPI_SPEED_DIV_128:
            hspi->Instance->CR1 |= (SPI_SPEED_DIV_128 << 3);
            break;

        case SPI_SPEED_DIV_256:
            hspi->Instance->CR1 |= (SPI_SPEED_DIV_256 << 3);
            break;

        default:
            return;
    }

    /** 4.- Configure CPHA **/
    switch (hspi->Init.CPHA) {
        case SPI_CPHA_LOW:
            hspi->Instance->CR1 &= ~SPI_CR1_CPHA;
            break;

        case SPI_CPHA_HIGH:
            hspi->Instance->CR1 |= SPI_CR1_CPHA;
            break;

        default:
            break;
    }

    /** 5.- Configure CPOL **/
    switch (hspi->Init.CPOL) {
        case SPI_CPOL_LOW:
            hspi->Instance->CR1 &= ~SPI_CR1_CPOL;
            break;

        case SPI_CPOL_HIGH:
            hspi->Instance->CR1 |= SPI_CR1_CPOL;
            break;

        default:
            return;
    }

    /** 6.- Configure SSM **/
    switch (hspi->Init.SSM) {
        case SPI_SSM_DISABLE:
            hspi->Instance->CR1 &= ~SPI_CR1_SSM;
            break;

        case SPI_SSM_ENABLE:
            hspi->Instance->CR1 |= SPI_CR1_SSM;
            break;

        default:
            return;
    }

    /** 7.- Configure Data Size **/
    switch (hspi->Init.DataSize)
    {
        case SPI_DATA_SIZE_4BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_4BIT << 8);
            break;

        case SPI_DATA_SIZE_5BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_5BIT << 8);
            break;

        case SPI_DATA_SIZE_6BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_6BIT << 8);
            break;

        case SPI_DATA_SIZE_7BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_7BIT << 8);
            break;

        case SPI_DATA_SIZE_8BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_8BIT << 8);
            break;

        case SPI_DATA_SIZE_9BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_9BIT << 8);
            break;

        case SPI_DATA_SIZE_10BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_10BIT << 8);
            break;

        case SPI_DATA_SIZE_11BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_11BIT << 8);
            break;

        case SPI_DATA_SIZE_12BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_12BIT << 8);
            break;

        case SPI_DATA_SIZE_13BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_13BIT << 8);
            break;

        case SPI_DATA_SIZE_14BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_14BIT << 8);
            break;

        case SPI_DATA_SIZE_15BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_15BIT << 8);
            break;

        case SPI_DATA_SIZE_16BIT:
            hspi->Instance->CR2 |= (SPI_DATA_SIZE_16BIT << 8);
            break;

        default:
            return;
    }

}

void DRV_SPI_DeInit(SPI_HandleTypeDef *hspi)
{
    /** Disable SPI Module **/
    hspi->Instance->CR1 &= ~SPI_CR1_SPE;

    /** Clear CR1 and CR2 registers **/
    hspi->Instance->CR1 = 0x0000;
    hspi->Instance->CR2 = 0x0700;

}

void DRV_SPI_Transmit(SPI_TypeDef *SPIx, uint8_t *pData, uint32_t size)
{
    while(size != 0)
    {
        //Wait until TXE is set
        if( __SPI_GET_FLAG(SPIx,SPI_FLAG_TXE) ) {

            //Set data to DR Register (TODO: Prototype, only for 8bit, in future 16bit will be implemented).
            SPIx->DR = *(pData);

            //Increment pointer and decrement size
            pData++;
            size--;
        }
    }
}

void DRV_SPI_Receive(SPI_TypeDef *SPIx, uint8_t *pData, uint32_t size)
{
    while(size != 0)
    {
        //Wait until TXE is set
        if( __SPI_GET_FLAG(SPIx,SPI_FLAG_RXNE) ) {

            //2.- Set data to DR Register (TODO: Prototype, only for 8bit, in future 16bit will be implemented).
            *(pData) = SPIx->DR;

            //Increment pointer and decrement size
            pData++;
            size--;
        }
    }

    //Clear Overun flag
    __SPI_CLEAR_OVRFLAG(SPIx);

}

void DRV_SPI_ISRHandler(SPI_HandleTypeDef *hspi)
{

}
