# FILEPATH: /home/antares/Perceptron/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(Perceptron)

# Add executable
add_executable(perceptron main.cpp)

# Add tests
enable_testing()
add_executable(tests tests.cpp)
add_test(NAME tests COMMAND tests)

# Link libraries
target_link_libraries(tests PRIVATE Catch2::Catch2)
target_link_libraries(perceptron PRIVATE PerceptronLib)

# Add subdirectory
add_subdirectory(PerceptronLib)
