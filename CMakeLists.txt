cmake_minimum_required(VERSION 3.20.0)
project(Perceptron VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(src bin)

# cmake -S . -B build_debug -D CMAKE_BUILD_TYPE=Debug
# cmake --build build_debug --clean-first --config Debug