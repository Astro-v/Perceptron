/**
 * @file neuron.hpp
 * @brief Implement the Neuron class
 * @author Valentin MICHEL
 * @date 09/10/2023
 * @note For naming rules follow https://manual.gromacs.org/5.1.1/dev-manual/naming.html
 */

#ifndef NEURON_HPP
#define NEURON_HPP

/**
 * @class Neuron
 * @brief Single neuron class
*/
class Neuron
{
private:
    NetInputFct netInputFct_;
    ActivationFct activationFct_;
    ActivationFct derivateActivationFct_;
    std::shared_ptr<double> output_;
    std::vector<std::shared_ptr<double>> input_;
    std::vector<std::shared_ptr<double>> weight_;
    size_t inputNbr_;

public:
    /**
     * @name Neuron
     * @brief Constructor for the Neuron class
     * @param netImputFct Net input function for the neuron
     * @param activationFct Activation fonction for the neuron
     * @param derivateActivationFct Derivate activation fonction for the neuron
     * @param weight Weight for the bias entry
     * @return No return
    */
    Neuron(NetInputFct netInputFct, ActivationFct activationFct, ActivationFct derivateActivationFct, const double& weight = 0);
    
    /**
     * @name ~Neuron
     * @brief Destructor for the Neuron class
     * @return No return
    */
    ~Neuron();

    /**
     * @name run
     * @brief Function that update the output value according to the inputs
     * @return No return
    */
    void run();

    /**
     * @name add
     * @brief Function that add a new input to the neuron
     * @param input Pointer over the input
     * @param weight Weight refering to the added input
     * @return No return
    */
    void add(std::shared_ptr<double> input, const double& weight);
    
    /**
     * @name clear
     * @brief Function that clear all added input
     * @return No return
    */
    void clear();

    /**
     * @name setWeight
     * @brief Accessor to set the weight
     * @param index Index of the relied input
     * @param weight Weight value
     * @return No return
    */
    void setWeight(const size_t& index, const double& weight);

    /**
     * @name setBias
     * @brief Accessor to set the bias weight
     * @param weight Weight value
     * @return No return
    */
    void setBias(const double& weight);

    /**
     * @name getOutput
     * @brief Accessor to get the output of the neuron
     * @return Pointer over the output value
    */
    std::shared_ptr<double> getOutput();

    /**
     * @name getOutputValue
     * @brief Accessor to get the output value of the neuron
     * @return Copy of the output value
    */
    double getOutputValue() const;

    /**
     * @name getInputValue
     * @brief Accessor to get the input of index value of the neuron
     * @return Copy of the input value
    */
    double getInputValue(const int& index) const;

    /**
     * @name getInputNbr
     * @brief Accessor to get the number of input for the neuron
     * @return The number of added input to the neuron
    */
    size_t getInputNbr() const;

    /**
     * @name getWeight
     * @brief Accessor to get the weight
     * @param index Index of the returned weight
     * @return The number of added input to the neuron
    */
    double getWeight(const int& index) const;

    /**
     * @name getDerivativeOutput
     * @brief Compute and return the derivate outpur
     * @return The output given by derivateActivation(netInput(input, weight))
    */
    double getDerivativeOutput() const;
};


#endif // NEURON_HPP