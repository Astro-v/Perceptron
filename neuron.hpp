/**
 * @file neuron.hpp
 * @brief Implement the Neuron class
 * @author Valentin MICHEL
 * @date 09/10/2023
 * @note For naming rules follow https://manual.gromacs.org/5.1.1/dev-manual/naming.html
 */

/**
 * \brief Concept
*/
template <typename T>
concept iterable = requires (T x) { for (auto e: x) e; };

/**
 * @class Neuron
 * @brief Single neuron class
*/
class Neuron
{
private:
    /* data */
public:
    Neuron(auto (&fcomp)(iterable auto&));
    ~Neuron();
};
