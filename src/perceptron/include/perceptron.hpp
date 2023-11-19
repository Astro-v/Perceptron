/**
 * @file perceptron.hpp
 * @brief Implement the Perceptron class
 * @author Valentin MICHEL
 * @date 09/10/2023
 * @note For naming rules follow https://manual.gromacs.org/5.1.1/dev-manual/naming.html
 */

#ifndef PERCEPTRON_HPP
#define PERCEPTRON_HPP

typedef std::vector<Neuron> Layer;


/**
 * @brief A class representing a perceptron, a type of artificial neural network.
 * 
 * A perceptron consists of one or more layers of neurons, each connected to the next layer by a set of weights. 
 * The output of each neuron is determined by the weighted sum of its inputs, passed through an activation function.
 * The perceptron can be trained using a supervised learning algorithm to adjust the weights and improve its accuracy.
 */
template <size_t in, size_t out>
class Perceptron
{
private:
    /**
     * @brief Number of layers in the perceptron.
     * 
     */
    size_t nbLayer_;

    /**
     * @brief A vector of unsigned integers used to represent the layers of a perceptron.
     * 
     */
    std::vector<size_t> layerList_;
    
    /**
     * @brief A vector of shared pointers to double values representing the input list of the perceptron.
     */
    std::vector<std::shared_ptr<double>> inputList_;   
    
    /**
     * @brief A vector of shared pointers to double values. Contains the output values list of the perceptron.
     * 
     */
    std::vector<std::shared_ptr<double>> outputList_;

    /**
     * @brief A vector of Layer objects representing the layers of a perceptron.
     * 
     */
    std::vector<Layer> neuronList_;

    /**
     * @brief The minimum value for the random initialization of weights.
     * 
     */
    double minRdm_ = -2;

    /**
     * @brief The maximum value for the random initialization of weights.
     * 
     */
    double maxRdm_ =  2;

public:


    /**
     * @brief Constructs a new Perceptron object.
     * 
     */
    Perceptron();

    /**
     * @brief Constructs a Perceptron object with the given layer list.
     * 
     * @param layerList A vector of size_t values representing the number of neurons in each layer.
     */
    Perceptron(const std::vector<size_t>& layerList);

    /**
     * @brief Destructor for the Perceptron class.
     * 
     */
    ~Perceptron();

    /**
     * @brief Inserts a new layer of neurons at the specified index.
     * 
     * @param nbNeuron The number of neurons in the new layer.
     * @param index The index at which to insert the new layer. If set to -1, the new layer is appended to the end.
     */
    void insertLayer(const size_t& nbNeuron = 1,const size_t& index = -1);

    /**
     * @brief Sets the weight of a neuron in a specific layer.
     * 
     * @param indexLayer The index of the layer containing the neuron.
     * @param indexNeuron The index of the neuron whose weight is being set.
     * @param indexWeight The index of the weight being set.
     * @param value The value to set the weight to.
     */
    void setWeight(const size_t& indexLayer, const size_t& indexNeuron, const size_t& indexWeight, const double& value);

    /**
     * @brief Sets the input vector for the perceptron.
     * 
     * @param input The input vector to be set.
     */
    void setInput(const std::vector<double>& input);

    /**
     * @brief Get the output value of the perceptron at the given index.
     * 
     * @param index The index of the output value to retrieve.
     * @return Double The output value at the given index.
     */
    double getOutput(const size_t& index);

    /**
     * @brief Prints the weights and bias of the perceptron.
     * 
     */
    void print() const;

    /**
     * @brief Trains the perceptron with the given input and expected output using the specified learning rate.
     * 
     * @param input The input vector.
     * @param expectedOutput The expected output vector.
     * @param lambda The learning rate.
     */
    void learn(const std::vector<double>& input, const std::vector<double>& expectedOutput, const double& lambda);

protected:

    /**
     * @brief Runs the perceptron algorithm.
     * 
     */
    void run();

    /**
     * @brief Initializes the perceptron weights and bias.
     * 
     */
    void initialize();

    /**
     * @brief Adds a layer to the perceptron with the specified number of neurons and at the specified index.
     * 
     * @param nbNeuron Number of neurons to add to the layer.
     * @param index Index at which to add the layer. If negative, the layer is added at the end.
     */
    void addLayer(const size_t& nbNeuron = 1,const size_t& index = -1);
};

#include "perceptron.ipp"

#endif // PERCEPTRON_HPP