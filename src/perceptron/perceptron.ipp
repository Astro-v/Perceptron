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
    for (size_t index {0}; index < in; ++index)
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
    for (size_t index1 {0}; index1 < nbLayer_; ++index1)
    {
        for (size_t index2 {0}; index2 < layerList_[index1]; ++index2)
        {
            std::cout << index1 << " - " << index2 << "(" << neuronList_[index1][index2].getInputNbr() << ") : " << neuronList_[index1][index2].getOutputValue() << std::endl;
            for (size_t index3 {0}; index3 < neuronList_[index1][index2].getInputNbr() + 1; ++index3)
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
        for (size_t index1 {0}; index1 < layer; ++index1)
        {
            error.back().emplace_back(0);
        }
    }

    // Compute all error
    for (size_t index1 {0ul}; index1 < layerList_.back(); ++index1)
    {
        error.back()[index1] = neuronList_.back()[index1].getDerivativeOutput() * (neuronList_.back()[index1].getOutputValue() - expectedOutput[index1]);
    }

    for (size_t index1 {nbLayer_ - 2}; index1 >= 0; --index1)
    {
        for (size_t index2 {0}; index2 < layerList_[index1]; ++index2)
        {
            double sum = 0;
            for (size_t index3 {0}; index3 < layerList_[index1 + 1]; ++index3)
            {
                sum += neuronList_[index1 + 1][index3].getWeight(index2) * error[index1 + 1][index3];
            }
            error[index1][index2] = neuronList_[index1][index2].getDerivativeOutput() * sum;   
        }
    }

    // Update all weight
    for (size_t index1 {0}; index1 < nbLayer_; ++index1)
    {
        for (size_t index2 {0}; index2 < layerList_[index1]; ++index2)
        {
            for (size_t index3 {0}; index3 < neuronList_[index1][index2].getInputNbr(); ++index3)
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
    for (size_t index1 {0}; index1 < nbLayer_; ++index1)
    {
        for (size_t index2 {0}; index2 < layerList_[index1]; ++index2)
        {
            neuronList_[index1][index2].run();
        }
    }
}

template <size_t in, size_t out>
void Perceptron<in, out>::initialize()
{
    // Allocation for the entry list
    for (size_t index {0}; index < in; ++index)
    {
        inputList_.push_back(std::make_shared<double>(0));
    }

    layerList_.push_back(out);
    neuronList_.emplace_back();
    nbLayer_ = 1;

    // Creation of the neurons
    for (size_t index {0}; index < out; ++index)
    {
        neuronList_.back().emplace_back(weightedSum, sigmoid, dSigmoid, getRandomNbr(minRdm_, maxRdm_));
    }

    // Set the link between entry
    for (size_t index1 {0}; index1 < out; ++index1)
    {   
        for (size_t index2 {0}; index2 < in; ++index2)
        {
            neuronList_[0][index1].add(inputList_[index2], getRandomNbr(minRdm_, maxRdm_));
        }
    }

    // Allocation for the output list
    for (size_t index {0}; index < out; ++index)
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
    for (size_t index1 {0}; index1 < localIndex; ++index1)
    {
        ++itNeuronList;
        ++itLayerList;
    }
    itNeuronList = neuronList_.emplace(itNeuronList);
    itLayerList = layerList_.insert(itLayerList, nbNeuron);
    ++nbLayer_;

    // Create each neurons in the layer
    for (size_t index1 {0}; index1 < nbNeuron; ++index1)
    {
        itNeuronList->emplace_back(weightedSum, sigmoid, dSigmoid, getRandomNbr(minRdm_, maxRdm_));
    }
    
    // Set the link between entry
    if (itLayerList == layerList_.begin())
    {
        // For the first layer
        for (size_t index1 {0}; index1 < *itLayerList; ++index1)
        {   
            for (size_t index2 {0}; index2 < in; ++index2)
            {
                itNeuronList->at(index1).add(inputList_[index2], getRandomNbr(minRdm_, maxRdm_));
            }
        }
    }
    else
    {
        for (size_t index1 {0}; index1 < *itLayerList; ++index1)
        {   
            for (size_t index2 {0}; index2 < *std::prev(itLayerList, 1); ++index2)
            {
                itNeuronList->at(index1).add(prev(itNeuronList, 1)->at(index2).getOutput(), getRandomNbr(minRdm_, maxRdm_));
            }
        }
    }
    
    // Set the link with the outputs
    for (size_t index1 {0}; index1 < *std::next(itLayerList, 1); ++index1)
    {   
        std::next(itNeuronList, 1)->at(index1).clear();
        for (size_t index2 {0}; index2 < *itLayerList; ++index2)
        {
            std::next(itNeuronList, 1)->at(index1).add(itNeuronList->at(index2).getOutput(), getRandomNbr(minRdm_, maxRdm_));
        }
    }
}