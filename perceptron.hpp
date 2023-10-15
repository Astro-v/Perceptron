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
 * @class Perceptron
 * @brief Perceptron class as several layer of Neurons
*/
template <size_t in, size_t out>
class Perceptron
{
private:
    size_t nbLayer_;
    std::vector<size_t> layerList_;
    std::vector<std::shared_ptr<double>> inputList_;   
    std::vector<std::shared_ptr<double>> outputList_;   
    std::vector<Layer> neuronList_;

public:
    /**
     * @name Perceptron
     * @brief Default constructor for the Perceptron class
     * @return No return
    */
    Perceptron();

    /**
     * @name Perceptron
     * @brief Constructor for the Perceptron class
     * @param layerList List of size for each layer
     * @return No return
    */
    Perceptron(std::vector<size_t> layerList);

    /**
     * @name ~Neuron
     * @brief Destructor for the Neuron class
     * @return No return
    */
    ~Perceptron();

    /**
     * @name insertLayer
     * @brief Insert a layer with nbNeuron neuron
     * @param nbNeuron Number of Neurons to add to the layer (defautl 1)
     * @param index Index for the insertion (default = -1 mean added at the end before the output layer)
     * @return No return
    */
    void insertLayer(const size_t& nbNeuron = 1,const int& index = -1);

    /**
     * @name setInput
     * @brief Update all output according to the new input list
     * @param input New input list
     * @return No return
    */
    void setInput(const std::vector<double>& input);

    /**
     * @name getOutput
     * @brief Return a specific output
     * @param index Index of the returned output
     * @return Return the output associated to the index
    */
    double getOutput(const int& index);

protected:
    /**
     * @name run
     * @brief Update all output of each neurons starting from the upper layer
     * @return No return
    */
    void run();
};

#endif // PERCEPTRON_HPP