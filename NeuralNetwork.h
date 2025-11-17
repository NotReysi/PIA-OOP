#pragma once

#include <vector>
#include <stdexcept>
#include "Layer.h"

class NeuralNetwork {
private:
    std::vector<Layer> layers_;

public:
    // Constructor
    NeuralNetwork();

    // Adds a new layer to the network
    void add_layer(const Layer& layer);

    // Implements forward propagation through the entire network
    std::vector<double> predict(std::vector<double> inputs) const;
};