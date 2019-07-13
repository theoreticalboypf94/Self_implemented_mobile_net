//
// Created by pavel on 27.11.18.
//
#ifndef RFF
#define RFF
#include <string>
#include <iostream>
#include <fstream>

template<int i, int j, int k, int l>
void rff(std::string path, double result[i][j][k][l]) {
    //function for read weights in depthvise convolution operation use much time (28)
    std::ifstream ifile(path, std::ios::in);
    double num;

    for(int ii=0; ii < i; ii++) {
        for (int jj=0; jj < j; jj++) {
            for (int kk=0; kk < k; kk++) {
                for (int ll=0; ll < l; ll++) {
                    ifile >> num;
                    result[ii][jj][kk][ll] = num;

                    bool do_I_need_to_show = false;
                    if (do_I_need_to_show) {
                        std::cout << num << std::endl;
                    }
                }
            }
        }
    }

    bool do_I_need_to_show = false;
    if (do_I_need_to_show) {
        for (int ii = 0; ii < i; ii++) {
            for (int jj = 0; jj < j; jj++) {
                for (int kk = 0; kk < k; kk++) {
                    for (int ll = 0; ll < l; ll++) {
                        std::cout << result[ii][jj][kk][ll] << '\t';
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }
}

template<int i, int j, int c>
void read_picture(std::string path, double result[i][j][c]) {
    //special function to read input image from txt file, it using once time
    std::cout << "*****";
    std::ifstream ifile(path, std::ios::in);
    double num;

    for(int ii=0; ii < i; ii++) {
        for (int jj=0; jj < j; jj++) {
            for (int cc=0; cc < c; cc++) {
                    ifile >> num;
                    result[ii][jj][cc] = num;
            }
        }
    }
}

template<int i> // сделано в том предположении, что мы таки можем отслеживать размер каналов не прибигая непосредственно к чению файлов
void read_scale(std::string path, double weight[i], double bias[i]) {
    std::ifstream ifile(path, std::ios::in);
    double num;
    for (int j=0; j<i; j++) {
        ifile >> num;
        weight[j] = num;
    }
    for (int j=0; j<i; j++) {
        ifile >> num;
        bias[j] = num;
    }
}

// закоментированно потому что этот файл будет вызван в дальнейшем, то что снизу по сути это документация как это работает
//int main() {
//    double res[32][3][3][3];
//    //rff<32,3,3,3>("python-nn-parser/TXT/conv-0.txt", res);
//    double img[3][224][224];  // input image shape(0,3,224,224)
//    read_picture<3,224,224>("../input/input_image.txt", img);
//
//}

#endif