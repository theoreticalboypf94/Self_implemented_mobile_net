//
// Created by pavel on 29.11.18.
//

#ifndef IMPLEMENTATION_LAYER_H
#define IMPLEMENTATION_LAYER_H

#include "AVG_pool.h"
#include "Batch norm.h"
#include "Conv.h"
#include "read_from_text.h"
#include "ReLu.h"
#include "Scale.h"
#include "Soft_max.h"
#include <iostream>
#include <string>

//закоментировано на время инклуда
int glob_counter_for_nan_test = 0;


template<int res_1, int res_2, int img_1, int img_2, int conv_1, int conv_2 >
inline void init_pointers(double**&result, double **&input_img, double **&weights){
        weights = new double* [conv_1];
        for (int i=0; i<conv_1; i++)
                weights[i] = new double[conv_2];
        input_img = new double* [img_1];
        for (int i=0; i<img_1; i++)
                input_img[i] = new double[img_2];
        result = new double* [res_1];
        for (int i=0; i<res_1; i++)
                result[i] = new double[res_2];
}
template<int res_1, int img_1, int conv_1>
inline void del_pointers(double**&result, double **&input_img, double **&weights){

        for (int i=0; i<conv_1; i++)
                delete[] weights[i];

        for (int i=0; i<img_1; i++)
                delete[] input_img[i];

        for (int i=0; i<res_1; i++)
                delete[] result[i];
        delete[] weights;
        delete[] input_img;
        delete[]  result;
}


template<int input_i, int input_j, int input_k, int input_l, int stride ,int conv_shape_0
        ,int conv_shape_1, int conv_shape_2, int conv_shape_3>                      //banch chanall stroka stolbec
