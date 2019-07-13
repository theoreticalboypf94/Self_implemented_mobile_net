//
// Created by pavel on 30.11.18.
//
#include "Layer.cpp"
#include <iostream>

double input[1][3][224][224];
double pic[3][224][224];

double output1[1][32][112][112] ={0};
double output2[1][32][112][112] ={0};
double output3[1][64][112][112] ={0};
double output4[1][64][56][56]   ={0};
double output5[1][128][56][56]  ={0};
double output6[1][128][56][56]  ={0};
double output7[1][128][56][56]  ={0};
double output8[1][128][28][28]  ={0};
double output9[1][256][28][28]  ={0};
double output10[1][256][28][28] ={0};
double output11[1][256][28][28] ={0};
double output12[1][256][14][14] ={0};
double output13[1][512][14][14] ={0};
double output14[1][512][14][14] ={0};
double output15[1][512][14][14] ={0};
double output16[1][512][14][14] ={0};
double output17[1][512][14][14] ={0};
double output18[1][512][14][14] ={0};
double output19[1][512][14][14] ={0};
double output20[1][512][14][14] ={0};
double output21[1][512][14][14] ={0};
double output22[1][512][14][14] ={0};
double output23[1][512][14][14] ={0};
double output24[1][512][7][7]   ={0};
double output25[1][1024][7][7]  ={0};
double output26[1][1024][7][7]  ={0};
double output27[1][1024][7][7]  ={0};
double output28[1000][1024][1][1] = {0};




