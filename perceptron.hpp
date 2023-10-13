/**
 * @file perceptron.hpp
 * @brief Implement the Perceptron class
 * @author Valentin MICHEL
 * @date 09/10/2023
 * @note For naming rules follow https://manual.gromacs.org/5.1.1/dev-manual/naming.html
 */

#ifndef PERCEPTRON_HPP
#define PERCEPTRON_HPP

/**
 * @class Perceptron
 * @brief Perceptron class as several layer of Neurons
*/
class Perceptron
{
private:
    size_t nbInput_;
    std::vector<size_t> layerList_;   

public:
    /**
     * @name Perceptron
     * @brief Constructor for the Perceptron class
     * @return No return
    */
    Perceptron(size_t nbInput, std::vector<size_t> layerList);

    /**
     * @name ~Neuron
     * @brief Destructor for the Neuron class
     * @return No return
    */
    ~Perceptron();

};

#endif // PERCEPTRON_HPP