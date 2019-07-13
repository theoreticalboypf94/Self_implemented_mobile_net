//
// Created by pavel on 26.11.18.
//

#ifndef IMPLEMENTATION_SCALE_H
#define IMPLEMENTATION_SCALE_H

double* scale(double* input, double* weights, double* bias, int chanals = 1) {
    double *result = new double[chanals];
    for(int i=0; i<chanals; i++) {
        result[i] = input[i] * weights[i] + bias[i];
    }
    return result;
}

#endif //IMPLEMENTATION_SCALE_H
