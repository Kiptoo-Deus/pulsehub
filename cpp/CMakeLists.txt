cmake_minimum_required(VERSION 3.10)
project(PulseHubCpp)
set(CMAKE_CXX_STANDARD 17)

# Manually set SDL2 paths
include_directories(C:/vcpkg/installed/x64-windows/include)
link_directories(C:/vcpkg/installed/x64-windows/lib)

add_library(system_monitor SHARED system_monitor.cpp)
target_link_libraries(system_monitor PRIVATE SDL2.lib SDL2main.lib)

set_target_properties(system_monitor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
)