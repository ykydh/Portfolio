#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

#include "AI.h"

double **create_X(int numElems, int numSets) {
  double input;
  double **X = new double *[numSets];

  for (int i = 0; i < numSets; i++) {
    X[i] = new double[numElems];
  }

  for (int i = 0; i < numSets; i++) {
    for (int j = 0; j < numElems; j++) {
      std::cin >> input;
      X[i][j] = input;
    }
  }

  return X;
}

void print_X(std::vector<std::vector<double> > x) {
  int count = 0;
  for (int i = 0; i < x.size(); i++) {
    count = 0;
    std::cout << "[";
    for (int j = 0; j < x[0].size(); j++) {
      std::cout << x[i][j];
      if (count < 3) {
        std::cout << ", ";
      }
      count++;
    }
    std::cout << "]" << std::endl;
  }
  return;
}

std::vector<std::vector<double> >
Product(std::vector<std::vector<double> > input,
        std::vector<std::vector<double> > weights) {
  int input_rows = input.size();
  int input_cols = input[0].size();
  int weights_cols = weights[0].size();

  // Validate dimensions
  if (input_cols != weights.size()) {
    throw std::invalid_argument(
        "Matrix dimensions do not match for multiplication");
  }

  // Initialize the product matrix with appropriate dimensions
  std::vector<std::vector<double> > product(
      input_rows, std::vector<double>(weights_cols, 0.0));

  // Perform matrix multiplication
  for (int i = 0; i < input_rows; ++i) {
    for (int j = 0; j < weights_cols; ++j) {
      double temp = 0.0;
      for (int k = 0; k < input_cols; ++k) {
        temp += input[i][k] * weights[k][j];
      }
      product[i][j] = temp;
    }
  }

  return product;
}

std::vector<std::vector<double> >
LayerDense::forward(std::vector<std::vector<double> > input) {
  std::vector<std::vector<double> > output;
  output = Product(input, weights);
  return output;
}

void printMatrix(std::vector<std::vector<double> > matrix) {
  int rows = matrix.size();
  int cols = matrix[0].size();

  if (rows <= 0)
    throw std::out_of_range("No elements in the passed matrix");

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout << std::setprecision(3) << matrix[i][j] << "  ";
    }
    std::cout << "\n";
  }
}

std::vector<std::vector<double> >
Activation_Relu::forward(std::vector<std::vector<double> > input) {
  if (input.size() < 1)
    throw std::invalid_argument("No value in the input vector");
  int rows = input.size();
  int cols = input[0].size();
  std::vector<std::vector<double> > output(rows, std::vector<double>(cols, 0));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (input[i][j] <= 0)
        output[i][j] = 0;
      else
        output[i][j] = input[i][j];
    }
  }
  return output;
}

std::vector<double> Activation_Softmax::forward(std::vector<double> input) {
  // Find the maximum value for numerical stability
  double max = *std::max_element(input.begin(), input.end());

  // Exponentiate the shifted values
  std::vector<double> temp(input.size());
  for (size_t i = 0; i < input.size(); ++i) {
    temp[i] = std::exp(input[i] - max);
  }

  // Calculate the sum of all exponentials
  double sum = std::accumulate(temp.begin(), temp.end(), 0.0);

  // Normalize to create probabilities
  std::vector<double> output(input.size());
  for (size_t i = 0; i < temp.size(); ++i) {
    output[i] = temp[i] / sum;
  }

  return output;
}

void delete_X(double **X, int set) {
  for (int i = 0; i < set; i++) {
    delete[] X[i];
  }
  delete[] X;
  return;
}

std::vector<std::vector<double> > convert(double **X, int element, int set) {
  std::vector<std::vector<double> > converted;
  std::vector<double> temp;
  for (int i = 0; i < set; i++) {
    temp.clear();
    for (int j = 0; j < element; j++) {
      temp.push_back(X[i][j]);
    }
    converted.push_back(temp);
  }
  return converted;
}

std::pair<std::vector<std::vector<double> >, std::vector<int> >
create_data(int points, int classes) {
  std::vector<std::vector<double> > X(points * classes, std::vector<double>(2));
  std::vector<int> y(points * classes);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> noise(
      0, 0.2); // Random noise with mean 0 and std deviation 0.2

  for (int class_number = 0; class_number < classes; ++class_number) {
    for (int i = 0; i < points; ++i) {
      int index = points * class_number + i;

      // Radius
      double r = static_cast<double>(i) / points;

      // Angle with some added noise
      double t = class_number * 4 + 4.0 * i / points + noise(gen);

      // Coordinates
      X[index][0] = r * sin(t * 2.5);
      X[index][1] = r * cos(t * 2.5);

      // Class label
      y[index] = class_number;
    }
  }

  return std::make_pair(X, y); // Correct way to create and return a pair
  
}
