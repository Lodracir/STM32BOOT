//
// Created by resca on 7/13/2023.
//

/***************************************************************************
 *
 * Required Includes
 *
 ***************************************************************************/

//ANSI C
#include <stdbool.h>
#include <stdlib.h>

//Boot Flash include
#include "BOOT_FLASH.h"

/***************************************************************************
 *
 * Defines
 *
 ***************************************************************************/

/***************************************************************************
 *
 * Private functions
 *
 ***************************************************************************/

static boot_status_t flash_lock(void)
{
    //Lock Flash
    SET_BIT(FLASH->CR, FLASH_CR_LOCK);

    return BOOT_OK;
}

static boot_status_t flash_unlock(void)
{
    //Check if FLASH is locked, if is then unlock it
    if(READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET) {

        //Unlock Internal Flash
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;

        //Check if Flash is unlocked
        if(READ_BIT(FLASH->CR, FLASH_CR_LOCK) != RESET) {
            return BOOT_ERROR;
        }
    }

    return BOOT_OK;
}

static boot_status_t boot_wait_for_last_operation(uint32_t Timeout)
{
    /** Get Tick start **/
    uint32_t TickOld = BOOT_GetTick();

    /** Wait to Flash finish last operation **/
    while( READ_BIT(FLASH->SR, FLASH_SR_BSY) == SET )
    {
        if( (Timeout == 0) || ( BOOT_GetTick() - TickOld ) > Timeout )
        {
            return BOOT_TIMEOUT;
        }
    }

    /** Check EOP flag **/
    if(READ_BIT(FLASH->SR, FLASH_SR_EOP) == SET )
    {
        /** Clear bit **/
        CLEAR_BIT(FLASH->SR, FLASH_SR_EOP);
    }

    return BOOT_OK;
}

static void boot_flash_program_halfword(uint32_t Address, uint16_t Data)
{
    /** Proceed to program the new data **/
    SET_BIT(FLASH->CR, FLASH_CR_PG);

    /** Write data in the selected address **/
    *(__IO uint16_t *)Address = Data;
}

static void boot_flash_page_erase(uint32_t PageAddress)
{
    //Set Page erase operation
    SET_BIT(FLASH->CR, FLASH_CR_PER);

    //Set Page address to be erased
    WRITE_REG(FLASH->AR, PageAddress);

    //Start operation
    SET_BIT(FLASH->CR, FLASH_CR_STRT);
}

static boot_status_t boot_flash_program(uint32_t Address, uint64_t Data, boot_flash_program_type TypeProgram) {

    //Local Variables
    uint8_t Index = 0, itr = 0;
    boot_status_t uStatus = BOOT_OK;

    /** Wait for last operation **/
    uStatus = boot_wait_for_last_operation(5000);
    if(uStatus != BOOT_OK)
    {
        return uStatus;
    }

    switch(TypeProgram)
    {
        case BOOT_FLASH_TYPEPROGRAM_HALFWORD:
            itr = 1;
            break;

        case BOOT_FLASH_TYPEPROGRAM_WORD:
            itr = 2;
            break;

        case BOOT_FLASH_TYPEPROGRAM_DOUBLEWORD:
            itr = 4;
            break;

        default:
            return BOOT_ERROR;
    }

    /** Unlock Flash memory **/
    uStatus = flash_unlock();
    if(uStatus != BOOT_OK)
    {
        return uStatus;
    }

    for( Index = 0; Index < itr; Index++)
    {
        /** Write data in Flash **/
        boot_flash_program_halfword(Address + (2 * Index), (uint16_t)(Data >> (16 * Index)));

        /** Wait to write process finish **/
        uStatus = boot_wait_for_last_operation(5000);

        /** Once operation finished, then disable PG bit **/
        CLEAR_BIT(FLASH->CR, FLASH_CR_PG);

        if(uStatus != BOOT_OK)
        {
            break;
        }
    }

    /** Lock Flash memory **/
    (void)flash_lock();

    return uStatus;
}

/***************************************************************************
 *
 * Public Functions
 *
 ***************************************************************************/

