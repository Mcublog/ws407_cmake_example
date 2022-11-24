cmake_minimum_required(VERSION 3.22)

set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)

# Setup compiler settings
set(CMAKE_TRY_COMPILE_TARGET_TYPE   "STATIC_LIBRARY")
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)

include(config/common.cmake)
include(config/mcu.cmake)
include(config/desktop.cmake)
# endregion

message("Build type: "              ${CMAKE_BUILD_TYPE})
message("Desktop target: "          ${DESKTOP_TARGET})
message("MCU target: "              ${STM32F407F_TARGET})

project(ws407_cmake_example VERSION 0.0.1 LANGUAGES C CXX ASM)

add_subdirectory(app)
add_subdirectory(targets)
add_subdirectory(libs)
add_subdirectory(test)

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

# Link libs
target_link_libraries(${DESKTOP_TARGET} app)

# Include paths
target_include_directories(${DESKTOP_TARGET} PRIVATE
    ${APP_DIR}
)
# endregion

# region STM32F407F_TARGET

# Added app lib
target_link_libraries(${STM32F407F_TARGET} app_fw)
target_link_libraries(${STM32F407F_TARGET} rtt)

# Include paths
target_include_directories(${STM32F407F_TARGET} PRIVATE
    ${APP_DIRS}
    ${RTT_INCLUDE_DIRS}
)

# endregion

# region Tests

# Added app lib
target_link_libraries(${COMMON_TYPES_TARGET} app)

add_test(NAME common_types_test
         COMMAND common_types_test)

enable_testing()
# endregion
