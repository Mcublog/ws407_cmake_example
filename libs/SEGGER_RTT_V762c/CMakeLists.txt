include(${PROJECT_SOURCE_DIR}/config/common.cmake)
# # Get target name
# get_property(RTT_LIB GLOBAL PROPERTY RTT_LIB_NAME_PROPERTY)
# # GET DEFINES
# get_property(symbols_SYMB GLOBAL PROPERTY STM32_DEFINES_PROPERTY)
# # Get inlcudes
# get_property(INCLUDE_DIRS GLOBAL PROPERTY RTT_INCLUDES_PROPERTY)
# # Get compiler options
# get_property(ARM_NONE_EABI_FLAGS GLOBAL PROPERTY ARM_NONE_EABI_FLAGS_PROPERTY)

# Add sources
file(GLOB_RECURSE RTT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/RTT/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/RTT/*.S
    ${CMAKE_CURRENT_SOURCE_DIR}/Syscalls/SEGGER_RTT_Syscalls_GCC.c
)

# Build lib
add_library(${RTT_LIB} STATIC ${RTT_SOURCES})

# Include paths
target_include_directories(${RTT_LIB} PRIVATE ${RTT_INCLUDE_DIRS})

# Project symbols
target_compile_definitions(${RTT_LIB} PRIVATE ${symbols_SYMB})

# Compiler options
target_compile_options(${RTT_LIB} PRIVATE ${ARM_NONE_EABI_FLAGS})

