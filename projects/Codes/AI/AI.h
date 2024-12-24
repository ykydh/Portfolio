#ifndef AI_H
#define AI_H

#include<vector>
class LayerDense
{       
    public:
        LayerDense(int n_inputs, int n_neurons) {
        this->n_inputs = n_inputs;
        this->n_neurons = n_neurons;

        // Initialize weights
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> dist(0.0, 1.0);

        weights = std::vector<std::vector<double>>(n_inputs, std::vector<double>(n_neurons, 0.0));
        for (int i = 0; i < n_inputs; i++) {
            for (int j = 0; j < n_neurons; j++) {
                weights[i][j] = 0.1 * dist(gen);  // Randomly initialize weights scaled by 0.1
            }
        }

        // Initialize biases to 0 for each neuron
        biases = std::vector<double>(n_neurons, 0.0);
    }
        /*
        [1,2,3,4]
        [1,3,2,4]
        [4,21,4,54]
        n_inputs:4
        n_neurons:3
        */

        std::vector<std::vector<double> > forward(std::vector<std::vector<double> > input);
        

    private:
    std::vector<std::vector<double> > weights;
    std::vector<double> biases;
    int n_inputs;
    int n_neurons;
};

/*
[1,2,3,4]
[1,3,2,4]
[4,21,4,54]
numElems:4
numSets:3
*/
void delete_X(double  ** X,int set);

double** create_X(int numElems,int numSets);


void print_X(double **x,int elements,int sets);

//This function is trying to multiply matrixes, transpose have done in init function so just product
std::vector<std::vector<double> > Product(std::vector<std::vector<double> > input,std::vector<std::vector<double> >weights);

void printMatrix(std::vector<std::vector<double> > matrix);

std::vector<std::vector<double> > convert(double ** X,int element,int set);
#endif