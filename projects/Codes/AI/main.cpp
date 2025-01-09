#include "AI.h" // Assume this contains LayerDense and activation class definitions
#include <iomanip>
#include <iostream>
#include <vector>
#include <utility> // For std::pair

int main() {
  // Number of rows (data points) and columns (features) for input X
  int set = 3;     // Number of rows (data points)
  int element = 4; // Number of columns (features)

  // Generate random input matrix X
  std::pair<std::vector<std::vector<double> >, std::vector<int> > result =
      create_data(100, set);
  std::vector<std::vector<double> > X = result.first;
  std::vector<int> y = result.second;

  // Initialize layers
  LayerDense Dense1(2, 3);
  Activation_Relu activation1;
  LayerDense Dense2(3, 3); // Input neurons = 3, Output neurons = 3
  Activation_Softmax activation2;

  // Forward pass
  std::vector<std::vector<double> > Layer_out1 = Dense1.forward(X);
  std::vector<std::vector<double> > Activation_out1 = activation1.forward(Layer_out1);

  std::vector<std::vector<double> > Layer_out2 = Dense2.forward(Activation_out1);

  // Apply softmax to each row of Layer_out2
  std::vector<std::vector<double> > Activation_out2;
  for (size_t i = 0; i < Layer_out2.size(); ++i) {
    Activation_out2.push_back(activation2.forward(Layer_out2[i]));
  }

  // Print the final output
  for (size_t i = 0; i < Activation_out2.size(); ++i) {
    for (size_t j = 0; j < Activation_out2[i].size(); ++j) {
      std::cout << std::fixed << std::setprecision(4) << Activation_out2[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
