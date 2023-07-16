//
// Created by resca on 7/13/2023.
//

#ifndef INTERNALFLASHDRIVER_BOOT_FLASH_H
#define INTERNALFLASHDRIVER_BOOT_FLASH_H

/***************************************************************************
 *
 * Required Includes
 *
 ***************************************************************************/

//BOOT Header
#include "BOOT.h"

/***************************************************************************
 *
 * Typedef enum
 *
 ***************************************************************************/

typedef enum
{
    BOOT_FLASH_PROC_NONE = 0,
    BOOT_FLASH_PROC_PAGEERASE,
    BOOT_FLASH_PROC_MASSERASE,
    BOOT_FLASH_PROC_PROGRAMHALFWORD,
    BOOT_FLASH_PROC_PROGRAMWORD,
    BOOT_FLASH_PROC_PROGRAMDOUBLEWORD

}boot_flash_procedure_t;

typedef enum
{
    BOOT_FLASH_TYPEPROGRAM_HALFWORD = 1,  //Program a half-word (16-bit) at a specified address.
    BOOT_FLASH_TYPEPROGRAM_WORD,          //Program a word (32-bit) at a specified address.
    BOOT_FLASH_TYPEPROGRAM_DOUBLEWORD     //Program a double word (64-bit) at a specified address

}boot_flash_program_type;

typedef enum
{
    FLASH_TYPEERASE_PAGES = 0,    // Pages erase only
    FLASH_TYPEERASE_MASSERASE     // Flash mass erase activation

}boot_flash_erase_type;

/***************************************************************************
 *
 * Typedef structure
 *
 ***************************************************************************/

typedef struct
{
    __IO boot_flash_procedure_t ProcedureOnGoing; //Internal variable to indicate which procedure is ongoing or not in IT context
    __IO uint32_t               DataRemaining;    //Internal variable to save the remaining pages to erase or half-word to program in IT context
    __IO uint32_t               Address;          //Internal variable to save address selected for program or erase
    __IO uint64_t               Data;             //Internal variable to save data to be programmed
    boot_lock_status_t          Lock;             //FLASH locking object
    __IO uint32_t               ErrorCode;        //FLASH error code

} boot_flash_process_t;

typedef struct
{
    boot_flash_erase_type   TypeErase;   //TypeErase: Mass erase or page erase.
    uint32_t                PageAddress; //PageAdress: Initial FLASH page address to erase when mass erase is disabled
    uint32_t                NbPages;     //NbPages: Number of pagess to be erased.

} boot_erase_init_t;

/***************************************************************************
 *
 * Defines
 *
 ***************************************************************************/

#define FLASH_PAGE_0    (0x08000000UL)
#define FLASH_PAGE_255  (0x0807F800UL)

#define FLASH_PAGE_SIZE 0x800

#define EMPTY_MEM_VALUE (0xFFFFFFFFUL)

/***************************************************************************
 *
 * Prototype Public Functions
 *
 ***************************************************************************/

boot_status_t BOOT_FLASH_Write(uint32_t Address, uint32_t *pData, uint16_t Size);
boot_status_t BOOT_FLASH_Write16Bit(uint32_t Address, uint16_t *pData, uint16_t Size);

boot_status_t BOOT_FLASH_Read(uint32_t Address, uint32_t *pData, uint16_t Size);
boot_status_t BOOT_Flash_Read16Bit(uint32_t Address, uint16_t *pData, uint16_t Size);

boot_status_t BOOT_FLASH_Erase(boot_erase_init_t *pEraseInit, uint32_t *PageError);
boot_status_t BOOT_FLASH_ErasePage(uint32_t PageAddress, uint16_t NumberOfPages, uint32_t *PageError);

#endif //INTERNALFLASHDRIVER_BOOT_FLASH_H
