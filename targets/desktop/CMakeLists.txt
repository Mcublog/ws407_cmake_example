set(MOCKS mocks)
# Set defines
add_definitions(-DprojCOVERAGE_TEST=0)
add_definitions(-D_WINDOWS_)

get_property(INCLUDE_DIRS GLOBAL PROPERTY DESKTOP_INCLUDE_DIR)

# Add includes dir
include_directories(${INCLUDE_DIRS})
# Add sources
file(GLOB MOCKS_SOURCES "${IO_MOCK_DIR}/*.c" "${MOCKS_DIR}/*.c")

add_library(${MOCKS} STATIC ${MOCKS_SOURCES})
