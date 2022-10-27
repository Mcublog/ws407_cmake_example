# Get target name
get_property(DESKTOP_TARGET GLOBAL PROPERTY DESKTOP_TARGET_NAME_PROPERTY)
# Set defines
add_definitions(-DprojCOVERAGE_TEST=0)
add_definitions(-D_WINDOWS_)

get_property(INCLUDE_DIRS GLOBAL PROPERTY DESKTOP_INCLUDE_DIR)

# Add includes dir
include_directories(${INCLUDE_DIRS})
# Add sources
file(GLOB_RECURSE DESKTOP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

# Buid DESKTOP target
add_executable(${DESKTOP_TARGET} ${DESKTOP_SOURCES})
