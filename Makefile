﻿#ARM Program flags
CC = arm-none-eabi-gcc
AS = ${CC} -x assembler-with-cpp
SIZE = arm-none-eabi-size

#Debug Flag
DEBUG = 1

#Executable name
EXECUTABLE_NAME = bootloader

#MCU Defines
STM32F334R8TX_DEFINE = -DSTM32F334x8
STM32F303K8Tx_DEFINE = -DSTM32F303x8

#Linker files
STM32F334R8TX_LINKER = STM32F334R8TX_FLASH.ld
STM32F303K8Tx_LINKER = STM32F303K8Tx_FLASH.ld

#Main directories
BUILD_DIR = build
DRIVERS_DIR = Drivers
STARTUP_DIR = Startup
SRC_DIR = Src
INC_DIR = Inc
LINKER_DIR = Linker

#Subdirectories
CMSIS_DIR = ${DRIVERS_DIR}/CMSIS
MODULE_DIR = ${DRIVERS_DIR}/Module
HARDWDEF_DIR = ${DRIVERS_DIR}/HardwareDefinition

#Variable declarations
INCLUDES = 

#MCU Define select
ifeq ($(MCU),STM32F334R8TX)
DEFINES = ${STM32F334R8TX_DEFINE}
else
DEFINES = ${STM32F303K8Tx_DEFINE}
endif

#Linker file select
ifeq ($(MCU),STM32F334R8TX)
LINKER_FILE = ${LINKER_DIR}/${STM32F334R8TX_LINKER}
else
LINKER_FILE = ${LINKER_DIR}/${STM32F303K8Tx_LINKER}
endif

#Startup file select
ifeq ($(MCU),STM32F334R8TX)
ASM_FILES += Startup/startup_stm32f334r8tx.s
else
ASM_FILES += Startup/startup_stm32f303x8.s
endif

#Sources files
SRC_FILES += main.c
SRC_FILES += ${SRC_DIR}/stm32f3xx_it.c
SRC_FILES += ${SRC_DIR}/syscalls.c
SRC_FILES += ${SRC_DIR}/sysmem.c

# Driver files
SRC_FILES += ${MODULE_DIR}/Src/DRV_FLASH.c
SRC_FILES += ${MODULE_DIR}/Src/DRV_FPU.c
SRC_FILES += ${MODULE_DIR}/Src/DRV_GPIO.c
SRC_FILES += ${MODULE_DIR}/Src/DRV_UART.c
SRC_FILES += ${MODULE_DIR}/Src/DRV_TIMEBASE.c
SRC_FILES += ${MODULE_DIR}/Src/DRV_SPI.c

# Hardware Definition files
SRC_FILES += ${HARDWDEF_DIR}/Src/Port.c

#Include directories
INCLUDES += -I ${INC_DIR}
INCLUDES += -I ${CMSIS_DIR}/Include
INCLUDES += -I ${CMSIS_DIR}/Device/ST/STM32F3xx/Include
INCLUDES += -I ${MODULE_DIR}/Inc
INCLUDES += -I ${HARDWDEF_DIR}/Inc

#Flags
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu11  ${DEFINES} ${INCLUDES}
LDFLAGS = -T ${LINKER_FILE} -nostdlib -mcpu=cortex-m4 -mthumb -Wl,-Map=${BUILD_DIR}/${EXECUTABLE_NAME}.map --specs=nosys.specs

#Debug decision
ifeq ($(DEBUG),1)
CFLAGS += -Og -g
LDFLAGS += -Og -g
else
CFLAGS += -O2
LDFLAGS += -O2
endif

#######################################
# build the application
#######################################

# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(SRC_FILES:.c=.o)))
vpath %.c $(sort $(dir $(SRC_FILES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_FILES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_FILES)))

#Compile
${BUILD_DIR}/%.o: %.c
	${CC} ${CFLAGS} $< -o $@

${BUILD_DIR}/%.o: %.s
	${AS} ${CFLAGS} $< -o $@

${BUILD_DIR}/${EXECUTABLE_NAME}.elf: create ${OBJECTS}
	${CC} ${LDFLAGS} ${OBJECTS} -o ${BUILD_DIR}/${EXECUTABLE_NAME}.elf

all : ${BUILD_DIR}/${EXECUTABLE_NAME}.elf
	${SIZE} ${BUILD_DIR}/${EXECUTABLE_NAME}.elf

create:
	mkdir -p ${BUILD_DIR}

clean:
	rm -fR ${BUILD_DIR}
