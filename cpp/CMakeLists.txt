cmake_minimum_required(VERSION 3.10)
project(PulseHubCpp)
set(CMAKE_CXX_STANDARD 17)

# Build a shared library
add_library(system_monitor SHARED system_monitor.cpp)

# Ensure outputs go to lib/Debug on Windows
set_target_properties(system_monitor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>" # .dll
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>" # .so (Unix)
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>" # .lib (Windows)
)