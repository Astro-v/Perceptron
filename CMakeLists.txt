project(Perceptron)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

set(SRCS
    main.cpp
    perceptron.cpp
    neuron.cpp
    resource.cpp
    )
    
set(HEADERS    
    perceptron.hpp
    neuron.hpp
    resource.hpp
    )

add_executable(perceptron ${SRCS} ${HEADERS})