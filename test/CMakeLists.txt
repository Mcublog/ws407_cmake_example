include(${PROJECT_SOURCE_DIR}/config/common.cmake)

# Common sources
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_executable(${COMMON_TYPES_TARGET} ${TEST_SOURCES})

# Include paths
target_include_directories(${COMMON_TYPES_TARGET} PRIVATE ${APP_DIRS})