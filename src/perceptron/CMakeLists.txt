# FILEPATH: /home/antares/Perceptron/src/perceptron/CMakeLists.txt

# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(perceptron VERSION 1.0)

# Add the source files for the executable
add_executable(perceptron main.cpp perceptron.cpp)

# Set the C++ standard to C++11
set_target_properties(perceptron PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Link the necessary libraries
target_link_libraries(perceptron PRIVATE some_library)
