#include "Activation.h"

ActivationFunction string_to_activation(const std::string& func_name) {
    // Create an uppercase version for case-insensitive comparison
    std::string upper_name = func_name;
    std::transform(upper_name.begin(), upper_name.end(), upper_name.begin(), ::toupper);

    if (upper_name == "STEP") return ActivationFunction::STEP;
    if (upper_name == "SIGMOID") return ActivationFunction::SIGMOID;
    if (upper_name == "RELU") return ActivationFunction::RELU;
    if (upper_name == "TANH") return ActivationFunction::TANH;
    throw std::invalid_argument("Invalid activation function name: " + func_name);
}

std::string activation_to_string(ActivationFunction func) {
    switch (func) {
        case ActivationFunction::STEP: return "STEP";
        case ActivationFunction::SIGMOID: return "SIGMOID";
        case ActivationFunction::RELU: return "RELU";
        case ActivationFunction::TANH: return "TANH";
        default: return "UNKNOWN";
    }
}