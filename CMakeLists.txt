cmake_minimum_required(VERSION 3.0.0)
project(ws407_cmake_example VERSION 0.0.1)

# Added color compiler output
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
endif()

# Set defines
add_definitions(-DprojCOVERAGE_TEST=0)
add_definitions(-D_WINDOWS_)

set (${DESKTOP_TARGET} ws407_cmake_example_desktop)

set(DESKTOP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/targets/desktop)
set(IO_MOCK_DIR ${DESKTOP_DIR}/io_mock)
set(MOCKS_DIR ${DESKTOP_DIR}/mocks)
set(APP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app)
set(DEBUG_DIR ${APP_DIR}/debug)
# include(CTest)
# enable_testing()

# Add includes dir
include_directories(
    ${DESKTOP_DIR}
    ${IO_MOCK_DIR}
    ${DEBUG_DIR}
    ${APP_DIR}

)

include_directories(app)

# Add all sources
file(GLOB MOCKS_SOURCES "${IO_MOCK_DIR}/*.c" "${MOCKS_DIR}/*.c")

set(DESKTOP_SOURCES
    ${DESKTOP_DIR}/main.c
    ${APP_DIR}/application.c
    ${DEBUG_DIR}/log_libs.c
    ${MOCKS_SOURCES}
)

add_executable(ws407_cmake_example_desktop ${DESKTOP_SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
