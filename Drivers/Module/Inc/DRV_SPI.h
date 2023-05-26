//
// Created by lodracir on 25/02/23.
//

#ifndef INC_001_MAKEFILE_TEST_DRV_SPI_H
#define INC_001_MAKEFILE_TEST_DRV_SPI_H

/****************************************************************
 *                                                              *
 *                     Required Includes                        *
 *                                                              *
 ****************************************************************/

//MCU
#include "MCU.h"

//ANSI C
#include <stdint.h>
#include <stdbool.h>

/****************************************************************
*                                                               *
*                      Typedef Enumeration                      *
*                                                               *
*****************************************************************/

typedef enum
{
    SPI_ERROR_OK = 0x00,
    SPI_ERROR_INIT,
    SPI_ERROR_BUSY,
    SPI_ERROR_TIMEOUT

} spi_error_t;

typedef enum
{
    SPI_STATE_RESET = 0x00,
    SPI_STATE_READY = 0x01,
    SPI_STATE_BUSY  = 0x02,
    SPI_STATE_BUSY_TX = 0x03,
    SPI_STATE_BUSY_RX = 0x04

} spi_state_t;

typedef enum
{
    SPI_DEVICE_MODE_SLAVE   = 0,
    SPI_DEVICE_MODE_MASTER  = 1
}spi_mode_t;

typedef enum
{
    SPI_BUS_CONFIG_FULL_DUPLEX,
    SPI_BUS_CONFIG_HALF_DUPLEX,
    SPI_BUS_CONFIG_TX_ONLY,
    SPI_BUS_CONFIG_RX_ONLY
}spi_bus_t;

typedef enum
{
    SPI_SPEED_DIV_2     = 0,
    SPI_SPEED_DIV_4     = 1,
    SPI_SPEED_DIV_8     = 2,
    SPI_SPEED_DIV_16    = 3,
    SPI_SPEED_DIV_32    = 4,
    SPI_SPEED_DIV_64    = 5,
    SPI_SPEED_DIV_128   = 6,
    SPI_SPEED_DIV_256   = 7

}spi_speed_t;

typedef enum
{
    SPI_DATA_SIZE_4BIT      = 3,
    SPI_DATA_SIZE_5BIT      = 4,
    SPI_DATA_SIZE_6BIT      = 5,
    SPI_DATA_SIZE_7BIT      = 6,
    SPI_DATA_SIZE_8BIT      = 7,
    SPI_DATA_SIZE_9BIT      = 8,
    SPI_DATA_SIZE_10BIT     = 9,
    SPI_DATA_SIZE_11BIT     = 10,
    SPI_DATA_SIZE_12BIT     = 11,
    SPI_DATA_SIZE_13BIT     = 12,
    SPI_DATA_SIZE_14BIT     = 13,
    SPI_DATA_SIZE_15BIT     = 14,
    SPI_DATA_SIZE_16BIT     = 15,

}spi_data_size_t;

typedef enum
{
    SPI_CPOL_LOW    = 0,
    SPI_CPOL_HIGH   = 1

}spi_cpol_t;

typedef enum
{
    SPI_CPHA_LOW    = 0,
    SPI_CPHA_HIGH   = 1

}spi_cpha_t;

typedef enum
{
    SPI_SSM_DISABLE = 0,
    SPI_SSM_ENABLE  = 1
}spi_ssm_t;

/** @defgroup SPI_Flags_definition SPI Flags Definition
  * @{
  */
#define SPI_FLAG_RXNE                   SPI_SR_RXNE   /* SPI status flag: Rx buffer not empty flag       */
#define SPI_FLAG_TXE                    SPI_SR_TXE    /* SPI status flag: Tx buffer empty flag           */
#define SPI_FLAG_BSY                    SPI_SR_BSY    /* SPI status flag: Busy flag                      */
#define SPI_FLAG_CRCERR                 SPI_SR_CRCERR /* SPI Error flag: CRC error flag                  */
#define SPI_FLAG_MODF                   SPI_SR_MODF   /* SPI Error flag: Mode fault flag                 */
#define SPI_FLAG_OVR                    SPI_SR_OVR    /* SPI Error flag: Overrun flag                    */
#define SPI_FLAG_FRE                    SPI_SR_FRE    /* SPI Error flag: TI mode frame format error flag */
#define SPI_FLAG_FTLVL                  SPI_SR_FTLVL  /* SPI fifo transmission level                     */
#define SPI_FLAG_FRLVL                  SPI_SR_FRLVL  /* SPI fifo reception level                        */
#define SPI_FLAG_MASK                   (SPI_SR_RXNE | SPI_SR_TXE | SPI_SR_BSY | SPI_SR_CRCERR\
                                         | SPI_SR_MODF | SPI_SR_OVR | SPI_SR_FRE | SPI_SR_FTLVL | SPI_SR_FRLVL)

#define __SPI_GET_FLAG(__INSTANCE__, __FLAG__) ((((__INSTANCE__)->SR) & (__FLAG__)) == (__FLAG__))

/** @brief  Clear the SPI OVR pending flag.
  * @param  __HANDLE__ specifies the SPI Handle.
  *         This parameter can be SPI where x: 1, 2, or 3 to select the SPI peripheral.
  * @retval None
  */
#define __SPI_CLEAR_OVRFLAG(__INSTANCE__)           \
  do{                                               \
    __IO uint32_t tmpreg_ovr = 0x00U;               \
    tmpreg_ovr = (__INSTANCE__)->DR;                \
    tmpreg_ovr = (__INSTANCE__)->SR;                \
    UNUSED(tmpreg_ovr);                             \
  } while(0U)

/****************************************************************
*                                                               *
*                       Typedef Structure                       *
*                                                               *
*****************************************************************/

typedef struct
{
    spi_mode_t          DeviceMode;
    spi_bus_t           BusConfig;
    spi_speed_t         SclkSpeed;
    spi_data_size_t     DataSize;
    spi_cpol_t          CPOL;
    spi_cpha_t          CPHA;
    spi_ssm_t           SSM;

} SPI_Config_t;

typedef struct
{
    SPI_TypeDef     *Instance;
    SPI_Config_t    Init;
    uint8_t         *pTxBuffPtr;
    uint16_t        TxXferSize;
    __IO uint16_t   TxXferCount;
    uint8_t         *pRxBuffPtr;
    uint16_t        RxXferSize;
    __IO uint16_t   RxXferCount;
    spi_state_t     State;
    __IO uint32_t   ErrorCode;

} SPI_HandleTypeDef;

/****************************************************************
*                                                               *
*                             Defines                           *
*                                                               *
*****************************************************************/

/********************************************************************
 * Prototype Functions
 ********************************************************************/

void DRV_SPI_Init(SPI_HandleTypeDef *hspi);
void DRV_SPI_DeInit(SPI_HandleTypeDef *hspi);

void DRV_SPI_Transmit(SPI_TypeDef *SPIx, uint8_t *pData, uint32_t size);
void DRV_SPI_Receive(SPI_TypeDef *SPIx, uint8_t *pData, uint32_t size);

void DRV_SPI_ISRHandler(SPI_HandleTypeDef *hspi);

#endif //INC_001_MAKEFILE_TEST_DRV_SPI_H
