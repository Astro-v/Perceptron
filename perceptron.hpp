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
    void insertLayer(const size_t& nbNeuron = 1,const int& index = -1);

    /**
     * @brief Sets the weight of a neuron in a specific layer.
     * 
     * @param indexLayer The index of the layer containing the neuron.
     * @param indexNeuron The index of the neuron whose weight is being set.
     * @param indexWeight The index of the weight being set.
     * @param value The value to set the weight to.
     */
    void setWeight(const int& indexLayer, const int& indexNeuron, const int& indexWeight, const double& value);

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
    double getOutput(const int& index);

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
    void addLayer(const size_t& nbNeuron = 1,const int& index = -1);
};

template <size_t in, size_t out>
Perceptron<in, out>::Perceptron()
{
    initRandom();

    this->initialize();
    this->run();
}

template <size_t in, size_t out>
Perceptron<in, out>::Perceptron(const std::vector<size_t>& layerList)
{
    
    initRandom();
    
    this->initialize();
    for (const auto& nbNeuron : layerList)
    {
        this->addLayer(nbNeuron, -1);
    }
    this->run();
}

template <size_t in, size_t out>
Perceptron<in, out>::~Perceptron()
{

}

template <size_t in, size_t out>
void Perceptron<in, out>::insertLayer(const size_t& nbNeuron, const int& index)
{
    this->addLayer(nbNeuron, index);
    this->run();
}

template <size_t in, size_t out>
void Perceptron<in, out>::setWeight(const int& indexLayer, const int& indexNeuron, const int& indexWeight, const double& value)
{
    neuronList_[indexLayer][indexNeuron].setWeight(indexWeight, value);
}


template <size_t in, size_t out>
void Perceptron<in, out>::setInput(const std::vector<double>& input)
{
    if (input.size() != in)
    {
        throw;
    }

    // Set the inputs
    for (int index {0}; index < in; ++index)
    {
        *(inputList_[index]) = input[index];
    } 
    
    // Update all neurons output
    this->run();
}

template <size_t in, size_t out>
double Perceptron<in, out>::getOutput(const int& index)
{
    if (index < 0 || index >= out)
    {
        std::cout << "ERROR : Index out of range" << std::endl;
        throw;
    }

    return *(outputList_[index]);
}


template <size_t in, size_t out>
void Perceptron<in, out>::print() const
{
    for (int index1 {0}; index1 < nbLayer_; ++index1)
    {
        for (int index2 {0}; index2 < layerList_[index1]; ++index2)
        {
            std::cout << index1 << " - " << index2 << "(" << neuronList_[index1][index2].getInputNbr() << ") : " << neuronList_[index1][index2].getOutputValue() << std::endl;
            for (int index3 {0}; index3 < neuronList_[index1][index2].getInputNbr() + 1; ++index3)
            {
                std::cout << "W" << std::to_string(index3) << " : " << neuronList_[index1][index2].getWeight(index3) << std::endl;
            }
        }
    }
}

template <size_t in, size_t out>
void Perceptron<in, out>::learn(const std::vector<double>& input, const std::vector<double>& expectedOutput, const double& lambda)
{
    this->setInput(input);

    // Initialize the error list
    std::vector<std::vector<double>> error;
    for (const auto& layer : layerList_)
    {
        error.emplace_back();
        for (int index1 {0}; index1 < layer; ++index1)
        {
            error.back().emplace_back(0);
        }
    }

    // Compute all error
    for (size_t index1 {0ul}; index1 < layerList_.back(); ++index1)
    {
        error.back()[index1] = neuronList_.back()[index1].getDerivativeOutput() * (neuronList_.back()[index1].getOutputValue() - expectedOutput[index1]);
    }

    for (int index1 {nbLayer_ - 2}; index1 >= 0; --index1)
    {
        for (int index2 {0}; index2 < layerList_[index1]; ++index2)
        {
            double sum = 0;
            for (int index3 {0}; index3 < layerList_[index1 + 1]; ++index3)
            {
                sum += neuronList_[index1 + 1][index3].getWeight(index2) * error[index1 + 1][index3];
            }
            error[index1][index2] = neuronList_[index1][index2].getDerivativeOutput() * sum;   
        }
    }

    // Update all weight
    for (int index1 {0}; index1 < nbLayer_; ++index1)
    {
        for (int index2 {0}; index2 < layerList_[index1]; ++index2)
        {
            for (int index3 {0}; index3 < neuronList_[index1][index2].getInputNbr(); ++index3)
            {
                neuronList_[index1][index2].setWeight(index3, neuronList_[index1][index2].getWeight(index3) - 
                lambda * error[index1][index2] * neuronList_[index1][index2].getInputValue(index3));
            }
        }
    }

    this->run();
}

