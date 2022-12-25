include(${PROJECT_SOURCE_DIR}/config/common.cmake)
include(${PROJECT_SOURCE_DIR}/config/desktop.cmake)

set(CMAKE_C_COMPILER ${GCC_DESKTOP})
# Common sources
file(GLOB_RECURSE TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${APP_DIR}/*.c
    ${IO_MOCK_DIR}/*.c
    ${MOCKS_DIR}/*.c
 )

add_executable(${COMMON_TYPES_TARGET} ${TEST_SOURCES})

# Include paths
target_include_directories(${COMMON_TYPES_TARGET} PRIVATE ${APP_DIRS} ${DESKTOP_INCLUDE_DIR})

# Added test
add_test(NAME ${COMMON_TYPES_TARGET}
         COMMAND ${COMMON_TYPES_TARGET})
