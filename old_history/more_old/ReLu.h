//
// Created by pavel on 23.11.18.
//

#ifndef IMPLEMENTATION_RELU_H
#define IMPLEMENTATION_RELU_H


double** relu(const int height, const int width, double** input) {
    double** result = new double*[height];
    for (int i=0; i<height; i++)
        result[i] = new double[width];

    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            result[i][j] = (input[i][j] > 0) ? input[i][j] : 0.;
        }
    }
    return result;
}


#endif //IMPLEMENTATION_RELU_H
