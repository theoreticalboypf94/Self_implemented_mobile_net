//
// Created by pavel on 23.11.18.
//

#ifndef IMPLEMENTATION_SOFT_MAX_H
#define IMPLEMENTATION_SOFT_MAX_H
#include <cmath>

double* soft_max(double* input, int shape ) {
    /*
     * Thsi function serves to realize soft_max function
     * soft_max = exp(a_i) / \Sigma_j { exp(a_j)}
     * input - input array of double
     * shape - amount of independent spaces
     */
    double *output= new double[shape];
    double denomenator =0.;
    for(int i=0; i<shape; i++)
        denomenator+=exp(input[i]);
    for(int i=0; i<shape; i++)
        output[i] = exp(input[i]) / denomenator;

    return output;
}




#endif //IMPLEMENTATION_SOFT_MAX_H
