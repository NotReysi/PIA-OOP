#include "Layer.h"

// Constructor
Layer::Layer(ActivationFunction func) : activation_(func) {}

// Adds a fully configured neuron to this layer
void Layer::add_neuron(const Neuron& neuron) {
    neurons_.push_back(neuron);
}

// Performs the feed-forward operation for this entire layer
std::vector<double> Layer::feed_forward(const std::vector<double>& inputs) const {
    std::vector<double> layer_outputs;
    layer_outputs.reserve(neurons_.size());

    for (const auto& neuron : neurons_) {
        // 1. Calculate weighted sum + bias
        double net_input = neuron.calculate_output(inputs);
        // 2. Apply this layer's activation function
        double activated_output = apply_activation(net_input);
        // 3. Add to the output list
        layer_outputs.push_back(activated_output);
    }
    return layer_outputs;
}

// Getter for neuron count
size_t Layer::get_neuron_count() const {
    return neurons_.size();
}

// --- Private Activation Methods ---

double Layer::step_function(double sum) const { 
    return (sum >= 0.0) ? 1.0 : 0.0; 
}
double Layer::sigmoid_function(double sum) const { 
    return 1.0 / (1.0 + std::exp(-sum)); 
}
double Layer::relu_function(double sum) const { 
    return std::max(0.0, sum); 
}
double Layer::tanh_function(double sum) const { 
    return std::tanh(sum); 
}

// Applies the layer's activation function
double Layer::apply_activation(double sum) const {
    switch (activation_) {
        case ActivationFunction::STEP: return step_function(sum);
        case ActivationFunction::SIGMOID: return sigmoid_function(sum);
        case ActivationFunction::RELU: return relu_function(sum);
        case ActivationFunction::TANH: return tanh_function(sum);
        default: throw std::runtime_error("Unknown activation function selected.");
    }
}