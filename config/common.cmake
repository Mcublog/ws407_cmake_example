set(APP     app)
set(APP_FW  app_fw)
# region GLOBAL PROPERTIES
set(STM32F407_TARGET_PATH           ${PROJECT_SOURCE_DIR}/targets/stm32f407)
set(DESKTOP_TARGET_PATH             ${PROJECT_SOURCE_DIR}/targets/desktop)

set(APP_DIR ${PROJECT_SOURCE_DIR}/app)
set(DEBUG_DIR ${APP_DIR}/debug)
set(UTILS_DIR ${APP_DIR}/utils)
set(IO_DIR ${APP_DIR}/io)
set(LIBS_DIR ${PROJECT_SOURCE_DIR}/libs)

set(APP_DIRS
    ${APP_DIR}
    ${DEBUG_DIR}
    ${UTILS_DIR}
    ${IO_DIR}
)

set(IO_MOCK_DIR ${DESKTOP_TARGET_PATH}/io_mock)
set(MOCKS_DIR ${DESKTOP_TARGET_PATH}/mocks)

set_property(GLOBAL PROPERTY DESKTOP_INCLUDE_DIR
    ${DESKTOP_DIR}
    ${IO_MOCK_DIR}
    ${MOCKS_DIR}
    ${APP_DIRS}
)

# region HAL
set(HAL_INCLUDE_DIRS
    # Put here your include dirs, one in each line, relative to CMakeLists.txt file location
    ${STM32F407_TARGET_PATH}/Core/Inc
    ${STM32F407_TARGET_PATH}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${STM32F407_TARGET_PATH}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    ${STM32F407_TARGET_PATH}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${STM32F407_TARGET_PATH}/Drivers/CMSIS/Include
)
# endregion

# region RTT
set(RTT_LIB rtt)
set(RTT_VERSION SEGGER_RTT_V762c)
set(RTT_DIR ${LIBS_DIR}/${RTT_VERSION})
set(RTT_INCLUDE_DIRS
    ${RTT_DIR}/Config
    ${RTT_DIR}/RTT)
# endregion

set(COMMON_TYPES_TARGET common_types_test)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
