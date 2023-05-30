#ARM Program flags
CC = arm-none-eabi-gcc
AS = ${CC} -x assembler-with-cpp
SIZE = arm-none-eabi-size

#Debug Flag
DEBUG = 1

#Executable name
EXECUTABLE_NAME = bootloader

#define MCU Family Define
MCU_FAMILY_DEFINE = -DSTM32F3XX

#MCU Defines
STM32F334R8TX_DEFINE = -DSTM32F334x8
STM32F303K8Tx_DEFINE = -DSTM32F303x8
STM32F303RETx_DEFINE = -DSTM32F303xE

#Linker files
STM32F334R8TX_LINKER = STM32F334R8TX_FLASH.ld
STM32F303K8Tx_LINKER = STM32F303K8Tx_FLASH.ld
STM32F303RETx_LINKER = STM32F303RETX_FLASH.ld

#Main directories
BUILD_DIR = build
DRIVERS_DIR = Drivers
STARTUP_DIR = Startup
SRC_DIR = Src
INC_DIR = Inc
LINKER_DIR = Linker

#Subdirectories
CMSIS_DIR = ${DRIVERS_DIR}/CMSIS
HARDWDEF_DIR = ${DRIVERS_DIR}/HardwareDefinition
BOOT_DIR = ${DRIVERS_DIR}/Bootloader

#Variable declarations
INCLUDES =
DEFINES =

#MCU Family define select
ifeq ($(MCU_FAMILY),STM32F3XX)
DEFINES += ${MCU_FAMILY_DEFINE}
endif

#MCU Define select
ifeq ($(MCU),STM32F334R8TX)
DEFINES += ${STM32F334R8TX_DEFINE}
endif

ifeq ($(MCU),STM32F303RET6)
DEFINES += ${STM32F303RETx_DEFINE}
else
DEFINES += ${STM32F303K8Tx_DEFINE}
endif

#Linker file select
ifeq ($(MCU),STM32F334R8TX)
LINKER_FILE = ${LINKER_DIR}/${STM32F334R8TX_LINKER}
endif

ifeq ($(MCU),STM32F303RET6)
LINKER_FILE =  ${LINKER_DIR}/${STM32F303RETx_LINKER}
else
LINKER_FILE = ${LINKER_DIR}/${STM32F303K8Tx_LINKER}
endif

#Startup file select
ifeq ($(MCU),STM32F334R8TX)
ASM_FILES += Startup/startup_stm32f334r8tx.s
endif

ifeq ($(MCU),STM32F303RET6)
ASM_FILES += Startup/startup_stm32f303retx.s
else
ASM_FILES += Startup/startup_stm32f303x8.s
endif

#Sources files
SRC_FILES += main.c
SRC_FILES += ${SRC_DIR}/stm32f3xx_it.c
SRC_FILES += ${SRC_DIR}/syscalls.c
SRC_FILES += ${SRC_DIR}/sysmem.c
SRC_FILES += ${SRC_DIR}/system_stm32f3xx.c

# Hardware Definition files
SRC_FILES += ${HARDWDEF_DIR}/Src/Port.c

# Bootloader files
SRC_FILES += ${BOOT_DIR}/Src/BOOT.c
SRC_FILES += ${BOOT_DIR}/Src/BOOT_GPIO.c
SRC_FILES += ${BOOT_DIR}/Src/BOOT_UART.c

#Include directories
INCLUDES += -I ${INC_DIR}
INCLUDES += -I ${CMSIS_DIR}/Include
INCLUDES += -I ${CMSIS_DIR}/Device/ST/STM32F3xx/Include
INCLUDES += -I ${HARDWDEF_DIR}/Inc
INCLUDES += -I ${BOOT_DIR}/Inc

#Flags
CFLAGS = -c -mcpu=cortex-m4 -mthumb -std=gnu11 ${DEFINES} ${INCLUDES}
LDFLAGS = -T ${LINKER_FILE} -nostdlib -mcpu=cortex-m4 -mthumb -Wl,-Map=${BUILD_DIR}/${EXECUTABLE_NAME}.map -Wl,--print-memory-usage --specs=nosys.specs

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

create:
	mkdir -p ${BUILD_DIR}

clean:
	rm -fR ${BUILD_DIR}
