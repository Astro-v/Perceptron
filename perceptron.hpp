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

    double minRdm_ = -2;
    double maxRdm_ =  2;

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
     * @param layerList List of all layer to add to the perceptron
     * @return No return
    */
    Perceptron(const std::vector<size_t>& layerList);

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
     * @name setWeight
     * @brief Set a specific weight  
     * @param indexLayer Index of the neurons layer
     * @param indexNeuron Index of the neuron inside the layer
     * @param indexWeight Index of the weight inside the neuron
     * @param value New value for the weight
     * @return No return
    */
    void setWeight(const int& indexLayer, const int& indexNeuron, const int& indexWeight, const double& value);

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

    /**
     * @name print
     * @brief Display the all the neurons layer
     * @return No return
    */
    void print() const;
    
    /**
     * @name print
     * @brief Display the all the neurons layer
     * @param input Input list
     * @param expectedOutput Expected output
     * @param lambda Learning rate (between 0 and 1)
     * @return No return
    */
    void learn(const std::vector<double>& input, const std::vector<double>& expectedOutput, const double& lambda);

protected:
    /**
     * @name run
     * @brief Update all output of each neurons starting from the upper layer
     * @return No return
    */
    void run();

    /**
     * @name initialize
     * @brief Initialize the perceptron
     * @return No return
    */
    void initialize();

    /**
     * @name addLayer
     * @brief Add a layer to the perceptron
     * @param nbNeuron Number of Neurons to add to the layer (defautl 1)
     * @param index Index for the insertion (default = -1 mean added at the end before the output layer)
     * @return No return
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