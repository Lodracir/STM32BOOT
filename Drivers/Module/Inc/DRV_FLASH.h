//
// Created by resca on 18/02/2023.
//

#ifndef _DRV_FLASH_H_
#define _DRV_FLASH_H_

/***
 * Required Includes
 ***/

//MCU Include
#include "stm32f3xx.h"

/***
 * Defines
 ***/

#define FLASH_VOLTAGE_RANGE_1   0x00U
#define FLASH_VOLTAGE_RANGE_2   0x01U
#define FLASH_VOLTAGE_RANGE_3   0x02U
#define FLASH_VOLTAGE_RANGE_4   0x03U

/***
 * Typedef enumerations
 ***/

typedef enum
{
    FLASH_PAGE_0 = 0x00,
    FLASH_PAGE_1,
    FLASH_PAGE_2,
    FLASH_PAGE_3,
    FLASH_PAGE_4,
    FLASH_PAGE_5,
    FLASH_PAGE_6,
    FLASH_PAGE_7,
    FLASH_PAGE_8,
    FLASH_PAGE_9,
    FLASH_PAGE_10,
    FLASH_PAGE_11,
    FLASH_PAGE_12,
    FLASH_PAGE_13,
    FLASH_PAGE_14,
    FLASH_PAGE_15,
    FLASH_PAGE_16,
    FLASH_PAGE_17,
    FLASH_PAGE_18,
    FLASH_PAGE_19,
    FLASH_PAGE_20,
    FLASH_PAGE_21,
    FLASH_PAGE_22,
    FLASH_PAGE_23,
    FLASH_PAGE_24,
    FLASH_PAGE_25,
    FLASH_PAGE_26,
    FLASH_PAGE_27,
    FLASH_PAGE_28,
    FLASH_PAGE_29,
    FLASH_PAGE_30,
    FLASH_PAGE_31,

    FLASH_PAGE_TOTAL
} flash_page_t;

typedef enum
{
    FLASH_PROC_NONE = 0,
    FLASH_PROC_SECTERASE,
    FLASH_PROC_MASSERASE,
    FLASH_PROC_PROGRAM
} _flash_procedure_t;

typedef enum
{
    DEV_UNLOCKED = 0x00,
    DEV_LOCKED = 0x01

} _dev_locktype_t;

/***
 * Typedef structure
 ***/

typedef struct
{
    /** Internal variable to indicate currently running procedure **/
    __IO _flash_procedure_t OngoingProcedure;

    /** Internal variable to save number of sectors to erase **/
    __IO uint32_t NbSectorsToErase;
    __IO uint32_t Sector;
    __IO uint32_t Address;
    __IO _dev_locktype_t Lock;
    __IO uint32_t ErrorCode;

} _flash_process_t;

typedef struct
{
    uint32_t TypeErase;
    uint32_t Sector;
    uint32_t NbSectors;
    uint32_t VoltageRange;

} _flash_eraseInit_t;

void DRV_FLASH_ErasePage(flash_page_t Page);

#endif // _DRV_FLASH_H_