boot_status_t BOOT_FLASH_Write(uint32_t Address, uint32_t *pData, uint16_t Size)
{
    //Local Variables
    boot_status_t uStatus = BOOT_OK;

    while(Size != 0)
    {
        uStatus = boot_flash_program(Address, *(pData), BOOT_FLASH_TYPEPROGRAM_WORD);
        if(uStatus != BOOT_OK)
        {
            break;
        }

        /** Update data **/
        Address += 4U;
        pData++;
        Size--;
    }

    return uStatus;
}

boot_status_t BOOT_FLASH_Write16Bit(uint32_t Address, uint16_t *pData, uint16_t Size)
{
    //Local Variables
    boot_status_t uStatus = BOOT_OK;

    while(Size != 0)
    {
        uStatus = boot_flash_program(Address, *(pData), BOOT_FLASH_TYPEPROGRAM_HALFWORD);
        if(uStatus != BOOT_OK)
        {
            break;
        }

        /** Update data **/
        Address += 2U;
        pData++;
        Size--;
    }

    return uStatus;
}

boot_status_t BOOT_FLASH_Read(uint32_t Address, uint32_t *pData, uint16_t Size)
{
    /** Local Variables **/
    boot_status_t uStatus = BOOT_OK;

    if( Address < FLASH_PAGE_0 || Address > (FLASH_PAGE_255 + FLASH_PAGE_SIZE) )
    {
        return BOOT_ERROR;
    }

    /** Read data from Flash **/
    while(Size != 0)
    {
        *(pData) =  *(__IO uint32_t *) Address;
        Address += 4;
        pData++;
        Size--;
    }

    return uStatus;
}

boot_status_t BOOT_Flash_Read16Bit(uint32_t Address, uint16_t *pData, uint16_t Size)
{
    /** Local Variables **/
    boot_status_t uStatus = BOOT_OK;

    if( Address < FLASH_PAGE_0 || Address > (FLASH_PAGE_255 + FLASH_PAGE_SIZE) )
    {
        return BOOT_ERROR;
    }

    /** Read data from Flash **/
    while(Size != 0)
    {
        *(pData) =  *(__IO uint16_t *) Address;
        Address += 2;
        pData++;
        Size--;
    }

    return uStatus;
}

boot_status_t BOOT_FLASH_Erase(boot_erase_init_t *pEraseInit, uint32_t *PageError) {

    //Local Variables
    uint32_t Address = 0;
    boot_status_t uStatus = BOOT_OK;

    /** Check if input data is valid **/
    if(pEraseInit == NULL || PageError == NULL)
    {
        return BOOT_ERROR;
    }

    //Select erase operation according to erase type
    switch(pEraseInit->TypeErase)
    {
        case FLASH_TYPEERASE_PAGES:
            uStatus = BOOT_FLASH_ErasePage(pEraseInit->PageAddress, pEraseInit->NbPages, PageError);
            break;

        case FLASH_TYPEERASE_MASSERASE:
            break;

        default:
            return BOOT_ERROR;
    }

    return uStatus;
}

boot_status_t BOOT_FLASH_ErasePage(uint32_t PageAddress, uint16_t NumberOfPages, uint32_t *PageError) {

    //Local Variables
    uint32_t Address = 0;
    boot_status_t uStatus = BOOT_OK;

    /** Wait for last operation **/
    if (boot_wait_for_last_operation(5000) == BOOT_OK)
    {
        //Unlock Flash
        uStatus = flash_unlock();
        if(uStatus != BOOT_OK)
        {
            return uStatus;
        }

        for(Address = PageAddress; Address < ((NumberOfPages * FLASH_PAGE_SIZE) + PageAddress); Address += FLASH_PAGE_SIZE )
        {
            //Erase Page
            boot_flash_page_erase(Address);

            uStatus = boot_wait_for_last_operation(5000);

            //Clear PER Flag
            CLEAR_BIT(FLASH->CR, FLASH_CR_PER);

            /** If and error happened, set Address value which an error occurred **/
            if(uStatus != BOOT_OK)
            {
                *(PageError) = Address;
                break;
            }
        }

        //Lock Flash
        (void)flash_lock();

    }
    else
    {
        uStatus = BOOT_TIMEOUT;
    }

    return uStatus;
}

