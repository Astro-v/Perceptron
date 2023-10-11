/**
 * @file main.cpp
 * @brief Main file
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

/**
 * @include Internal header
*/
#include "neuron.hpp"

Neuron::Neuron(NetInputFct netInputFct, ActivationFct activationFct, const double& weight):
netInputFct_(netInputFct),
activationFct_(activationFct)
{
    output_ = std::make_shared<double>();

    // Bias weight
    weight_.push_back(weight);

    inputNbr_ = 0;
}

Neuron::~Neuron()
{
    *output_ = (netInputFct_(input_, weight_));
}

void Neuron::run()
{

}

void Neuron::add(std::shared_ptr<double> input, const double& weight)
{
    input_.push_back(input);
    weight_.insert(weight_.begin(), weight);
    ++inputNbr_;
}

void Neuron::setWeight(const size_t& index, const double& weight)
{
    if (index >= 0 && index < inputNbr_)
        weight_.at(index) = weight;
}

void Neuron::setBias(const double& weight)
{
    *(--weight_.end()) = weight;
}

std::shared_ptr<double> Neuron::getOutput()
{
    return output_;
}

size_t Neuron::getInputNbr() const
{
    return inputNbr_;
}