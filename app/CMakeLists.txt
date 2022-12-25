include(${PROJECT_SOURCE_DIR}/config/common.cmake)

# Add includes dir
include_directories(
    .
    debug
    utils
)

# Common sources
file(GLOB_RECURSE APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

# region FW lib
add_library(${APP_FW} STATIC ${APP_SOURCES})

# endregion
#
# Compiler options
#
target_compile_options(${APP_FW} PRIVATE ${ARM_NONE_EABI_FLAGS})
#
# APP lib
#
add_library(${APP} STATIC ${APP_SOURCES})
