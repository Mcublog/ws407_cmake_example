cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_TRY_COMPILE_TARGET_TYPE   "STATIC_LIBRARY")
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)

set(DESKTOP_TARGET                  ws407_desktop)

include(config/common.cmake)
include(config/mcu_config.cmake)
# endregion

message("Build type: "              ${CMAKE_BUILD_TYPE})
message("Desktop target: "          ${DESKTOP_TARGET})
message("MCU target: "              ${STM32F407F_TARGET})

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

# region STM32F407F_TARGET

# Added app lib
target_link_libraries(${STM32F407F_TARGET} app_fw)

# Include paths
target_include_directories(${STM32F407F_TARGET} PRIVATE
    ${APP_DIRS}
)

# endregion


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
