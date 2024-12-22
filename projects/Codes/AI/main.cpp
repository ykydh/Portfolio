#include<iostream>
#include<cstdlib>
#include<vector>

#include "AI.h"
int main()
{
    /*
    std::vector <std::vector<double>> X ={{1, 2, 3, 2.5},
                                          {12.0, 5.0,-1.0, 2.0},
                                          {-1.5, 2.7, 3.3, -0.81}};
    */
    int set, element;

    double** X;

    set=3;
    element=4;
    X = create_X(element,set);
    print_X(X,element,set);

    //do not for get to delete
    delete_X(X,set);
    return 0;
}


//Thu Dec19 init finished
