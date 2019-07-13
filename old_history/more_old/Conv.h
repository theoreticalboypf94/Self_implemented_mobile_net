//
// Created by pavel on 23.11.18.
//

#ifndef IMPLEMENTATION_CONV_H
#define IMPLEMENTATION_CONV_H
#include <iostream>

double** depthwise_convolution(double** input,double** weights ,
        const int height_t = 100, const int width_t = 100,
        const int height_f = 3, const int width_f = 3, int stride=1){
    /*
     * height_t, width_t - высота и ширина входного Тензора
     * height_f, width_f - высота и ширина Фильтра
     * stride - как следует из названия это шаг на который мы перемещаемся - конструкция выглядит так
     *         x|0|x
     *         0|0|0
     *         x|0|x - где х - означает центр фильтр-матрицы
     *
     */
    //first of all we need to extended our matrix - add one or two lines (one) for 3x3 conv filter

    // формируюем расширенную матрицу
    double extended[height_t+2][width_t+2];
    for(int i=0; i<height_t+2; i++){
        for(int j=0; j<width_t+2; j++){
            if (i==0 || j==0 || i==height_t+1 || j==width_t+1) {
                extended[i][j] = 0;
            }
            else{
                extended[i][j] = input[i-1][j-1];
            }
        }
    }

    //create two dimensional output array
    double **result ;
    result = new double*[height_t/stride];
    for(int i=0; i<height_t/stride; i++){
        result[i] = new double[width_t/stride];
    }
    int result_i = 0, result_j = 0; //внутренние индексы выходного массива которые будут инкрементированы сепаратно
    // без превлечения дополнительных конструкций в виде вложенных циклов.

    double local_conv = 0.; // переменная хранящая результат локальной конвольции 3х3 на 3х3
    for (int i=0; i+stride<=height_t; i+=stride) {
        for (int j=0; j+stride<=width_t; j+=stride) {
            // положение левого верхнего конца сверточного фильтра

            // операция свертки имплементирована внизу

            for (int k=0; k<height_f; k++) {
                for (int l=0; l<width_f; l++) {
                    local_conv += extended[i+k][j+l] * weights[k][l];
                }
            }
            result[result_i][result_j] = local_conv;
            result_i += 1;
            local_conv = 0.;
        }
        result_j += 1;              //чтобы не было выхода за пределы массива
        result_i = 0;
    }
    //convolution
    return result;
}

#endif //IMPLEMENTATION_CONV_H
