//
// Created by pavel on 23.11.18.
//

#ifndef IMPLEMENTATION_BATCH_NORM_H
#define IMPLEMENTATION_BATCH_NORM_H

#include <cmath>
#include <iostream>

double math_expectatinon(double* set, int shape){
    double sum = 0.;
    for(int i=0; i<shape; i++)
        sum += set[i];
    return sum/(shape);
}

double math_variance(double* set, int shape) {
    double E_x = math_expectatinon(set, shape);
    double variance = 0.;
    for(int i=0; i<shape; i++){
        variance+=pow((set[i] - E_x),2);
    }
    variance =variance / shape;
    return variance;
}

double* batch_norm(double* input, int shape) {
    double E_x = math_expectatinon(input, shape);
    double D_x = math_variance(input, shape);
    double* result = new double[shape];
    for(int i=0; i<shape; i++) {
        result[i] = (input[i] - E_x)/ (pow(D_x, 0.5));
    }

    bool informative_output_message = false;
    if (informative_output_message) {
            std::cout << "set {";
            for (int i=0; i<shape; i++){
                std::cout << input[i] << ", ";
            }
            std::cout << "}" << std::endl;
            std::cout << "shape = " << shape << std::endl;
            std::cout << "E_x = " << E_x  << std::endl;
            std::cout << "D_x = " << D_x << std::endl;
    }

    return result;
}

#endif //IMPLEMENTATION_BATCH_NORM_H
