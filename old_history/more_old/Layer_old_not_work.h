//
// Created by pavel on 28.11.18.
//

#ifndef IMPLEMENTATION_LAYER_H
#define IMPLEMENTATION_LAYER_H

#include "first_step_test_of_functions.cpp"
#include "read_from_text.h"


/*
 * double** depthwise_convolution(double** input,double** weights ,
 *                                const int height_t = 100, const int width_t = 100,
 *                                const int height_f = 3, const int width_f = 3, int stride=1)
 *
 *
 * template<int i, int j, int k, int l>
 * void rff(std::string path, double result[i][j][k][l])
 *
 * double** depthwise_convolution(double** input,double** weights ,
        const int height_t = 100, const int width_t = 100,
        const int height_f = 3, const int width_f = 3, int stride=1)
 */

template<int tensor_1, int tensor_2, int img_1, int img_2, int res_1, int res_2>
void init_pointers(double**result, double **input_img, double **weights){
    weights = new double* [tensor_1];
    for (int i=0; i<tensor_1; i++)
        weights[i] = new double[tensor_2];
    input_img = new double* [img_1];
    for (int i=0; i<img_1; i++)
        input_img[i] = new double[img_2];
    result = new double* [res_1];
    for (int i=0; i<res_1; i++)
        result[i] = new double[res_2];
}

template<int input_i, int input_j, int input_k, int input_l, int stride ,int conv_tensor_shape_0
        ,int conv_tensor_shape_1, int conv_tensor_shape_2, int conv_tensor_shape_3>                      //banch chanall stroka stolbec
void LAYER(std::string path_conv, std::string path_scale_weights, std::string path_scale_bias, int scale_weights_shape,
           double input[input_i][input_j][input_k][input_l],
           double output[conv_tensor_shape_0][conv_tensor_shape_1/input_j][input_k/stride][input_l/stride]) {      //TODO изменить выходной массив должным образом
    //NB!!!!!!!!!!!!!!!
    // я не выдержал терминалогию тут тензор это фильтр а картинка (img) это тензор
    //плюс к тому тут выходной файл будет того же размера что и входной - часть данных просто не будет изменена

    //_______________________________________________________________________
    //
    //________________________________CONVOLUTION____________________________
    //
    //_______________________________________________________________________
    double conv_matrix[conv_tensor_shape_0][conv_tensor_shape_1][conv_tensor_shape_2][conv_tensor_shape_3];
    rff<conv_tensor_shape_0,conv_tensor_shape_1,conv_tensor_shape_2,conv_tensor_shape_3>(path_conv, conv_matrix);
    double **result, **input_img, **weights, after_loop_result[input_k/stride][input_l/stride] = {0}; //
    init_pointers<conv_tensor_shape_2, conv_tensor_shape_3, input_k, input_l, input_k/stride, input_l/stride>(result, input_img, weights);//God forgive me for this shit
    //теперь у меня есть result, input_img, weights                           (фильтр, изображение, результат)
    if (input_j == conv_tensor_shape_1){
        for (int i=0; i<conv_tensor_shape_0; i++) {         //set of banch
            for (int j=0; j<conv_tensor_shape_1; j++) {       //set of channals
                //weight(filter) init
                for (int k=0; k<conv_tensor_shape_2; k++) {
                    for (int l=0; l<conv_tensor_shape_3; l++) {
                        weights[k][l] = conv_matrix[i][j][k][l];
                    }
                }
                //input(img) init
                for (int k=0; k<input_k; k++) {
                    for (int l=0; l<input_k; l++) {
                        input_img[k][l] = input[0][j][k][l];/////////TODO БИЛЯ
                    }
                }
                result = depthwise_convolution(input_img, weights,
                                               input_k, input_l,
                                               conv_tensor_shape_2,conv_tensor_shape_3, stride);
                for (int ii=0; ii<input_k/stride; ii++) {
                    for (int jj=0; jj<input_l/stride; jj++) {
                        after_loop_result[ii][jj] += result[ii][jj];
                    }
                }
                for (int k=0; k<input_k/stride; k++) {
                    for (int l=0; l<input_l/stride; l++) {
                        output[i][j][k][l] = after_loop_result[k][l];
                    }
                }
            }
        }


    }
    else {
        // пока оставлю так как есть много еще проблем
    }
}

double input[1][3][224][224];
double pic[3][224][224];
double output[32][1][224][224];
int function_LAYER_test() {

    std::cout << "*****";

    read_picture<3,224,224>("../input/input_image.txt", pic);
    for (int i=0; i<3; i++) {
        for (int j=0; j<224; j++) {
            for (int k=0; k<224; k++) {
                input[0][i][j][k] = pic[i][j][k];
            }

        }
    }

    LAYER<1,3, 224, 224, 1, 32, 3, 3, 3>("python-nn-parser/TXT/conv-0.txt","NONE", "NONE", 333, input, output);


    return 0;
}
#endif //IMPLEMENTATION_LAYER_H