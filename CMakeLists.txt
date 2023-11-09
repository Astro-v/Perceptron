cmake_minimum_required(VERSION 3.20.0)

project(Perceptron VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(src)

add_executable(Perceptron main perceptron)