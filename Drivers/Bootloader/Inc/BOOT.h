//
// Created by resca on 27/05/2023.
//

#ifndef INC_005_BOOTLOADER_BOOT_H
#define INC_005_BOOTLOADER_BOOT_H

/***************************************************************************
 *
 * Required Includes
 *
 ***************************************************************************/

//MCU
#include "MCU.h"

//Port
#include "Port.h"

/***************************************************************************
 *
 * Typedef Enumeration
 *
 ***************************************************************************/
typedef enum
{
    BOOT_GPIO_SET = 0,
    BOOT_GPIO_RESET

}boot_gpio_state_t;

typedef enum
{
    BOOT_GPIO_ALT_FN_0   = 0x00,
    BOOT_GPIO_ALT_FN_1,
    BOOT_GPIO_ALT_FN_2,
    BOOT_GPIO_ALT_FN_3,
    BOOT_GPIO_ALT_FN_4,
    BOOT_GPIO_ALT_FN_5,
    BOOT_GPIO_ALT_FN_6,
    BOOT_GPIO_ALT_FN_7,
    BOOT_GPIO_ALT_FN_8,
    BOOT_GPIO_ALT_FN_9,
    BOOT_GPIO_ALT_FN_10,
    BOOT_GPIO_ALT_FN_11,
    BOOT_GPIO_ALT_FN_12,
    BOOT_GPIO_ALT_FN_13,
    BOOT_GPIO_ALT_FN_14,
    BOOT_GPIO_ALT_FN_15

} boot_gpio_alt_fcn_t;

/***************************************************************************
 *
 * Defines
 *
 ***************************************************************************/

#define BOOT_SYSTICK_LOAD_VALUE      8000
#define BOOT_SYSTICK_CTRL_ENABLE     (1U << 0)
#define BOOT_SYSTICK_CTRL_TICKINT    (1U << 1)
#define BOOT_SYSTICK_CTRL_CLKSRC     (1U << 2)

#define BOOT_HSI_CLOCK_SPEED 8000000

#define _BOOT_RCC_AHBENR_IOPAEN  (1U << 17)
#define _BOOT_RCC_AHBENR_IOPBEN  (1U << 18)
#define _BOOT_RCC_AHBENR_IOPCEN  (1U << 19)
#define _BOOT_RCC_AHBENR_ADC12EN (1U << 28)

#define _BOOT_RCC_APB1ENR_USART2 (1 << 17)

#define _BOOT_RCC_APB2ENR_SPI1   (1 << 12)
#define _BOOT_RCC_APB1ENR_SPI2   (1 << 14)
#define _BOOT_RCC_APB1ENR_SPI3   (1 << 15)

/***************************************************************************
 *
 * MACROS
 *
 ***************************************************************************/

//GPIO Clock
#define _BOOT_RCC_GPIOA_CLK_Enable()     (RCC->AHBENR |= _BOOT_RCC_AHBENR_IOPAEN)
#define _BOOT_RCC_GPIOB_CLK_Enable()     (RCC->AHBENR |= _BOOT_RCC_AHBENR_IOPBEN)
#define _BOOT_RCC_GPIOC_CLK_Enable()     (RCC->AHBENR |= _BOOT_RCC_AHBENR_IOPCEN)
#define _BOOT_RCC_ADC12_CLK_Enable()     (RCC->AHBENR |= _BOOT_RCC_AHBENR_ADC12EN)

//USART Clock
#define _BOOT_RCC_USART2_CLK_Enable()    (RCC->APB1ENR |= _BOOT_RCC_APB1ENR_USART2)

/***************************************************************************
 *
 * Prototype Functions
 *
 ***************************************************************************/

/** Init and DeInit **/
void BOOT_Init(void);

void BOOT_IntTick(void);
uint32_t BOOT_GetTick(void);
void Delay_ms(uint32_t delay);

/** GPIO Output Functions **/
void BOOT_InitOutputPin(Port_t *Port, boot_gpio_state_t DefaultState);
void BOOT_WritePin(Port_t *Port, boot_gpio_state_t state);
void BOOT_TogglePin(Port_t *Port);

/** USART Functions **/
void BOOT_USART_TXPortConfig( Port_t *Port, boot_gpio_alt_fcn_t AltFun );
void BOOT_USART_RXPortConfig( Port_t *Port, boot_gpio_alt_fcn_t AltFun );
void BOOT_USART_Init(USART_TypeDef *USARTx, uint32_t Baudrate);

void BOOT_UART_Transmit(USART_TypeDef *USARTx, uint8_t *pData, uint32_t Size);
void BOOT_UART_Receive(USART_TypeDef *USARTx, uint8_t *pData, uint32_t Size);
void BOOT_UART_Print(USART_TypeDef *USARTx, char *pChar);

#endif //INC_005_BOOTLOADER_BOOT_H
