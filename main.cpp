#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits> // For std::numeric_limits

#include "Activation.h"
#include "Neuron.h"
#include "Layer.h"
#include "NeuralNetwork.h"
#include "utils.h"

// --- Main Interactive Program ---
int main() {
    try {
        std::cout << "=== Multi-Layer Network Builder (C++) ===" << std::endl;
        std::cout << "Let's build the network, layer by layer." << std::endl;
        std::cout << "------------------------------------------" << std::endl;

        NeuralNetwork my_network;
        int num_network_inputs = 0;

        // 1. Get number of initial inputs (features)
        std::cout << "How many features will your initial input data have? (e.g., 2 for [x1, x2]): ";
        if (!(std::cin >> num_network_inputs) || num_network_inputs <= 0) {
            throw std::runtime_error("Invalid number of inputs.");
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
        
        int inputs_for_this_layer = num_network_inputs;

        // 2. Get number of layers
        int num_layers;
        std::cout << "How many layers do you want to build (e.g., 2 for 1 hidden + 1 output): ";
        if (!(std::cin >> num_layers) || num_layers <= 0) {
            throw std::runtime_error("Invalid number of layers.");
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

        // 3. Loop and build each layer
        for (int i = 0; i < num_layers; ++i) {
            std::cout << "\n--- Configuring Layer " << (i + 1) << " ---" << std::endl;

            // Get activation function for this layer
            std::string func_name;
            std::cout << "Activation for Layer " << (i + 1) << " (STEP, SIGMOID, RELU, TANH): ";
            std::getline(std::cin, func_name);
            Layer current_layer(string_to_activation(func_name));

            // Get number of neurons for this layer
            int num_neurons;
            std::cout << "How many neurons in Layer " << (i + 1) << "?: ";
            if (!(std::cin >> num_neurons) || num_neurons <= 0) {
                throw std::runtime_error("Invalid number of neurons.");
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

            // 4. Loop and build each neuron
            for (int j = 0; j < num_neurons; ++j) {
                std::cout << "\n  Configuring Neuron " << (j + 1) << " (Layer " << (i+1) << ")" << std::endl;
                std::cout << "  (This neuron must have " << inputs_for_this_layer << " weights)" << std::endl;

                // Get weights
                std::vector<double> weights = read_vector_input("  Enter weights");
                if (weights.size() != inputs_for_this_layer) {
                    throw std::invalid_argument("Weight count mismatch. Expected " 
                        + std::to_string(inputs_for_this_layer) + ", but got " + std::to_string(weights.size()));
                }

                // Get bias
                double bias;
                std::cout << "  Enter bias: ";
                if (!(std::cin >> bias)) {
                    throw std::runtime_error("Invalid bias input.");
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

                // Add the configured neuron to the layer
                current_layer.add_neuron(Neuron(weights, bias));
            }

            // Add the configured layer to the network
            my_network.add_layer(current_layer);
            std::cout << "\nLayer " << (i + 1) << " with " << num_neurons << " neurons added." << std::endl;
            std::cout << "------------------------------------------" << std::endl;

            // The number of outputs from this layer is the number of inputs for the *next* layer
            inputs_for_this_layer = num_neurons;
        }
        
        std::cout << "Network construction complete!" << std::endl;

        // 5. Get Input Data and Run Prediction
        std::cout << "\n--- Running Prediction ---" << std::endl;
        std::cout << "Enter the initial input vector for the network." << std::endl;
        std::cout << "(Must have " << num_network_inputs << " values)" << std::endl;
        
        std::vector<double> input_data = read_vector_input("Input data");

        // 6. Validate Input Size
        if (input_data.size() != num_network_inputs) {
             throw std::invalid_argument("Input size (" + std::to_string(input_data.size()) + 
                                       ") must match the network's expected input size (" + std::to_string(num_network_inputs) + ").");
        }
        
        // 7. Compute and print the final output
        std::vector<double> output = my_network.predict(input_data);
        
        std::cout << "\n--- FINAL NETWORK OUTPUT ---" << std::endl;
        print_vector("Output: ", output);

    } catch (const std::exception& e) {
        std::cerr << "\nFATAL ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}