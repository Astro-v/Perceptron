/**
 * @file neuron.cpp
 * @brief Neuron file
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
#include "resource.hpp"
#include "neuron.hpp"

Neuron::Neuron(NetInputFct netInputFct, ActivationFct activationFct, ActivationFct derivateActivationFct, const double& weight):
netInputFct_(netInputFct),
activationFct_(activationFct),
derivateActivationFct_(derivateActivationFct)
{
    output_ = std::make_shared<double>();

    // Bias weight
    weight_.push_back(std::make_shared<double>(weight));

    inputNbr_ = 0;
}

Neuron::~Neuron()
{
    
}

void Neuron::run()
{
    *output_ = activationFct_(netInputFct_(input_, weight_)); 
}

void Neuron::add(std::shared_ptr<double> input,  const double& weight)
{
    input_.push_back(input);
    weight_.insert(std::prev(weight_.end(), 1), std::make_shared<double>(weight));
    ++inputNbr_;
}

void Neuron::clear()
{
    input_.clear();
    weight_.erase(weight_.begin(), weight_.end() - 1);
    inputNbr_ = 1;
}

void Neuron::setWeight(const size_t& index, const double& weight)
{
    if (index >= 0 && index <= inputNbr_)
        *(weight_.at(index)) = weight;
}

void Neuron::setBias(const double& weight)
{
    *weight_.back() = weight;
}

std::shared_ptr<double> Neuron::getOutput()
{
    return output_;
}

double Neuron::getOutputValue() const
{
    return *output_;
}


double Neuron::getInputValue(const int& index) const
{
    if (index < 0 && index >= inputNbr_)
        throw;  
    return *input_[index];
}

size_t Neuron::getInputNbr() const
{
    return inputNbr_;
}

double Neuron::getWeight(const int& index) const
{
    if (index < 0 && index >= inputNbr_ + 1)
        throw;
    return *weight_.at(index);
}

double Neuron::getDerivativeOutput() const
{
    return derivateActivationFct_(netInputFct_(input_, weight_)); 
}