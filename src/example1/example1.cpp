/**
 * @file example1.cpp
 * @brief Example file demonstrating the usage of Perceptron class with 2 input and 2 output neurons.
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
#include "example1.hpp"

int main()
{
    Perceptron<2ul, 2ul> percep;

    percep.insertLayer(2);
    percep.setWeight(0,0,0,0.3);
    percep.setWeight(0,0,1,-0.4);
    percep.setWeight(0,0,2,0.25);
    percep.setWeight(0,1,0,0.2);
    percep.setWeight(0,1,1,0.6);
    percep.setWeight(0,1,2,0.45);
    percep.setWeight(1,0,0,0.7);
    percep.setWeight(1,0,1,-0.5);
    percep.setWeight(1,0,2,0.15);
    percep.setWeight(1,1,0,-0.3);
    percep.setWeight(1,1,1,-0.1);
    percep.setWeight(1,1,2,0.35);

    std::vector<double> input;
    input.push_back(2);
    input.push_back(3);

    percep.setInput(input);
    percep.print();

    return 0;
}