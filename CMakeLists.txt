cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_TRY_COMPILE_TARGET_TYPE   "STATIC_LIBRARY")
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)

set(STM32F407_TARGET_PATH           ${CMAKE_CURRENT_SOURCE_DIR}/targets/stm32f407)
set(STM32F407_EXE                   ws407_fw)
set(DESKTOP_TARGET                  ws407_desktop)
message("Build type: "              ${CMAKE_BUILD_TYPE})


project(ws407_cmake_example VERSION 0.0.1)
enable_language(ASM)


# Added color compiler output
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
endif()

# Set defines
add_definitions(-DprojCOVERAGE_TEST=0)
add_definitions(-D_WINDOWS_)

set(DESKTOP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/targets/desktop)
set(IO_MOCK_DIR ${DESKTOP_DIR}/io_mock)
set(MOCKS_DIR ${DESKTOP_DIR}/mocks)
set(APP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app)
set(DEBUG_DIR ${APP_DIR}/debug)
set(UTILS_DIR ${APP_DIR}/utils)
# include(CTest)
# enable_testing()

# Add includes dir
include_directories(
    ${DESKTOP_DIR}
    ${IO_MOCK_DIR}
    ${DEBUG_DIR}
    ${APP_DIR}

)

include_directories(app)

# Add all sources
file(GLOB MOCKS_SOURCES "${IO_MOCK_DIR}/*.c" "${MOCKS_DIR}/*.c")

file(GLOB APP_SOURCES "${DEBUG_DIR}/*.c" "${APP_DIR}/*.c")

file(GLOB UTILS_SOURCES "${UTILS_DIR}/*.c")

set(DESKTOP_SOURCES
    ${DESKTOP_DIR}/main.c
    ${APP_SOURCES}
    ${MOCKS_SOURCES}
)

add_executable(${DESKTOP_TARGET} ${DESKTOP_SOURCES})

#
# Core MCU flags, CPU, instruction set and FPU setup
# Needs to be set properly for your MCU
#
set(CPU_PARAMETERS
    -mthumb
    # This needs attention to properly set for used MCU
    -mcpu=cortex-m4
    -mfpu=fpv5-d16
    -mfloat-abi=hard

)

# Set linker script
set(linker_script_SRC  ${STM32F407_TARGET_PATH}/STM32F407VETx_FLASH.ld)

#
# List of source files to compile
#
# Put here your source files, one in each line, relative to CMakeLists.txt file location
file(GLOB_RECURSE sources_SRCS ${STM32F407_TARGET_PATH}/*.c ${STM32F407_TARGET_PATH}/*.s)

#
# Include directories
#
set(include_path_DIRS
    # Put here your include dirs, one in each line, relative to CMakeLists.txt file location
    ${STM32F407_TARGET_PATH}/Core/Inc
    ${STM32F407_TARGET_PATH}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${STM32F407_TARGET_PATH}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    ${STM32F407_TARGET_PATH}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${STM32F407_TARGET_PATH}/Drivers/CMSIS/Include
    ${APP_DIR}
    ${DEBUG_DIR}
    ${UTILS_DIR}
)

#
# Symbols definition
#
set(symbols_SYMB
    # Put here your symbols (preprocessor defines), one in each line
    # Encapsulate them with double quotes for safety purpose
    "DEBUG"
    "USE_HAL_DRIVER"
    "STM32F407xx"
)

# Executable files
add_executable(${STM32F407_EXE} ${sources_SRCS} ${APP_SOURCES} ${UTILS_SOURCES})

# Include paths
target_include_directories(${STM32F407_EXE} PRIVATE ${include_path_DIRS})

# Project symbols
target_compile_definitions(${STM32F407_EXE} PRIVATE ${symbols_SYMB})

# Compiler options
target_compile_options(${STM32F407_EXE} PRIVATE
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

# Linker options
target_link_options(${STM32F407_EXE} PRIVATE
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
# add_custom_command(TARGET ${STM32F407_EXE} POST_BUILD
#     COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${STM32F407_EXE}>
# )

# Convert output to hex and binary
add_custom_command(TARGET ${STM32F407_EXE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${STM32F407_EXE}> ${STM32F407_EXE}.hex
)

# Convert to bin file -> add conditional check?
add_custom_command(TARGET ${STM32F407_EXE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${STM32F407_EXE}> ${STM32F407_EXE}.bin
)

#######

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
