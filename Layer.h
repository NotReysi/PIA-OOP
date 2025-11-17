#pragma once

#include <vector>
#include <cmath>
#include <stdexcept>
#include "Neuron.h"
#include "Activation.h"

class Layer {
private:
    std::vector<Neuron> neurons_;
    ActivationFunction activation_;

    // Private Activation Methods
    double step_function(double sum) const;
    double sigmoid_function(double sum) const;
    double relu_function(double sum) const;
    double tanh_function(double sum) const;
    double apply_activation(double sum) const;

public:
    // Constructor
    Layer(ActivationFunction func);

    // Adds a fully configured neuron to this layer
    void add_neuron(const Neuron& neuron);

    // Performs the feed-forward operation for this entire layer
    std::vector<double> feed_forward(const std::vector<double>& inputs) const;

    // Getter to know how many neurons are in this layer
    size_t get_neuron_count() const;
};