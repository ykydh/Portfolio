#include "AI.h" // Assume this contains the LayerDense class definition and necessary headers
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

int main() {
  // Number of rows (data points) and columns (features) for input X
  int set = 3;     // Number of rows (data points)
  int element = 4; // Number of columns (features)

  // Generate random input matrix X
  // double** X = create_X(element, set);  // Randomly generate a 3x4 input
  // matrix

  std::pair<std::vector<std::vector<double>>, std::vector<int>> result =
      create_data(100, set);
  std::vector<std::vector<double>> X = result.first;
  std::vector<int> y = result.second;

  // print_X(X);             // Print the input matrix
  std::vector<std::vector<double>> Layer_out;
  std::vector<std::vector<double>> Activation_out;
  // Initialize two layers
  LayerDense layer1(2, 5);
  Activation_Relu activation1;
  Layer_out = layer1.forward(X);
  Activation_out = activation1.forward(Layer_out);
  print_X(Activation_out);

  return 0;
}

// Convert X to std::vector<std::vector<double>> for line 21;