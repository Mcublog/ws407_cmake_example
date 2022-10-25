set(APP app)
set(APP_FW app_fw)

# Add includes dir
include_directories(
    .
    debug
    utils
)

# Common sources
file(GLOB_RECURSE APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

# region FW lib
add_library(${APP_FW} STATIC ${APP_SOURCES})

get_property(ARM_NONE_EABI_FLAGS GLOBAL PROPERTY ARM_NONE_EABI_FLAGS_PROPERTY)
# message(ARM_NONE_EABI_FLAGS="${ARM_NONE_EABI_FLAGS}")

# endregion
#
# Compiler options
#
target_compile_options(${APP_FW} PRIVATE ${ARM_NONE_EABI_FLAGS})
#
# APP lib
#
add_library(${APP} STATIC ${APP_SOURCES})
