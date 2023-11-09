/**
 * @file resource.hpp
 * @brief Implement the resourses that can be needed in other files
 * @author Valentin MICHEL
 * @date 09/10/2023
 * @note For naming rules follow https://manual.gromacs.org/5.1.1/dev-manual/naming.html
 */

#ifndef RESOURCE_HPP
#define RESOURCE_HPP

typedef double (&NetInputFct)(std::vector<std::shared_ptr<double>>, std::vector<std::shared_ptr<double>>);
typedef double (&ActivationFct)(const double&);

/**
 * @name weightedSum
 * @brief Function that compute the weighted sum of input
 * @param input Input list
 * @param weight Weight list - The last element is the bias weight associate with the -1 entry
 * @return Return the weighted sum
*/
double weightedSum(std::vector<std::shared_ptr<double>> input, std::vector<std::shared_ptr<double>> weight);

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

/**
 * @name initRandom
 * @brief Init the random package
 * @return No return
*/
void initRandom();

/**
 * @name getRandomNbr
 * @brief Return a random number between min and max
 * @param min Minimal value for the random number
 * @param max Maximal value for the random number
 * @return Return a random number between min and max
*/
double getRandomNbr(const double& min = 0, const double& max = 1);

#endif // RESOURCE_HPP