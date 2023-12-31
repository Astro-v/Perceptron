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
#include "perceptron.hpp"

/**
 * @name main
 * @brief Main function of the program
 * @return No error (0)
*/
int main()
{
    Perceptron<1ul, 1ul> percep;
    percep.insertLayer(2);
    std::cout << percep.getOutput(0) << std::endl;
    percep.print();
    return 0;
}

