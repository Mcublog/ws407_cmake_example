cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_TRY_COMPILE_TARGET_TYPE   "STATIC_LIBRARY")
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)

set(STM32F407F_TARGET               ws407_fw)
set(DESKTOP_TARGET                  ws407_desktop)

# region GLOBAL PROPERTIES
set(STM32F407_TARGET_PATH           ${CMAKE_CURRENT_SOURCE_DIR}/targets/stm32f407)
set(DESKTOP_TARGET_PATH             ${CMAKE_CURRENT_SOURCE_DIR}/targets/desktop)

set(APP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app)
set(DEBUG_DIR ${APP_DIR}/debug)
set(UTILS_DIR ${APP_DIR}/utils)

set(APP_DIRS
    ${APP_DIR}
    ${DEBUG_DIR}
    ${UTILS_DIR}
)

set_property(GLOBAL PROPERTY APP_INCLUDE_DIRS_PROPERTY ${APP_DIRS})

set(IO_MOCK_DIR ${DESKTOP_TARGET_PATH}/io_mock)
set(MOCKS_DIR ${DESKTOP_TARGET_PATH}/mocks)

set_property(GLOBAL PROPERTY DESKTOP_INCLUDE_DIR
    ${DESKTOP_DIR}
    ${IO_MOCK_DIR}
    ${MOCKS_DIR}
    ${APP_DIRS}
)

set(HAL_INCLUDE_DIRS
    # Put here your include dirs, one in each line, relative to CMakeLists.txt file location
    ${STM32F407_TARGET_PATH}/Core/Inc
    ${STM32F407_TARGET_PATH}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${STM32F407_TARGET_PATH}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    ${STM32F407_TARGET_PATH}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${STM32F407_TARGET_PATH}/Drivers/CMSIS/Include
)

set_property(GLOBAL PROPERTY HAL_INCLUDE_DIRS_PROPERTY ${HAL_INCLUDE_DIRS})
# endregion

# region MCU GLOBAL PROPERTY

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
# endregion


message("Build type: "              ${CMAKE_BUILD_TYPE})

project(ws407_cmake_example VERSION 0.0.1 LANGUAGES C CXX ASM)

add_subdirectory(app)
add_subdirectory(targets)

# Added color compiler output
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
endif()

# Set defines
add_definitions(-DprojCOVERAGE_TEST=0)
add_definitions(-D_WINDOWS_)

# region DESKTOP APP

# Buid DESKTOP target
add_executable(${DESKTOP_TARGET} ${DESKTOP_TARGET_PATH}/main.c)

# Link libs
target_link_libraries(${DESKTOP_TARGET} app)
target_link_libraries(${DESKTOP_TARGET} mocks)

# Include paths
target_include_directories(${DESKTOP_TARGET} PRIVATE
    ${DESKTOP_DIR}
    ${IO_MOCK_DIR}
    ${DEBUG_DIR}
    ${APP_DIR}
)
# endregion


# region F407 FW

# Set linker script
set(linker_script_SRC ${STM32F407_TARGET_PATH}/STM32F407VETx_FLASH.ld)

# Executable files
add_executable(${STM32F407F_TARGET} ${STM32F407_TARGET_PATH}/Core/Src/main.c)

# Link libs
target_link_libraries(${STM32F407F_TARGET} app_fw)
target_link_libraries(${STM32F407F_TARGET} hal)

# Include paths
target_include_directories(${STM32F407F_TARGET} PRIVATE
    ${HAL_INCLUDE_DIRS}
    ${APP_DIRS}
)

# Project symbols
target_compile_definitions(${STM32F407F_TARGET} PRIVATE ${symbols_SYMB})

# Compiler options
target_compile_options(${STM32F407F_TARGET} PRIVATE ${ARM_NONE_EABI_FLAGS})
# Linker options
target_link_options(${STM32F407F_TARGET} PRIVATE
    -T${linker_script_SRC}
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

# # Execute post-build to print size
# add_custom_command(TARGET ${STM32F407F_TARGETST_BUILD
#     COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${STM32F407F_TARGET )

# Convert output to hex and binary
add_custom_command(TARGET ${STM32F407F_TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${STM32F407F_TARGET}>$ ${STM32F407F_TARGET}.hex
)

# Convert to bin file -> add conditional check?
add_custom_command(TARGET ${STM32F407F_TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${STM32F407F_TARGET}>$ ${STM32F407F_TARGET}.bin
)
# endregion


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
