cmake_minimum_required (VERSION 2.8)
project (PID_Example)

#version number
set (PID_Example_VERSION_MAJOR 1)
set (PID_Example_VERSION_MINOR 0)

#include the subdirectory containing our libs
add_subdirectory (Library)
include_directories(Library)
#indicate the entry point for the executable
add_executable (PID_Example Library Example.cpp)

# Indicate which libraries to include during the link process.
target_link_libraries (PID_Example Library)

install (TARGETS PID_Example DESTINATION bin)
