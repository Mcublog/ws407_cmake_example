# region MCU GLOBAL PROPERTY
set(STM32F407F_TARGET               ws407_fw)

set_property(GLOBAL PROPERTY STM32F407_TARGET_NAME_PROPERTY
    ${STM32F407F_TARGET}
)

# Put here your symbols (preprocessor defines), one in each line
# Encapsulate them with double quotes for safety purpose
set(symbols_SYMB
    "DEBUG"
    "USE_HAL_DRIVER"
    "STM32F407xx"
)

set_property(GLOBAL PROPERTY STM32_DEFINES_PROPERTY
    ${symbols_SYMB}
)

set(CPU_PARAMETERS -mthumb
    # This needs attention to properly set for used MCU
    -mcpu=cortex-m4
    -mfpu=fpv5-d16
    -mfloat-abi=hard)

set(ARM_NONE_EABI_FLAGS
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    -fdata-sections
    -ffunction-sections
    -fdiagnostics-color=always
    # Full debug configuration
    -Og -g3 -ggdb
)

set_property(GLOBAL PROPERTY ARM_NONE_EABI_FLAGS_PROPERTY
    ${ARM_NONE_EABI_FLAGS}
)

# Set linker script
set(STM32F407_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/targets/stm32f407/STM32F407VETx_FLASH.ld)

set(STM32F407_LINKER_OPTION
    -T${STM32F407_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -specs=nano.specs
    -u _printf_float                # STDIO float formatting support
    -Wl,--start-group
    -lc
    -lm
    -lnosys
    -lstdc++
    -lsupc++
    -Wl,--end-group
    -Wl,--print-memory-usage
)
# endregion