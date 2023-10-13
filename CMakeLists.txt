project(Perceptron)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

add_executable(perceptron neuron.cpp perceptron.cpp resource.cpp main.cpp)