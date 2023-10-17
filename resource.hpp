/**
 * @file resource.hpp
 * @brief Implement the resourses that can be needed in other files
 * @author Valentin MICHEL
 * @date 09/10/2023
 * @note For naming rules follow https://manual.gromacs.org/5.1.1/dev-manual/naming.html
 */

#ifndef RESOURCE_HPP
#define RESOURCE_HPP

typedef double (&NetInputFct)(std::vector<std::shared_ptr<double>>, const std::vector<double>);
typedef double (&Fct)(const double&);

struct ActivationFct
{
    Fct function;
    Fct derivate;
};


/**
 * @name weightedSum
 * @brief Function that compute the weighted sum of input
 * @param input Input list
 * @param weight Weight list - The last element is the bias weight associate with the -1 entry
 * @return Return the weighted sum
*/
double weightedSum(std::vector<std::shared_ptr<double>> input, const std::vector<double> weight);

/**
 * @name sigmoid
 * @brief Sigmoid function
 * @param x Input variable of the function
 * @return Return value of Sigmoid(x)
*/
double sigmoid(const double& x);

/**
 * @name dSigmoid
 * @brief Derivative of sigmoid function
 * @param x Input variable of the function
 * @return Return value of dSigmoid(x) / dx
*/
double dSigmoid(const double& x);

#endif // RESOURCE_HPP