void LAYER(std::string path_conv, std::string path_scale,
           double input[input_i][input_j][input_k][input_l],
           //double output[conv_shape_0][conv_shape_1/input_j][input_k/stride][input_l/stride])
           double output[1][conv_shape_0][input_k/stride][input_l/stride])
{

        //_____________________________CONVOLUTION__________

        double conv_matrix[conv_shape_0][conv_shape_1][conv_shape_2][conv_shape_3];
        rff<conv_shape_0,conv_shape_1,conv_shape_2,conv_shape_3>(path_conv, conv_matrix);

        double **result, **input_img, **weights;
        double after_loop_result[input_k/stride][input_l/stride] = {0};
        init_pointers<input_k/stride, input_l/stride, input_k, input_l, conv_shape_2, conv_shape_3>(result, input_img, weights);

        if (input_j == conv_shape_1) {
                for(int i=0; i<conv_shape_0; i++) {
                        for(int j=0; j<conv_shape_1; j++) {
                                //внутри первых двух размерностий тензора: подготовка данных для конволюции
                                //read conv matrix
                                for(int ii=0; ii<conv_shape_2; ii++) {
                                        for(int jj=0; jj<conv_shape_3; jj++) {
                                                //чтение весов для конволюции
                                                weights[ii][jj] = conv_matrix[i][j][ii][jj] ;
                                                //std::cout << weights[ii][jj] << ' ';
                                                if (std::isnan(weights[ii][jj])){  //TEST
                                                        weights[ii][jj] = 0.;
                                                        glob_counter_for_nan_test+=1;
                                                }
                                        }
                                }
                                for (int k=0; k<input_k; k++) {
                                        for (int l=0; l<input_k; l++) {
                                                //чтение входного изображения по данному каналу
                                                input_img[k][l] = input[0][j][k][l];
                                        }
                                }
                                result = depthwise_convolution(input_img, weights,
                                                               input_k, input_l,
                                                               conv_shape_2,conv_shape_3, stride);

                                for (int ii=0; ii<input_k/stride; ii++) {
                                        for (int jj=0; jj<input_l/stride; jj++) {
                                                after_loop_result[ii][jj] += result[ii][jj];
                                                if (std::isnan(result[ii][jj])){  //TEST
                                                        weights[ii][jj] = 0.;
                                                        glob_counter_for_nan_test+=1;
                                                }
                                        }
                                }
                        }
                        for (int k=0; k<input_k/stride; k++) {
                                for (int l=0; l<input_l/stride; l++) {
                                        output[0][i][k][l] = after_loop_result[k][l];           //батч конволюционной матрицы i переходин в канал выхода
                                        if (std::isnan(output[0][i][k][l])){            //TEST
                                                std::cout << glob_counter_for_nan_test << std::endl;
                                                glob_counter_for_nan_test+=1;
                                        }
                                }
                        }
                }

                del_pointers<input_k/stride,  input_k, conv_shape_2>(result, input_img, weights);
        }
        else {  //НЕ ВЕРИФИЦИРОВАННЫЙ ПРОГОН -- БУДУ СМОТРЕТЬ ПО РЕЗУЛЬТАТУ РАБОТЫ В Neural_Network.cpp
            for(int i=0; i<conv_shape_0; i++) {
                for(int j=0; j<conv_shape_1; j++) {
                    //внутри первых двух размерностий тензора: подготовка данных для конволюции
                    //read conv matrix
                    for(int ii=0; ii<conv_shape_2; ii++) {
                        for(int jj=0; jj<conv_shape_3; jj++) {
                            //чтение весов для конволюции
                            weights[ii][jj] = conv_matrix[i][0][ii][jj] ;
                            //std::cout << weights[ii][jj] << ' ';
                            if (std::isnan(weights[ii][jj])){  //TEST
                                weights[ii][jj] = 0.;
                                glob_counter_for_nan_test+=1;
                            }
                        }
                    }
                    for (int k=0; k<input_k; k++) {
                        for (int l=0; l<input_k; l++) {
                            //чтение входного изображения по данному каналу
                            input_img[k][l] = input[0][j][k][l];
                        }
                    }
                    result = depthwise_convolution(input_img, weights,
                                                   input_k, input_l,
                                                   conv_shape_2,conv_shape_3, stride);

                }
                for (int k=0; k<input_k/stride; k++) {
                    for (int l=0; l<input_l/stride; l++) {
                        output[0][i][k][l] = result[k][l];           //батч конволюционной матрицы i переходин в канал выхода
                        if (std::isnan(output[0][i][k][l])){            //TEST
                            std::cout << glob_counter_for_nan_test << std::endl;
                            glob_counter_for_nan_test+=1;
                        }
                    }
                }
            }

            del_pointers<input_k/stride,  input_k, conv_shape_2>(result, input_img, weights);
        } // КОНЕЦ ЭКСПЕРЕМЕНТАЛЬНОЙ ВСТАВКИ

        //____________BATCH_NORM________________________
        //double* batch_norm(double* input, int shape)
        if (input_j == conv_shape_1) {
                double *elements = new double[input_k/stride * input_l/stride];
                int batch_counter = 0;
                double *BN_result = new double[input_k/stride * input_l/stride];

                for(int i=0; i<conv_shape_0; i++) {
                        //чтение из массива и расчет BN
                        for (int k=0; k<input_k/stride; k++) {
                                for (int l=0; l<input_l/stride; l++) {
                                        //std::cout << i << ' ' << j << ' '<< k << ' '<< l << std::endl;
                                        //elements[batch_counter] = output[i][0][k][l];
                                        elements[batch_counter] = output[0][i][k][l];
                                        //std::cout << output[0][i][k][l] << ' ';
                                        batch_counter += 1;

                                }
                        }


                        BN_result = batch_norm(elements, input_k/stride * input_l/stride); //записали
                        batch_counter = 0;

                        //запись в исходный массив измененных значений
                        for (int k=0; k<input_k/stride; k++) {
                                for (int l=0; l<input_l/stride; l++) {
                                        //std::cout <<BN_result[batch_counter];
                                        output[0][i][k][l] = BN_result[batch_counter];
                                        batch_counter += 1;
                                }
                        }
                        batch_counter = 0;
                }
                delete[] elements;
                delete[] BN_result;
        }


        //__________________________SCALE_________________
        //template<int i>
        //void read_scale(std::string path, double weight[i], double bias[i])

        //double* scale(double* input, double* weights, double* bias, int chanals = 1)
        if (input_j == conv_shape_1) {
                double weight[conv_shape_0], bias[conv_shape_0];
                read_scale<conv_shape_0>(path_scale, weight, bias);
                double* result = new double [conv_shape_0];
                double* scale_input = new double [conv_shape_0];
                for (int k=0; k<input_k/stride; k++) {
                        for (int l=0; l<input_l/stride; l++) {

                              //чтение значений по данной строке и столбце через все бачи (или как их там)
                              for(int i=0; i<conv_shape_0; i++){
                                      scale_input[i] = output[0][i][k][l];
                              }
                              result = scale(scale_input, weight, bias, conv_shape_0);
                                //запись бачей обратно (или как их там)
                              for(int i=0; i<conv_shape_0; i++){
                                      output[0][i][k][l] = result[i];
                              }
                        }
                }
                delete[] result;
                delete[] scale_input;
        }


        //________________________________________ReLu__________________________________________________________________
        //double** relu(const int height, const int width, double** input)
        // double output[conv_shape_0][conv_shape_1/input_j][input_k/stride][input_l/stride]
        if (input_j == conv_shape_1 ) {

            double **result, **local_slice;
            result = new double* [input_k/stride];
            local_slice = new double* [input_k/stride];
            for(int i=0; i<input_k/stride; i++) {
                result[i] = new double[input_l / stride];
                local_slice[i] = new double[input_l / stride];
            }
            for(int i=0; i<conv_shape_0; i++){
                //перевод к double**
                for(int k=0; k<input_k/stride; k++){
                    for(int l=0; l<input_l/stride; l++){
                        local_slice[k][l] = output[0][i][k][l];
                    }
                }

                result = relu(input_k/stride, input_l/stride, local_slice);

                for(int k=0; k<input_k/stride; k++){
                    for(int l=0; l<input_l/stride; l++){
                        output[0][i][k][l] = result[k][l];
                    }
                }
            }
        }

        std::cout<<std::endl<< "good run\n";
}

