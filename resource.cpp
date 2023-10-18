/**
 * @file resource.cpp
 * @brief Resource file
 * @author Valentin MICHEL
 * @date 09/10/2023
 * @note For naming rules follow https://manual.gromacs.org/5.1.1/dev-manual/naming.html
 */

/**
 * @include External header
*/
#include <memory>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

/**
 * @include Internal header
*/
#include "resource.hpp"

double weightedSum(std::vector<std::shared_ptr<double>> input, std::vector<std::shared_ptr<double>> weight)
{   
    double result = 0;
    auto itInput = input.begin();
    auto itWeight = weight.begin();
    while (itInput != input.end())
    {
        result += **itInput * **itWeight;
        ++itInput;
        ++itWeight;
    }
    result += **itWeight;
    return result;
}


double sigmoid(const double& x)
{
    return 1 / (1 + exp(-x));
}

double dSigmoid(const double& x)
{
    double y = exp(-x);
    return y / (1 + 2 * y + y * y);
}

void initRandom()
{
    std::srand(std::time(nullptr)); 
}

double getRandomNbr(const double& min, const double& max)
{
    return (static_cast<double>(std::rand()) / RAND_MAX) * (max - min) + min;
}