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

template <size_t in, size_t out>
Perceptron<in, out>::Perceptron()
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
        neuronList_.back().emplace_back(weightedSum, sigmoid, 0);
    }

    // Set the link between entry
    for (int index1 {0}; index1 < out; ++index1)
    {   
        for (int index2 {0}; index2 < in; ++index2)
        {
            neuronList_[0][index1].add(inputList_[index2], 1);
        }
    }

    // Allocation for the output list
    for (int index {0}; index < out; ++index)
    {
        outputList_.push_back(neuronList_[0][index].getOutput());
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
    for (int index {0}; index < localIndex; ++index)
    {
        ++itNeuronList;
        ++itLayerList;
    }
    itNeuronList = neuronList_.emplace(itNeuronList);
    itLayerList = layerList_.insert(itLayerList, nbNeuron);

    // Create each neurons in the layer
    for (int index {0}; index < nbNeuron; ++index)
    {
        itNeuronList->emplace_back(weightedSum, sigmoid, 0);
    }

    // Set the link between entry
    if (itLayerList == layerList_.begin())
    {
        // For the first layer
        for (int index1 {0}; index1 < *itLayerList; ++index1)
        {   
            for (int index2 {0}; index2 < in; ++index2)
            {
                itNeuronList->at(index1).add(inputList_[index2], 1);
            }
        }
    }
    else
    {
        for (int index1 {0}; index1 < *itLayerList; ++index1)
        {   
            for (int index2 {0}; index2 < *std::prev(itLayerList, 1); ++index2)
            {
                itNeuronList->at(index1).add(itNeuronList->at(index2).getOutput());
            }
        }
    }

    // Set the link with the outputs
    for (int index1 {0}; index1 < *std::next(itLayerList, 1); ++index1)
    {   
        itNeuronList->at(index1).clear();
        for (int index2 {0}; index2 < *itLayerList; ++index2)
        {
            itNeuronList->at(index1).add(itNeuronList->at(index2).getOutput());
        }
    }

    this->run();
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

#endif // PERCEPTRON_HPP