#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <string>

// Enumeration for supported activation functions
enum class ActivationFunction {
    STEP,
    SIGMOID,
    RELU,
    TANH
};

// Function to convert a string to the ActivationFunction enum
// Useful for user input handling
ActivationFunction string_to_activation(const std::string& func_name) {
    if (func_name == "STEP") return ActivationFunction::STEP;
    if (func_name == "SIGMOID") return ActivationFunction::SIGMOID;
    if (func_name == "RELU") return ActivationFunction::RELU;
    if (func_name == "TANH") return ActivationFunction::TANH;
    throw std::invalid_argument("Invalid activation function name.");
}

// Function to convert the enum back to a string for display
std::string activation_to_string(ActivationFunction func) {
    switch (func) {
        case ActivationFunction::STEP: return "STEP";
        case ActivationFunction::SIGMOID: return "SIGMOID";
        case ActivationFunction::RELU: return "RELU";
        case ActivationFunction::TANH: return "TANH";
        default: return "UNKNOWN";
    }
}

class Perceptron {
private:
    std::vector<double> weights_;
    double bias_;
    ActivationFunction current_function_;

    // --- Private Activation Methods (Implementation remains the same) ---
    double step_function(double sum) const { return (sum >= 0.0) ? 1.0 : 0.0; }
    double sigmoid_function(double sum) const { return 1.0 / (1.0 + std::exp(-sum)); }
    double relu_function(double sum) const { return std::max(0.0, sum); }
    double tanh_function(double sum) const { return std::tanh(sum); }

    double apply_activation(double sum) const {
        switch (current_function_) {
            case ActivationFunction::STEP: return step_function(sum);
            case ActivationFunction::SIGMOID: return sigmoid_function(sum);
            case ActivationFunction::RELU: return relu_function(sum);
            case ActivationFunction::TANH: return tanh_function(sum);
            default: throw std::runtime_error("Unknown activation function selected.");
        }
    }

public:
    // Constructor
    Perceptron(const std::vector<double>& weights, double bias, ActivationFunction func)
        : weights_(weights), bias_(bias), current_function_(func)
    {
        if (weights.empty()) {
            throw std::invalid_argument("Weights vector cannot be empty.");
        }
    }

    // Setter for Activation Function
    void set_activation_function(ActivationFunction func) {
        current_function_ = func;
    }

    // Getter for Activation Function (useful for displaying to the user)
    ActivationFunction get_activation_function() const {
        return current_function_;
    }

    // Core Computation Method (Implementation remains the same)
    double compute_output(const std::vector<double>& inputs) const {
        if (inputs.size() != weights_.size()) {
            throw std::invalid_argument("The number of inputs must match the number of weights.");
        }

        double net_input = 0.0;
        for (size_t i = 0; i < inputs.size(); ++i) {
            net_input += inputs[i] * weights_[i];
        }

        net_input += bias_;

        return apply_activation(net_input);
    }
};

// --- Helper function to read a vector of doubles from user input ---
std::vector<double> read_vector_input(const std::string& prompt) {
    std::vector<double> vec;
    std::string line;
    double value;

    std::cout << prompt << " (e.g., 0.5 -0.2 1.0): ";
    std::getline(std::cin, line);
    std::stringstream ss(line);

    while (ss >> value) {
        vec.push_back(value);
    }
    return vec;
}

// --- Main Interactive Program ---
int main() {
    try {
        std::cout << "=== Perceptron Simulator (C++) ===" << std::endl;
        
        // 1. Get Weights from User
        std::vector<double> initial_weights = read_vector_input("Enter initial weights, separated by spaces");
        if (initial_weights.empty()) {
            throw std::invalid_argument("Weights cannot be empty. Please restart and enter valid numbers.");
        }

        // 2. Get Bias from User
        double initial_bias;
        std::cout << "Enter the bias value: ";
        if (!(std::cin >> initial_bias)) {
            throw std::runtime_error("Invalid bias input.");
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
        
        // 3. Get Activation Function from User
        std::string func_name;
        std::cout << "\nEnter activation function (STEP, SIGMOID, RELU, TANH): ";
        std::getline(std::cin, func_name);
        // Convert to uppercase for case-insensitive check
        std::transform(func_name.begin(), func_name.end(), func_name.begin(), ::toupper);
        
        ActivationFunction initial_func = string_to_activation(func_name);

        // 4. Initialize Perceptron
        Perceptron my_perceptron(initial_weights, initial_bias, initial_func);
        std::cout << "\nPerceptron successfully initialized." << std::endl;
        std::cout << "-----------------------------------" << std::endl;

        // 5. Get Input Data from User
        std::vector<double> input_data = read_vector_input("Enter input data vector, separated by spaces");

        // 6. Validate Input Size
        if (input_data.size() != initial_weights.size()) {
             throw std::invalid_argument("Input size (" + std::to_string(input_data.size()) + 
                                         ") must match the number of weights (" + std::to_string(initial_weights.size()) + ").");
        }
        
        // 7. Compute and print the final output
        double output = my_perceptron.compute_output(input_data);
        
        std::cout << "\n--- COMPUTATION RESULT ---" << std::endl;
        std::cout << "Function Used: " << activation_to_string(my_perceptron.get_activation_function()) << std::endl;
        std::cout << "Final Output:  " << output << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "\nFATAL ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
