#include "NeuralNetwork.h"

// Constructor
NeuralNetwork::NeuralNetwork() {}

// Adds a new layer to the network
void NeuralNetwork::add_layer(const Layer& layer) {
    layers_.push_back(layer);
}

// Implements forward propagation through the entire network
std::vector<double> NeuralNetwork::predict(std::vector<double> inputs) const {
    if (layers_.empty()) {
        throw std::runtime_error("Network has no layers to predict with.");
    }

    // Sequentially pass the output of one layer as the input to the next
    for (const auto& layer : layers_) {
        inputs = layer.feed_forward(inputs);
    }
    
    // The final 'inputs' vector is the network's output
    return inputs;
}