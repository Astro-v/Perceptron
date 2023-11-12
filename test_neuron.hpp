#include "neuron.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

// Test case for the constructor and getters
void test_constructor_and_getters() {
    // Create a neuron with a net input function that sums the inputs and a sigmoid activation function
    Neuron n([](const std::vector<std::shared_ptr<double>>& inputs, const std::vector<std::shared_ptr<double>>& weights, const size_t& numInputs) {
        double netInput = 0;
        for (size_t i = 0; i < numInputs; i++) {
            netInput += *inputs[i] * *weights[i];
        }
        return netInput;
    }, [](const double& netInput) {
        return 1 / (1 + exp(-netInput));
    }, [](const double& netInput) {
        double activation = 1 / (1 + exp(-netInput));
        return activation * (1 - activation);
    });

    // Test that the input and weight vectors are empty
    assert(n.getInputNbr() == 0);
    assert(n.getOutputValue() == 0);
    assert(n.getWeight(0) == 0);
    assert(n.getInputValue(0) == 0);

    // Add an input and weight to the neuron
    std::shared_ptr<double> input1 = std::make_shared<double>(1);
    n.add(input1, 0.5);

    // Test that the input and weight vectors have size 1
    assert(n.getInputNbr() == 1);
    assert(n.getWeight(0) == 0.5);
    assert(n.getInputValue(0) == 1);

    // Add another input and weight to the neuron
    std::shared_ptr<double> input2 = std::make_shared<double>(2);
    n.add(input2, -0.5);

    // Test that the input and weight vectors have size 2
    assert(n.getInputNbr() == 2);
    assert(n.getWeight(1) == -0.5);
    assert(n.getInputValue(1) == 2);
}

// Test case for the run method
void test_run() {
    // Create a neuron with a net input function that sums the inputs and a sigmoid activation function
    Neuron n([](const std::vector<std::shared_ptr<double>>& inputs, const std::vector<std::shared_ptr<double>>& weights, const size_t& numInputs) {
        double netInput = 0;
        for (size_t i = 0; i < numInputs; i++) {
            netInput += *inputs[i] * *weights[i];
        }
        return netInput;
    }, [](const double& netInput) {
        return 1 / (1 + exp(-netInput));
    }, [](const double& netInput) {
        double activation = 1 / (1 + exp(-netInput));
        return activation * (1 - activation);
    });

    // Add two inputs and weights to the neuron
    std::shared_ptr<double> input1 = std::make_shared<double>(1);
    std::shared_ptr<double> input2 = std::make_shared<double>(2);
    n.add(input1, 0.5);
    n.add(input2, -0.5);

    // Run the neuron and test that the output is correct
    n.run();
    assert(fabs(n.getOutputValue() - 0.268941) < 0.0001);
}

// Test case for the setWeight method
void test_set_weight() {
    // Create a neuron with a net input function that sums the inputs and a sigmoid activation function
    Neuron n([](const std::vector<std::shared_ptr<double>>& inputs, const std::vector<std::shared_ptr<double>>& weights, const size_t& numInputs) {
        double netInput = 0;
        for (size_t i = 0; i < numInputs; i++) {
            netInput += *inputs[i] * *weights[i];
        }
        return netInput;
    }, [](const double& netInput) {
        return 1 / (1 + exp(-netInput));
    }, [](const double& netInput) {
        double activation = 1 / (1 + exp(-netInput));
        return activation * (1 - activation);
    });

    // Add two inputs and weights to the neuron
    std::shared_ptr<double> input1 = std::make_shared<double>(1);
    std::shared_ptr<double> input2 = std::make_shared<double>(2);
    n.add(input1, 0.5);
    n.add(input2, -0.5);

    // Set the weight of the second input
    n.setWeight(1, -1);

    // Test that the weight was set correctly
    assert(n.getWeight(1) == -1);
}

// Test case for the setBias method
void test_set_bias() {
    // Create a neuron with a net input function that sums the inputs and a sigmoid activation function
    Neuron n([](const std::vector<std::shared_ptr<double>>& inputs, const std::vector<std::shared_ptr<double>>& weights, const size_t& numInputs) {
        double netInput = 0;
        for (size_t i = 0; i < numInputs; i++) {
            netInput += *inputs[i] * *weights[i];
        }
        return netInput;
    }, [](const double& netInput) {
        return 1 / (1 + exp(-netInput));
    }, [](const double& netInput) {
        double activation = 1 / (1 + exp(-netInput));
        return activation * (1 - activation);
    });

    // Add two inputs and weights to the neuron
    std::shared_ptr<double> input1 = std::make_shared<double>(1);
    std::shared_ptr<double> input2 = std::make_shared<double>(2);
    n.add(input1, 0.5);
    n.add(input2, -0.5);

    // Set the bias weight of the neuron
    n.setBias(0.5);

    // Test that the bias weight was set correctly
    assert(n.getWeight(2) == 0.5);
}

// Test case for the clear method
void test_clear() {
    // Create a neuron with a net input function that sums the inputs and a sigmoid activation function
    Neuron n([](const std::vector<std::shared_ptr<double>>& inputs, const std::vector<std::shared_ptr<double>>& weights, const size_t& numInputs) {
        double netInput = 0;
        for (size_t i = 0; i < numInputs; i++) {
            netInput += *inputs[i] * *weights[i];
        }
        return netInput;
    }, [](const double& netInput) {
        return 1 / (1 + exp(-netInput));
    }, [](const double& netInput) {
        double activation = 1 / (1 + exp(-netInput));
        return activation * (1 - activation);
    });

    // Add two inputs and weights to the neuron
    std::shared_ptr<double> input1 = std::make_shared<double>(1);
    std::shared_ptr<double> input2 = std::make_shared<double>(2);
    n.add(input1, 0.5);
    n.add(input2, -0.5);

    // Run the neuron and test that the output is correct
    n.run();
    assert(fabs(n.getOutputValue() - 0.268941) < 0.0001);

    // Clear the neuron and test that the input and weight vectors are empty
    n.clear();
    assert(n.getInputNbr() == 0);
    assert(n.getOutputValue() == 0);
    assert(n.getWeight(0) == 0);
    assert(n.getInputValue(0) == 0);
}

// Test case for the getDerivativeOutput method
void test_get_derivative_output() {
    // Create a neuron with a net input function that sums the inputs and a sigmoid activation function
    Neuron n([](const std::vector<std::shared_ptr<double>>& inputs, const std::vector<std::shared_ptr<double>>& weights, const size_t& numInputs) {
        double netInput = 0;
        for (size_t i = 0; i < numInputs; i++) {
            netInput += *inputs[i] * *weights[i];
        }
        return netInput;
    }, [](const double& netInput) {
        return 1 / (1 + exp(-netInput));
    }, [](const double& netInput) {
        double activation = 1 / (1 + exp(-netInput));
        return activation * (1 - activation);
    });

    // Add two inputs and weights to the neuron
    std::shared_ptr<double> input1 = std::make_shared<double>(1);
    std::shared_ptr<double> input2 = std::make_shared<double>(2);
    n.add(input1, 0.5);
    n.add(input2, -0.5);

    // Run the neuron and test that the derivative of the output is correct
    n.run();
    assert(fabs(n.getDerivativeOutput() - 0.196612) < 0.0001);
}

int main() {
    test_constructor_and_getters();
    test_run();
    test_set_weight();
    test_set_bias();
    test_clear();
    test_get_derivative_output();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}