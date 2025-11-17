#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

// Helper function to read a vector of doubles from user input
std::vector<double> read_vector_input(const std::string& prompt);

// Helper function to print a vector
void print_vector(const std::string& title, const std::vector<double>& vec);