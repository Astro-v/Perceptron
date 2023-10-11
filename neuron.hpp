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
template <typename Func, typename... Args>
concept CallableOnIterable = requires(Func func, Args... args) {
    { func({args...}, {args...}) } -> std::same_as<void>;
};

/**
 * @class Neuron
 * @brief Single neuron class
*/
class Neuron
{
private:
    /* data */
public:
    template <CallableOnIterable T>
    Neuron(T);
    ~Neuron();
};
