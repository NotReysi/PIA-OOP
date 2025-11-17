#pragma once

#include <vector>
#include <stdexcept>
#include <string>

class Neuron {
private:
    std::vector<double> weights_;
    double bias_;

public:
    // Constructor
    Neuron(const std::vector<double>& weights, double bias);

    // Calculates the weighted sum of inputs plus the bias (net input)
    double calculate_output(const std::vector<double>& inputs) const;

    // Getter to know how many inputs this neuron expects
    size_t get_weight_count() const;
};