#define IND 7
int main() {
    /*
     *
     *       принимаем картинку
     *
     */
    read_picture<3,224,224>("../input/input_image.txt", pic);
    int number_isnan = 0;
    for (int i=0; i<3; i++) {
        for (int j=0; j<224; j++) {
            for (int k=0; k<224; k++) {
                input[0][i][j][k] = pic[i][j][k];
                if (std::isnan(input[0][i][j][k])){
                    input[0][i][j][k] = 0.;
                    number_isnan += 1;
                }
            }
        }
    }

    LAYER<1,3,224,224,2,32,3,3,3>    ("python-nn-parser/TXT/conv-0.txt" ,"python-nn-parser/TXT/SCALE-0.txt" ,   input   , output1);  //1
    LAYER<1,32,112,112,1,32,1,3,3>   ("python-nn-parser/TXT/conv-1.txt" ,"python-nn-parser/TXT/SCALE-1.txt" ,   output1 , output2);  //2
    LAYER<1,32,112,112,1,64,32,1,1>  ("python-nn-parser/TXT/conv-2.txt" ,"python-nn-parser/TXT/SCALE-2.txt" ,   output2 , output3);  //3
    LAYER<1,64,112,112,2,64,1,3,3>   ("python-nn-parser/TXT/conv-3.txt" ,"python-nn-parser/TXT/SCALE-3.txt" ,   output3 , output4);  //4
    LAYER<1,64,56,56,1,128,64,1,1>   ("python-nn-parser/TXT/conv-4.txt" ,"python-nn-parser/TXT/SCALE-4.txt" ,   output4 , output5);  //5
    LAYER<1,128,56,56,1,128,1,3,3>   ("python-nn-parser/TXT/conv-5.txt" ,"python-nn-parser/TXT/SCALE-5.txt" ,   output5 , output6);  //6
    LAYER<1,128,56,56,1,128,128,1,1> ("python-nn-parser/TXT/conv-6.txt" ,"python-nn-parser/TXT/SCALE-6.txt" ,   output6 , output7);  //7
    LAYER<1,128,56,56,2,128,1,3,3>   ("python-nn-parser/TXT/conv-7.txt" ,"python-nn-parser/TXT/SCALE-7.txt" ,   output7 , output8);  //8 стали проявляться отрицательные значения!!!
    LAYER<1,128,28,28,1,256,128,1,1> ("python-nn-parser/TXT/conv-8.txt" ,"python-nn-parser/TXT/SCALE-8.txt" ,   output8 , output9);  //9
    LAYER<1,256,28,28,1,256,1,3,3>   ("python-nn-parser/TXT/conv-9.txt" ,"python-nn-parser/TXT/SCALE-9.txt" ,   output9 , output10);  //10
    LAYER<1,256,28,28,1,256,256,1,1> ("python-nn-parser/TXT/conv-10.txt","python-nn-parser/TXT/SCALE-10.txt",   output10, output11);  //11
    LAYER<1,256,28,28,2,256,1,3,3>   ("python-nn-parser/TXT/conv-11.txt","python-nn-parser/TXT/SCALE-11.txt",   output11, output12);  //12
    LAYER<1,256,14,14,1,512,256,1,1> ("python-nn-parser/TXT/conv-12.txt","python-nn-parser/TXT/SCALE-12.txt",   output12, output13);  //13
    LAYER<1,512,14,14,1,512,1,3,3>   ("python-nn-parser/TXT/conv-13.txt","python-nn-parser/TXT/SCALE-13.txt",   output13, output14);  //14
    LAYER<1,512,14,14,1,512,512,1,1> ("python-nn-parser/TXT/conv-14.txt","python-nn-parser/TXT/SCALE-14.txt",   output14, output15);  //15
    LAYER<1,512,14,14,1,512,1,3,3>   ("python-nn-parser/TXT/conv-15.txt","python-nn-parser/TXT/SCALE-15.txt",   output15, output16);  //16
    LAYER<1,512,14,14,1,512,512,1,1> ("python-nn-parser/TXT/conv-16.txt","python-nn-parser/TXT/SCALE-16.txt",   output16, output17);  //17
    LAYER<1,512,14,14,1,512,1,3,3>   ("python-nn-parser/TXT/conv-17.txt","python-nn-parser/TXT/SCALE-17.txt",   output17, output18);  //18
    LAYER<1,512,14,14,1,512,512,1,1> ("python-nn-parser/TXT/conv-18.txt","python-nn-parser/TXT/SCALE-18.txt",   output18, output19);  //19
    LAYER<1,512,14,14,1,512,1,3,3>   ("python-nn-parser/TXT/conv-19.txt","python-nn-parser/TXT/SCALE-19.txt",   output19, output20);  //20
    LAYER<1,512,14,14,1,512,512,1,1> ("python-nn-parser/TXT/conv-20.txt","python-nn-parser/TXT/SCALE-20.txt",   output20, output21);  //21
    LAYER<1,512,14,14,1,512,1,3,3>   ("python-nn-parser/TXT/conv-21.txt","python-nn-parser/TXT/SCALE-21.txt",   output21, output22);  //22
    LAYER<1,512,14,14,1,512,512,1,1> ("python-nn-parser/TXT/conv-22.txt","python-nn-parser/TXT/SCALE-22.txt",   output22, output23);  //23
    LAYER<1,512,14,14,2,512,1,3,3>   ("python-nn-parser/TXT/conv-23.txt","python-nn-parser/TXT/SCALE-23.txt",   output23, output24);  //24
    LAYER<1,512,7,7,1,1024,512,1,1>  ("python-nn-parser/TXT/conv-24.txt","python-nn-parser/TXT/SCALE-24.txt",   output24, output25);  //25
    LAYER<1,1024,7,7,1,1024,1,3,3>   ("python-nn-parser/TXT/conv-25.txt","python-nn-parser/TXT/SCALE-25.txt",   output25, output26);  //26
    LAYER<1,1024,7,7,1,1024,1024,1,1>("python-nn-parser/TXT/conv-26.txt","python-nn-parser/TXT/SCALE-26.txt",   output26, output27);  //27 размер здесь 1,1024,7,7

    /*
     *       немного рукописно - не буду реализовывать
    */
    //превращение в форму 1,1024,1,1 через AVG_pool.h
    double sum =0.;
    double avg =0.;
    for(int j=0; j<1024; j++) {
        sum = 0.;
        avg = 0.;
        for(int k=0; k<7; k++) {
            for(int l=0; l<7; l++) {
                sum += output27[0][j][k][l];
            }
        }
        avg = sum / 49.;
        output26[0][j][0][0] = avg;                   //output26!
    }

// последняя конволюция
    rff<1000,1024,1,1>("python-nn-parser/TXT/conv-27.txt",output28);
    double num;
    double bias[1000];
    double result[1000];
    double loop_sum = 0;
    std::ifstream ifile("python-nn-parser/TXT/SCALE-27.txt", std::ios::in);
    for (int j=0; j<1000; j++) {
        ifile >> num;
        bias[j] = num;
    }

    for (int i=0; i<1000; i++){
        loop_sum = 0;
        for (int j=0; j<1024; j++) {
            loop_sum += output26[0][j][0][0]*output28[i][j][0][0];
        }
        result[i] = loop_sum + bias[i];
    }

//    for (int i=0; i<1000; i++)
//        std::cout << result[i] << ' ';

    //_______SOFTMAX________
    double* soft_max_result = new double[1000];
    soft_max_result = soft_max(result, 1000);

    for (int i=0; i<1000; i++)
        std::cout << soft_max_result[i] << ' ';

    loop_sum =0.;
    for (int i=0; i<1000; i++) {
        loop_sum += soft_max_result[i];
    }


    std::cout << std::endl << std::endl << loop_sum;
}
