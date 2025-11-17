#include "utils.h"

// Helper function to read a vector of doubles from user input
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

// Helper function to print a vector
void print_vector(const std::string& title, const std::vector<double>& vec) {
    std::cout << title;
    if (vec.empty()) {
        std::cout << "[empty]" << std::endl;
        return;
    }
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i == vec.size() - 1 ? "" : ", ");
    }
    std::cout << std::endl;
}