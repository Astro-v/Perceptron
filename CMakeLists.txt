cmake_minimum_required(VERSION 3.20.0)

project(Perceptron VERSION 0.1.0 LANGUAGES CXX)

add_executable(Perceptron main.cpp neuron.cpp resource.cpp) 

# cmake -S . -B build_debug -D CMAKE_BUILD_TYPE=Debug
# cmake --build build_debug --clean-first --config Debug