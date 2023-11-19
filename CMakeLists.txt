cmake_minimum_required(VERSION 3.20.0)
project(Perceptron VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(src bin)

# Interface library for warning flags
add_library(warning_props INTERFACE)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug mode")
    target_compile_options(warning_props INTERFACE -Wall -Wextra -Wpedantic -Werror -g -O0)
else()
    message("Release mode")
    target_compile_options(warning_props INTERFACE -O3)
endif()


# cmake -S . -B build_debug -D CMAKE_BUILD_TYPE=Debug
# cmake --build build_debug --clean-first --config Debug