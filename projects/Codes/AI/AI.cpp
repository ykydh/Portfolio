#include<iostream>
#include<random>

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

std::vector<std::vector<double>> Product(std::vector<std::vector<double>> input,std::vector<std::vector<double>>weights)
{
    int input_rows = input.size();
    int input_cols = input[0].size();
    // int weights_rows = weights.size();
    int weights_cols = weights[0].size();
    
    std::vector<std::vector<double>> product;

    for(int i = 0; i< input_rows;i++)
    {
        for(int j = 0; j < weights_cols; j++)
        {
            double temp = 0.0;
            for(int k = 0; k < input_cols;k++)
            {
                temp += input[i][k] * weights[k][j];
            }
            product[i][j] = temp;
        }
        
    }
    return product;
}


//followings are member functions 
double** LayerDense::initial()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.0, 1.0);
    double ** weight = new double *[n_inputs];
    double * bias = new double [n_neurons];
    
    for(int k = 0;k<n_inputs;k++)
    {
        weight[k] = new double[n_neurons];
    }

    for(int i = 0; i < n_inputs;i++)
    {
        for(int j = 0; j < n_neurons;j++)
        {
            weight[i][j] = 0.1 * dist(gen);
        }
    }

    for(int l = 0; l < n_neurons;l++)
    {
        bias[l] = 0;
    }
}

std::vector<std::vector<double>> LayerDense::forward(std::vector<std::vector<double>> input)
{
    std::vector<std::vector<double>> output;
    output = Product(input,weight);
    return output;
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