//
// Created by pavel on 23.11.18.
//

#ifndef IMPLEMENTATION_FULLY_CONNECTED_H
#define IMPLEMENTATION_FULLY_CONNECTED_H
#define INPUT_SHAPE 1024

double* fully_connected(double* input, double* weight){
    double* result = new double[1000];   //TODO - переделать в матрицу.
    for(int i=0; i<1000; i++) {
        for(int j=0; i<INPUT_SHAPE; j++){
            result[i] = weight[j] * input[j];
        }
    }
    return result;
}
#endif //IMPLEMENTATION_FULLY_CONNECTED_H
