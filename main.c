/***
 * Main Include
 ***/
#include "main.h"

/***
 * Prototype functions
 ***/
void SystemClock_Config(void);
void MX_GPIO_Config(void);
void MX_UART2_Config(void);
void MX_SPI1_Config(void);

#define BAUDRATE 115200
#define MSG_SIZE 512

/***
 * Local Variables
 ***/
uint8_t MSG[MSG_SIZE] = {0};
uint32_t MsgSize = 0;

// Main function
int main(void)
{
    SystemClock_Config();
    MX_GPIO_Config();
    MX_UART2_Config();

    while(1)
    {
        DRV_GPIO_TogglePin(&PB3);
        Delay_ms(500);
    }

    //Return
    return 0;
}

void MX_GPIO_Config(void)
{
    /** Local Variables **/
    GPIO_Config_t USART2_TX = {0};
    GPIO_Config_t USART2_RX = {0};
    GPIO_Config_t LD1 = {0};

    /** Init required GPIOx clock **/
    _DRV_RCC_GPIOA_CLK_Enable();
    _DRV_RCC_GPIOB_CLK_Enable();
    _DRV_RCC_GPIOC_CLK_Enable();

    /** Configure UART PA2 and PA3 GPIOs **/
    /** PA2 **/
    USART2_TX.Mode   = GPIO_MODE_ALT_FCN_PP;
    USART2_TX.Speed  = GPIO_SPEED_HIGH;
    USART2_TX.Pull   = GPIO_PULL_NO;
    USART2_TX.AltFun = GPIO_ALT_FCN_AF7_USART2;

    /** PA15 **/
    USART2_RX.Mode   = GPIO_MODE_ALT_FCN_PP;
    USART2_RX.Speed  = GPIO_SPEED_HIGH;
    USART2_RX.Pull   = GPIO_PULL_NO;
    USART2_RX.AltFun = GPIO_ALT_FCN_AF7_USART2;

    /** Init USART2 GPIO PIns **/
    DRV_GPIO_Init(&PA2, &USART2_TX);
    DRV_GPIO_Init(&PA15, &USART2_RX);

    /** PB3 as output **/
    LD1.Mode = GPIO_MODE_OUTPUT_PP;
    LD1.Pull = GPIO_PULL_NO;
    LD1.Speed = GPIO_SPEED_MEDIUM;

    /** Init LD1 (PB3) **/
    DRV_GPIO_Init(&PB3, &LD1);

    DRV_GPIO_WritePin(&PB3, GPIO_PIN_RESET);
}

void MX_UART2_Config(void)
{
    /** Enable USART2 Clock **/
    _DRV_RCC_USART2_CLK_Enable();

    /** Disable USART2 **/
    USART2->CR1 &= ~(1 << 0);

    /** Configure baudrate **/
    USART2->BRR = (HSI_CLOCK_SPEED/BAUDRATE);

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

void SystemClock_Config(void)
{
    /** Init systick timer **/
    DRV_TIMEBASE_Init();

}


