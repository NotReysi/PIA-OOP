#pragma once

#include <string>
#include <stdexcept>
#include <algorithm> // For std::transform
#include <cctype>    // For ::toupper

// Enumeration for supported activation functions
enum class ActivationFunction {
    STEP,
    SIGMOID,
    RELU,
    TANH
};

// Function to convert a string to the ActivationFunction enum
ActivationFunction string_to_activation(const std::string& func_name);

// Function to convert the enum back to a string for display
std::string activation_to_string(ActivationFunction func);