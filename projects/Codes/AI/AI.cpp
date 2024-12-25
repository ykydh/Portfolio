#include<iostream>
#include<random>
#include<iomanip>

#include "AI.h"

double** create_X(int numElems,int numSets)
{
    double input;
    double **X = new double*[numSets];

    for(int i = 0;i < numSets; i++)
    {
        X[i] = new double[numElems];
    }

    for(int i = 0; i < numSets; i++)
    {
        for(int j = 0; j < numElems; j++)
        {
            std::cin>>input;
            X[i][j] = input;
        }
    }

    return X;
}


void print_X(double **x,int elements,int sets)
{
    int count=0;
    for(int i = 0; i < sets; i++)
    {
        count = 0;
        std::cout <<"[";
        for(int j = 0; j < elements; j++)
        {
            std::cout<<x[i][j];
            if(count < 3)
            {
                std:: cout << ", ";
            }
            count++;
        }
        std::cout<<"]"<<std::endl;
        
    }
    return;
}

std::vector<std::vector<double> > Product(std::vector<std::vector<double> > input,std::vector<std::vector<double> > weights) 
{
    int input_rows = input.size();
    int input_cols = input[0].size();
    int weights_cols = weights[0].size();

    // Validate dimensions
    if (input_cols != weights.size()) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");
    }

    // Initialize the product matrix with appropriate dimensions
    std::vector<std::vector<double> > product(input_rows, std::vector<double>(weights_cols, 0.0));

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


//followings are member functions 
// LayerDense(int n_inputs, int n_neurons) {
//     this->n_inputs = n_inputs;
//     this->n_neurons = n_neurons;

//     // Initialize weights
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::normal_distribution<> dist(0.0, 1.0);

//     weights = std::vector<std::vector<double> >(n_inputs, std::vector<double>(n_neurons, 0.0));
//     for (int i = 0; i < n_inputs; i++) {
//         for (int j = 0; j < n_neurons; j++) {
//             weights[i][j] = 0.1 * dist(gen);
//         }
//     }

//     // Initialize biases
//     biases = std::vector<double>(n_neurons, 0.0);
// }

std::vector<std::vector<double> > LayerDense::forward(std::vector<std::vector<double> > input)
{
    std::vector<std::vector<double> > output;
    output = Product(input,weights);
    return output;
}

void printMatrix(std::vector<std::vector<double> > matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();

    if(rows <= 0)
        throw std::out_of_range("No elements in the passed matrix");

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            std::cout<<std::setprecision(3)<<matrix[i][j]<<"  ";
        }
        std::cout<<"\n";
    }
}

void delete_X(double ** X,int set)
{
    for(int i = 0; i < set;i++)
    {
        delete[] X[i];
    }
    delete[] X;
    return;
}




std::vector<std::vector<double> > convert(double ** X,int element,int set)
{
    std::vector<std::vector<double> > converted;
    std::vector<double> temp;
    for(int i = 0; i < set ;i++)
    {
        temp.clear();
        for(int j = 0; j < element;j++)
        {
            temp.push_back(X[i][j]);
        }
        converted.push_back(temp);
    }
    return converted;
}