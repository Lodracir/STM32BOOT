//
// Created by lodracir on 24/02/23.
//

#ifndef INC_001_MAKEFILE_TEST_PORT_H
#define INC_001_MAKEFILE_TEST_PORT_H

/***
 * Required Includes
 ***/

//MCU Include
#include "MCU.h"

//ANSI C
#include <stdint.h>

/***
 * Typedef struct
 ***/

typedef struct
{
    GPIO_TypeDef    *Port;
    uint32_t        Pin;
}Port_t;

/***
 * Extern values
 ***/

extern Port_t PA0;
extern Port_t PA1;
extern Port_t PA2;
extern Port_t PA3;
extern Port_t PA4;
extern Port_t PA5;
extern Port_t PA6;
extern Port_t PA15;

extern Port_t PB0;
extern Port_t PB1;
extern Port_t PB2;
extern Port_t PB3;
extern Port_t PB4;
extern Port_t PB5;

extern Port_t PC13;

#endif //INC_001_MAKEFILE_TEST_PORT_H
