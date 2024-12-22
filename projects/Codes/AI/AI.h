#ifndef AI_H
#define AI_H

#include<vector>
class LayerDense
{       
    public:
        double** initial();
        /*
        [1,2,3,4]
        [1,3,2,4]
        [4,21,4,54]
        n_inputs:4
        n_neurons:3
        */

        std::vector<std::vector<double>> forward(std::vector<std::vector<double>> input);
        

    private:
        std::vector<std::vector<double>> weight;
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
std::vector<std::vector<double>> Product(std::vector<std::vector<double>> input,std::vector<std::vector<double>>weights);

void printMatrix(std::vector<std::vector<double>> matrix);


#endif