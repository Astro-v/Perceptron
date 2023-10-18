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



double rate(Perceptron<2ul, 1ul>& percep, int n);

/**
 * @name main
 * @brief Main function of the program
 * @return No error (0)
*/
int main()
{
    Perceptron<2ul, 1ul> percep;
    percep.insertLayer(2);
    percep.insertLayer(4);
    percep.insertLayer(2);

    std::cout << "AVANT : " << rate(percep, 100) << std::endl;

    std::vector<double> input;
    input.push_back(0);
    input.push_back(0);

    std::vector<double> output;
    output.push_back(0);

    for (int i = 0; i< 10000 ; ++i)
    {
        input[0] = getRandomNbr();
        input[1] = getRandomNbr();
        double x = input[0] - 0.5;
        double y = input[1] - 0.5;
        if (x * x + y * y < 0.25)
        {
            output[0] = 1;
        }
        else
        {
            output[0] = 0;
        }
        percep.learn(input, output, 0.5);
    }

    
    std::cout << "APRES : " << rate(percep, 100) << std::endl;
    return 0;
}


double rate(Perceptron<2ul, 1ul>& percep, int n)
{
    double rating = 0;
    std::vector<double> input;
    input.push_back(0);
    input.push_back(0);

    double output = 0;

    for (int i = 0; i< n ; ++i)
    {
        input[0] = getRandomNbr();
        input[1] = getRandomNbr();
        double x = input[0] - 0.5;
        double y = input[1] - 0.5;        
        if (x * x + y * y < 0.25)
        {
            output = 1;
        }
        else
        {
            output = 0;
        }
        percep.setInput(input);
        double res = output - percep.getOutput(0);
        rating += res>=0?res:-res;
    }
    return  100.0 * (n - rating) / n;
}