// закоментированно на время инклуда
//double input[1][3][224][224];
//double pic[3][224][224];
//double output[1][32][224][224];
//
//double output2[32][1][224][224];


//int main() {
//        read_picture<3,224,224>("../input/input_image.txt", pic);
//        int number_isnan = 0;
//        for (int i=0; i<3; i++) {
//                for (int j=0; j<224; j++) {
//                        for (int k=0; k<224; k++) {
//                                input[0][i][j][k] = pic[i][j][k];
//                                if (std::isnan(input[0][i][j][k])){
//                                        input[0][i][j][k] = 0.;
//                                        number_isnan += 1;
//                                }
//                        }
//                }
//        }
//
//        LAYER<1,3,224,224,1,32,3,3,3>("python-nn-parser/TXT/conv-0.txt","python-nn-parser/TXT/SCALE-0.txt", input, output);
//        std::cout << "number_isnan" <<number_isnan;//number_isnan;
//        bool do_we_need_result = true;
//        if (do_we_need_result) {
//                for (int i = 0; i < 3; i++) {
//                        for (int j = 0; j < 224; j++) {
//                                for (int k = 0; k < 224; k++) {
//                                        //std::cout << (output[0][i][j][k]>0.1 ? output[0][i][j][k] : 0. ) << ' ';
//                                        std::cout << output[0][i][j][k] << ' ';
//                                        if (std::isnan(output[0][i][j][k]))
//                                                throw("FATAL we have nan in our result tensor");
//                                }
//                                std::cout << std::endl;
//                        }
//                }
//        }
//
//
//        return 0;
//}

#endif //IMPLEMENTATION_LAYER_H
//printf("%i - %i - %i\n", i, k, l);
//auto src = result[i];
//auto dst = output[i][0][k][l];

//fflush(stdout);
//std::cout << result[i] << std::endl;
//result[i] = 1;
//std::cout << i << ' ' << conv_shape_0 << '\n';