//
// Created by pavel on 27.11.18.
//

#include "read_from_text.h"
#include "first_step_test_of_functions.cpp"

/*
 *  Здесь дана черновое выполнение
 *
 */

//int main() {
//    double filter[32][3][3][3];                                 //banch chanall stroka stolbec
//    rff<32,3,3,3>("python-nn-parser/TXT/conv-0.txt", filter);
//
//    double img[3][224][224];  // input image shape(0,3,224,224)
//    read_picture<3,224,224>("../input/input_image.txt", img);
//
//    double **result, **input, **weights, after_loop_result[224][224] = {0}; //TODO загнать сюда шаблоны И написать надстройки над функциями для перехода от 4 тензора к 2 тензору
//    weights = new double* [3];
//    for (int i=0; i<3; i++)
//        weights[i] = new double[3];
//    input = new double* [224];
//    for (int i=0; i<224; i++)
//        input[i] = new double[224];
//    result = new double* [224];
//    for (int i=0; i<224; i++)
//        result[i] = new double[224];
//
//
//    for (int i=0; i<32; i++) {         //set of banch
//        for (int j=0; j<3; j++) {       //set of channals
//
//            //weight(filter) init
//            for (int k=0; k<3; k++) {
//                for (int l=0; l<3; l++) {
//                    weights[k][l] = filter[i][j][k][l];
//                }
//            }
//
//            //input(img) init
//            for (int k=0; k<224; k++) {
//                for (int l=0; l<224; l++) {
//                    input[k][l] = img[j][k][l];
//                }
//            }
//
//            result = depthwise_convolution(input, weights,
//                    224, 224, 3, 3, 1);
//            for (int i=0; i<224; i++) {
//                for (int j=0; j<224; j++) {
//                    after_loop_result[i][j] += result[i][j];
//                }
//            }
//
//        }
//    }
//
//    for (int i=0; i<224; i++) {
//        for (int j=0; j<224; j++) {
//            std::cout << after_loop_result[i][j] << ' ';
//        }
//        std::cout << std::endl;
//    }
//
//}

