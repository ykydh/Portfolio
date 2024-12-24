#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include "AI.h" // Assume this contains the LayerDense class definition and necessary headers

int main() {
    // Number of rows (data points) and columns (features) for input X
    int set = 3;        // Number of rows (data points)
    int element = 4;    // Number of columns (features)

    // Generate random input matrix X
    double** X = create_X(element, set);  // Randomly generate a 3x4 input matrix
    print_X(X, element, set);             // Print the input matrix

    // Initialize two layers
    LayerDense layer1(4, 5);              // 4 inputs, 5 neurons
    LayerDense layer2(5, 2);              // 5 inputs (from layer1), 2 neurons

    // Perform forward propagation through the layers
    auto output1 = layer1.forward(convert(X,element,set));                               // Forward pass through layer1
    std::cout << "Layer 1 Output:\n";
    printMatrix(output1);                                               // Print layer1 output

    auto output2 = layer2.forward(output1);                             // Forward pass through layer2
    std::cout << "Layer 2 Output:\n";
    printMatrix(output2);                                               // Print layer2 output

    // Clean up dynamically allocated memory for X
    delete_X(X, set);

    return 0;
}


//Convert X to std::vector<std::vector<double>> for line 21; 