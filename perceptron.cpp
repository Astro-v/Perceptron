/**
 * @file perceptron.cpp
 * @brief Perceptron file
 * @author Valentin MICHEL
 * @date 09/10/2023
 * @note For naming rules follow https://manual.gromacs.org/5.1.1/dev-manual/naming.html
 */

/**
 * @include External header
*/
#include <concepts>
#include <memory>
#include <vector>
#include <cmath>

/**
 * @include Internal header
*/
#include "resource.hpp"
#include "neuron.hpp"
#include "perceptron.hpp"

template<size_t in, size_t out>
Perceptron<in, out>::Perceptron()
{
    
}

template<size_t in, size_t out>
Perceptron<in, out>::Perceptron(std::vector<size_t> layerList):
nbLayer_(layerList.size()),
{

    if (nbLayer_ <= 0 || nbInput <= 0)
    {
        throw;
    }

    // Allocation for the entry list
    for (int index {0}; index < in; ++index)
    {
        inputList_.push_back(std::make_shared<double>(0));
    }

    // Creation of the neurons
    for (const auto& layerSize : layerList)
    {
        layerList_.push_back(layerSize);
        neuronList_.emplace_back();
        for (int index {0}; index < layerSize; ++index)
        {
            neuronList_.back().emplace_back(weightedSum, sigmoid, 0);
        }

        for (int index {0}; index < layerSize; ++index)
        {
            neuronList_.back().emplace_back(weightedSum, sigmoid, 0);
        }
    }

    // Creation of link between input and output
    for (int index1 {0}; index1 < layerList_[0]; ++index1)
    {
        for (int index2 {0}; index2 < in; ++index2)
        {
            neuronList_[0][index1].add(inputList_[index2], 1);
        }
    }

    for (int index1 {1}; index1 < nbLayer_; ++index1)
    {
        for (int index2 {0}; index2 < layerList_[index1]; ++index2)
        {
            for (int index3 {0}; index3 < layerList_[index1-1]; ++index3)
            {
                neuronList_[index1][index2].add(neuronList_[index1-1][index3].getOutput(), 1);
            }
        }
    }

    for (int index1 {0}; index1 < layerList_[0]; ++index1)
    {
        for (int index2 {0}; index2 < in; ++index2)
        {
            neuronList_[0][index1].add(inputList_[index2], 1);
        }
    }

    // Allocation for the output list
    for (int index {0}; index < layerList.back(); ++index)
    {
        outputList_.push_back(neuronList_.back().at(index).getOutput());
    }

    this->run();
}

template<size_t in, size_t out>
Perceptron<in, out>::~Perceptron()
{

}

template<size_t in, size_t out>
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

template<size_t in, size_t out>
double Perceptron<in, out>::getOutput(const int& index)
{
    if (index < 0 || index >= out)
    {
        throw;
    }

    return *outputList_[index];
}

template<size_t in, size_t out>
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