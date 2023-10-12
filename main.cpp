/**
 * @file main.cpp
 * @brief Main file
 * @author Valentin MICHEL
 * @date 09/10/2023
 * @note For naming rules follow https://manual.gromacs.org/5.1.1/dev-manual/naming.html
 */

/**
 * @include External header
*/
#include <concepts>
#include <memory>
#include <vector>
#include <iostream>
#include <cmath>

/**
 * @include Internal header
*/
#include "resource.hpp"
#include "neuron.hpp"

/**
 * @name main
 * @brief Main function of the program
 * @return No error (0)
*/
int main()
{
    std::vector<std::shared_ptr<double>> input;
    input.push_back(std::make_shared<double>(1));
    input.push_back(std::make_shared<double>(2));
    input.push_back(std::make_shared<double>(3));

    Neuron neuron(weightedSum, sigmoid, 0);

    neuron.add(input[0], 0);
    neuron.add(input[1], 0);
    neuron.add(input[2], 0);

    neuron.run();

    std::cout << *neuron.getOutput() << std::endl;

    

    return 0;
}

