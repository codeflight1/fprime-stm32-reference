set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(FPRIME_PLATFORM "Baremetal")
set(FPRIME_USE_BAREMETAL_SCHEDULER ON)

set(TOOLCHAIN_PREFIX $ENV{STM32_TOOLCHAIN_PATH}/bin/arm-none-eabi-)
# STEP 3: Specify the path to C and CXX cross compilers
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX}ld)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

set(MCU_LINKER_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/../../STM32H743VITX_FLASH.ld")

# --whole-archive needed to include interrupt handlers

set(CMAKE_EXE_LINKER_FLAGS " \
    -T${MCU_LINKER_SCRIPT} \
    -mcpu=cortex-m7 \
    -mfpu=fpv5-d16 \
    -mfloat-abi=hard \
    -mthumb \
    -Wl,--gc-sections \
    --specs=nosys.specs \
    -static \
    -Wl,--whole-archive ../lib/STM32H743/libStartup.a -Wl,--no-whole-archive \
    -Wl,--start-group \
    -lc \
    -lm \
    -lstdc++ \
    -lsupc++ \
    -Wl,--end-group")

set(COMPILER_COMMON_FLAGS
    "-fdata-sections -ffunction-sections \
    -Wall \
    -DUSE_HAL_DRIVER \
    -DUSE_PWR_LDO_SUPPLY \
    -DSTM32H743xx \
    -mcpu=cortex-m7 \
    -mthumb \
    -mfpu=fpv5-d16 \
    -mfloat-abi=hard \
    -DSTM32H743xx \
    --specs=nano.specs -Wl,--gc-sections")

set(CMAKE_C_FLAGS "${COMPILER_COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMPILER_COMMON_FLAGS}")
set(CMAKE_ASM_FLAGS "${COMPILER_COMMON_FLAGS} -x assembler-with-cpp" )

include_directories("${CMAKE_CURRENT_LIST_DIR}/../../Drivers/CMSIS/Include/")
include_directories("${CMAKE_CURRENT_LIST_DIR}/../../Drivers/STM32H7xx_HAL_Driver/Inc/")
include_directories("${CMAKE_CURRENT_LIST_DIR}/../../Drivers/CMSIS/Device/ST/STM32H7xx/Include/")
include_directories("${CMAKE_CURRENT_LIST_DIR}/../../Startup/")

set(CMAKE_FIND_ROOT_PATH $ENV{STM32_TOOLCHAIN_PATH})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