template <size_t in, size_t out>
void Perceptron<in, out>::run()
{
    // Update all neurons output
    for (int index1 {0}; index1 < nbLayer_; ++index1)
    {
        for (int index2 {0}; index2 < layerList_[index1]; ++index2)
        {
            neuronList_[index1][index2].run();
        }
    }
}

template <size_t in, size_t out>
void Perceptron<in, out>::initialize()
{
    // Allocation for the entry list
    for (int index {0}; index < in; ++index)
    {
        inputList_.push_back(std::make_shared<double>(0));
    }

    layerList_.push_back(out);
    neuronList_.emplace_back();
    nbLayer_ = 1;

    // Creation of the neurons
    for (int index {0}; index < out; ++index)
    {
        neuronList_.back().emplace_back(weightedSum, sigmoid, dSigmoid, getRandomNbr(minRdm_, maxRdm_));
    }

    // Set the link between entry
    for (int index1 {0}; index1 < out; ++index1)
    {   
        for (int index2 {0}; index2 < in; ++index2)
        {
            neuronList_[0][index1].add(inputList_[index2], getRandomNbr(minRdm_, maxRdm_));
        }
    }

    // Allocation for the output list
    for (int index {0}; index < out; ++index)
    {
        outputList_.push_back(neuronList_[0][index].getOutput());
    }
}


template <size_t in, size_t out>
void Perceptron<in, out>::addLayer(const size_t& nbNeuron,const int& index)
{
    int localIndex {0};
    if (index >= 0 && index < nbLayer_)
    {
        localIndex = index;
    }
    else
    {
        localIndex = nbLayer_ - 1;
    }

    // Create the layer
    auto itNeuronList = neuronList_.begin();
    auto itLayerList = layerList_.begin();
    for (int index1 {0}; index1 < localIndex; ++index1)
    {
        ++itNeuronList;
        ++itLayerList;
    }
    itNeuronList = neuronList_.emplace(itNeuronList);
    itLayerList = layerList_.insert(itLayerList, nbNeuron);
    ++nbLayer_;

    // Create each neurons in the layer
    for (int index1 {0}; index1 < nbNeuron; ++index1)
    {
        itNeuronList->emplace_back(weightedSum, sigmoid, dSigmoid, getRandomNbr(minRdm_, maxRdm_));
    }
    
    // Set the link between entry
    if (itLayerList == layerList_.begin())
    {
        // For the first layer
        for (int index1 {0}; index1 < *itLayerList; ++index1)
        {   
            for (int index2 {0}; index2 < in; ++index2)
            {
                itNeuronList->at(index1).add(inputList_[index2], getRandomNbr(minRdm_, maxRdm_));
            }
        }
    }
    else
    {
        for (int index1 {0}; index1 < *itLayerList; ++index1)
        {   
            for (int index2 {0}; index2 < *std::prev(itLayerList, 1); ++index2)
            {
                itNeuronList->at(index1).add(prev(itNeuronList, 1)->at(index2).getOutput(), getRandomNbr(minRdm_, maxRdm_));
            }
        }
    }
    
    // Set the link with the outputs
    for (int index1 {0}; index1 < *std::next(itLayerList, 1); ++index1)
    {   
        std::next(itNeuronList, 1)->at(index1).clear();
        for (int index2 {0}; index2 < *itLayerList; ++index2)
        {
            std::next(itNeuronList, 1)->at(index1).add(itNeuronList->at(index2).getOutput(), getRandomNbr(minRdm_, maxRdm_));
        }
    }
}

#endif // PERCEPTRON_HPP