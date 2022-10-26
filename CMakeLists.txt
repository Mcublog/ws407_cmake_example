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

include(config/common.cmake)
include(config/mcu_config.cmake)
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
target_link_options(${STM32F407F_TARGET} PRIVATE ${STM32F407_LINKER_OPTION})

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
