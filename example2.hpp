/**
 * @file example2.hpp
 * @brief Implement the second example of use
 * @author Valentin MICHEL
 * @date 09/10/2023
 * @note For naming rules follow https://manual.gromacs.org/5.1.1/dev-manual/naming.html
 */

/**
 * @name example2
 * @brief Function that run the second example of use of neurons
 * @return No return
*/
void example2();

/**
 * @name rate
 * @brief Return the rate of the perception for the example 2 case
 * @param percep Perception to rate
 * @param n Number of test to rate
 * @return Return the rate : 100 is the best score, 0 is the worth
*/
double rate(Perceptron<2ul, 1ul>& percep, int n);