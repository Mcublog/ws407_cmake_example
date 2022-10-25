set(HAL_LIB hal)

# GET DEFINES
get_property(symbols_SYMB GLOBAL PROPERTY STM32_DEFINES_PROPERTY)
# Get inlcudes
get_property(INCLUDE_DIRS GLOBAL PROPERTY HAL_INCLUDE_DIRS_PROPERTY)
get_property(APP_INCLUDE_DIRS GLOBAL PROPERTY APP_INCLUDE_DIRS_PROPERTY)
# Get compiler options
get_property(ARM_NONE_EABI_FLAGS GLOBAL PROPERTY ARM_NONE_EABI_FLAGS_PROPERTY)
# message(ARM_NONE_EABI_FLAGS="${ARM_NONE_EABI_FLAGS}")


# Add sources
file(GLOB_RECURSE HAL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.s")
list(REMOVE_ITEM HAL_SOURCES "main.c")

# message(HAL_SOURCES="${HAL_SOURCES}")
# message(symbols_SYMB="${symbols_SYMB}")

# Build lib
add_library(${HAL_LIB} STATIC ${HAL_SOURCES})

# Include paths
target_include_directories(${HAL_LIB} PRIVATE ${INCLUDE_DIRS} ${APP_INCLUDE_DIRS})

# Project symbols
target_compile_definitions(${HAL_LIB} PRIVATE ${symbols_SYMB})

# Compiler options
target_compile_options(${HAL_LIB} PRIVATE ${ARM_NONE_EABI_FLAGS})
