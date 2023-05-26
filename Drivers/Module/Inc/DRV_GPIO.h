//
// Created by resca on 19/02/2023.
//

#ifndef INC_001_MAKEFILE_TEST_DRV_GPIO_H
#define INC_001_MAKEFILE_TEST_DRV_GPIO_H

/***
 * Required Includes
 ***/

//MCU Include
#include "MCU.h"

//ANSI C
#include <stdbool.h>

//Hardware Definition
#include "Port.h"

/***
 * Typedef enumeration
 ***/

/** GPIO Configuration enumerations **/

/** GPIO Mode **/
typedef enum
{
    GPIO_MODE_INPUT = 0x00,
    GPIO_MODE_OUTPUT_PP,
    GPIO_MODE_OUTPUT_OD,
    GPIO_MODE_ALT_FCN_PP,
    GPIO_MODE_ALT_FCN_OD,
    GPIO_MODE_ANALOG

} gpio_mode_t;

typedef enum
{
    GPIO_SPEED_LOW = 0x00,
    GPIO_SPEED_MEDIUM,
    GPIO_SPEED_HIGH

} gpio_speed_t;

typedef enum
{
    GPIO_PULL_NO = 0x00,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN

} gpio_pull_t;

typedef enum
{
    GPIO_ALT_FN_0   = 0x00,
    GPIO_ALT_FN_1,
    GPIO_ALT_FN_2,
    GPIO_ALT_FN_3,
    GPIO_ALT_FN_4,
    GPIO_ALT_FN_5,
    GPIO_ALT_FN_6,
    GPIO_ALT_FN_7,
    GPIO_ALT_FN_8,
    GPIO_ALT_FN_9,
    GPIO_ALT_FN_10,
    GPIO_ALT_FN_11,
    GPIO_ALT_FN_12,
    GPIO_ALT_FN_13,
    GPIO_ALT_FN_14,
    GPIO_ALT_FN_15

} gpio_alt_fcn_t;

typedef enum
{
    GPIO_PIN_RESET = 0x00,
    GPIO_PIN_SET
} gpio_state_t;

typedef enum
{
    GPIO_STATE_READ_LOW = 0x00,
    GPIO_STATE_READ_HIGH
} gpio_read_state_t;

/***
 * Typedef structure
 ***/

typedef struct
{
    gpio_mode_t     Mode;
    gpio_speed_t    Speed;
    gpio_pull_t     Pull;
    gpio_alt_fcn_t  AltFun;

} GPIO_Config_t;

/***
 * Prototype Public Functions
 ***/

/** Init and DeInit functions **/
void DRV_GPIO_Init(Port_t *Port, GPIO_Config_t *Config);
void DRV_GPIO_DeInit(Port_t *Port, GPIO_Config_t *Config);

void DRV_GPIO_WritePin(Port_t *Port, gpio_state_t state);
void DRV_GPIO_TogglePin(Port_t *Port);

bool DRV_GPIO_ReadPin(Port_t *Port);

#endif //INC_001_MAKEFILE_TEST_DRV_GPIO_H
