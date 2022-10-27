# Get RTT dir name
get_property(segger_dir GLOBAL PROPERTY RTT_VERSION_PROPERTY)
add_subdirectory(${segger_dir})