/***
 * Main Include
 ***/
#include "main.h"

/***
 * Prototype functions
 ***/
void Boot_Config(void);

#define BAUDRATE 115200
#define MSG_SIZE 512

#define EMPTY_MEM_VALUE 0xFFFFFFFF

//Flash Memory
#define FLASH_START_ADDR    0x8000000
#define FLASH_APP_OFFSET    0x3000
#define FLASH_APP_ADDR      (FLASH_START_ADDR + FLASH_APP_OFFSET)

typedef void(*func_ptr)(void);

/***
 * Local Variables
 ***/
uint8_t MSG[MSG_SIZE] = {0};
uint32_t MsgSize = 0;

/***
 * Prototype Function
 ***/
 void StartApp(void);

// Main function
int main(void)
{
    /** Configure Bootloader module **/
    Boot_Config();

    /** Transmit initial message **/
    BOOT_UART_Print(USART2, "Bootloader started\r\n");
    Delay_ms(300);

    /** Start App **/
    StartApp();

    while(1)
    {
        //DRV_GPIO_TogglePin(&PB3);
        BOOT_TogglePin(&PB3);
        Delay_ms(500);
    }

    //Return
    return 0;
}

void StartApp(void)
{
    //Local Variables
    uint32_t AppStartAddress, MemVerificationData;
    func_ptr AppMain;

    MemVerificationData = *((uint32_t *)FLASH_APP_ADDR);

    /** Check if there is data **/
    if( MemVerificationData != EMPTY_MEM_VALUE)
    {
        BOOT_UART_Print(USART2, "Starting Application\r\n");

        AppStartAddress = (*(uint32_t *) (FLASH_APP_ADDR + 4));

        AppMain = (func_ptr)AppStartAddress;

        /** Init Main Stack Pointer **/
        __set_MSP(*(uint32_t *) FLASH_APP_ADDR);

        /** Jump **/
        AppMain();
    }
    else
    {
        BOOT_UART_Print(USART2, "No Application data found.\r\n");
        BOOT_UART_Print(USART2, "Please verify data and reset MCU.\r\n");
    }
}

void Boot_Config(void)
{
    //Configure Required Peripheral Clock
    _BOOT_RCC_GPIOA_CLK_Enable();
    _BOOT_RCC_GPIOB_CLK_Enable();
    _BOOT_RCC_GPIOC_CLK_Enable();
    _BOOT_RCC_USART2_CLK_Enable();

    /** Init Bootloader Module **/
    BOOT_Init();

    /** Configure required MCU Modules **/

    //GPIO
    BOOT_InitOutputPin(&PB3, BOOT_GPIO_SET);

    //UART
    BOOT_USART_TXPortConfig(&PA2, BOOT_GPIO_ALT_FN_7);
    BOOT_USART_RXPortConfig(&PA15, BOOT_GPIO_ALT_FN_7);
    BOOT_USART_Init(USART2, BAUDRATE);

}
