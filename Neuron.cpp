#include "Neuron.h"

// Constructor
Neuron::Neuron(const std::vector<double>& weights, double bias)
    : weights_(weights), bias_(bias) 
{
    if (weights.empty()) {
        throw std::invalid_argument("Neuron weights vector cannot be empty.");
    }
}

// Calculates the weighted sum of inputs plus the bias
double Neuron::calculate_output(const std::vector<double>& inputs) const {
    if (inputs.size() != weights_.size()) {
        throw std::invalid_argument("Neuron input count (" + std::to_string(inputs.size()) 
            + ") must match weight count (" + std::to_string(weights_.size()) + ").");
    }

    double net_input = 0.0;
    for (size_t i = 0; i < inputs.size(); ++i) {
        net_input += inputs[i] * weights_[i];
    }
    net_input += bias_;
    return net_input;
}

// Getter for weight count
size_t Neuron::get_weight_count() const {
    return weights_.size();
}