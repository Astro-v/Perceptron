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
 * \brief typedef
*/
typedef double (&ActivationFct)(const double&);
typedef double (&NetInputFct)(std::vector<std::shared_ptr<double>>, const std::vector<double>);

/**
 * @class Neuron
 * @brief Single neuron class
*/
class Neuron
{
private:
    ActivationFct activationFct_;
    NetInputFct netInputFct_;
    std::shared_ptr<double> output_;
    std::vector<std::shared_ptr<double>> input_;
    std::vector<double> weight_;

public:
    Neuron(NetInputFct, ActivationFct);
    ~Neuron();
};


#endif // NEURON_HPP