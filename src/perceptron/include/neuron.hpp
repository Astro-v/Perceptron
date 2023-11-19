/**
 * @file neuron.hpp
 * @brief Implement the Neuron class
 * @author Valentin MICHEL
 * @date 09/10/2023
 * @note For naming rules follow https://manual.gromacs.org/5.1.1/dev-manual/naming.html
 */

#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include <memory>
#include <functional>

/**
 * @brief The Neuron class represents a single neuron in a neural network.
 * 
 * It contains the necessary functions and variables to calculate the output of the neuron
 * based on its inputs and weights.
 */
class Neuron
{
private:
    /**
     * @brief Function pointer type for calculating the net input of a neuron.
     * 
     * @param inputs Array of input values.
     * @param weights Array of weights for each input.
     * @param numInputs Number of inputs.
     * @return double The net input value.
     */
    NetInputFct netInputFct_;

    /**
     * @brief Function pointer type for calculating the activation of a neuron.
     * 
     * @param netInput The net input value of the neuron.
     * @return double The activation value.
     */
    ActivationFct activationFct_;
    
    /**
     * @brief Function pointer type for calculating the derivative of the activation of a neuron.
     * 
     * @param netInput The net input value of the neuron.
     * @return double The derivative of the activation value.
     */
    ActivationFct derivateActivationFct_;
   
    /**
     * @brief A shared pointer to a double that stores the output of the neuron.
     */
    std::shared_ptr<double> output_;
    
    /**
     * @brief A vector of shared pointers to double values representing the input of the neuron.
     */
    std::vector<std::shared_ptr<double>> input_;

    /**
     * @brief A vector of shared pointers to double values representing the weights of a neuron, including the bias.
     */
    std::vector<std::shared_ptr<double>> weight_;


    /**
     * @brief Number of inputs of the neuron.
     * 
     */
    size_t inputNbr_;

public:

    /**
     * @brief Neuron constructor.
     * 
     * @param netInputFct Function used to calculate the net input of the neuron.
     * @param activationFct Activation function used to calculate the output of the neuron.
     * @param derivateActivationFct Derivative of the activation function used to calculate the gradient of the neuron.
     * @param weight Initial weight of the neuron (default: 0).
     */
    Neuron(NetInputFct netInputFct, ActivationFct activationFct, ActivationFct derivateActivationFct, const double& weight = 0);
    
    /**
     * @brief Destructor for the Neuron class.
     * 
     */
    ~Neuron();

    /**
     * @brief Runs the neuron's activation function and updates its output value.
     * 
     */
    void run();

    /**
     * @brief Adds an input and its corresponding weight to the neuron.
     * 
     * @param input A shared pointer to the input value.
     * @param weight The weight of the input.
     */
    void add(std::shared_ptr<double> input, const double& weight);
    
    /**
     * @brief Clears the state of the neuron.
     * 
     */
    void clear();

    /**
     * @brief Sets the weight of a specific input.
     * 
     * @param index The index of the input weight to be set.
     * @param weight The new weight value.
     */
    void setWeight(const size_t& index, const double& weight);

    /**
     * @brief Sets the bias weight of the neuron.
     * 
     * @param weight The new bias weight.
     */
    void setBias(const double& weight);

    /**
     * @brief Returns a shared pointer to the output value of the neuron.
     * 
     * @return A shared pointer to the output value of the neuron.
     */
    std::shared_ptr<double> getOutput();

    /**
     * @brief Returns the output value of the neuron.
     *
     * @return The output value of the neuron.
     */
    double getOutputValue() const;

    /**
     * @brief Returns the value of the input at the given index.
     * 
     * @param index The index of the input to retrieve.
     * @return The value of the input at the given index.
     */
    double getInputValue(const int& index) const;

    /**
     * @brief Returns the number of inputs of the neuron.
     * 
     * @return size_t The number of inputs of the neuron.
     */
    size_t getInputNbr() const;

    /**
     * @brief Returns the weight at the specified index.
     * 
     * @param index The index of the weight to retrieve.
     * @return The weight at the specified index.
     */
    double getWeight(const int& index) const;

    /**
     * @brief Calculates the derivative of the output of the neuron.
     * 
     * @return The derivative of the output of the neuron.
     */
    double getDerivativeOutput() const;
};


#endif // NEURON_HPP