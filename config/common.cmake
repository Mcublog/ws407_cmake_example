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
