//#include "H5Cpp.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

#include "Soft_max.h"
#include "Batch norm.h"
#include "ReLu.h"
#include "Conv.h"
#include "AVG_pool.h"
#include "Scale.h"

/*
 *  Данная программа является тестовой обкаткой всех команд из нашей нейросети и выгрузке данных из
 *  hdf5 файла
 */

//using namespace H5; //ТУТ ХЕРНЯ -- закоментил чтобы не мешала работать
//ILSVRC2012_val_00000002.JPEG.tfl.hdf5
// h5dump ../input/in.hdf5
int test()
{
    bool do_we_need_to_read     = false;
    bool soft_max_test          = false;
    bool Batch_norm_test        = false;
    bool ReLu_test              = false;
    bool Conv_test              = false;
    bool Pool_test              = false;
    bool scale_test             = false;

// ТУТ ХЕРНЯ -- закоментил чтобы не мешала работать
//    if (do_we_need_to_read) {
//        // показанно корректное считывание входных  массивов
//
//        H5File file("../input/ILSVRC2012_val_00000002.JPEG.tfl.hdf5", H5F_ACC_RDONLY);
//        DataSet dataset = file.openDataSet("input");
//        DataSpace dataspace = dataset.getSpace();
//        float a[1][224][224][3];
//
//
//        hsize_t local[dataspace.getSimpleExtentNdims()]; //считываем размерность тензора и число элементов в каждой размерности
//        dataspace.getSimpleExtentDims(local); //считываем размерность тензора и число элементов в каждой размерности
//
//
//        dataset.read(a, PredType::NATIVE_FLOAT); //записываем прочитанное в список
//        bool screen_viev = true;
//        if (screen_viev) {
//            // выводим на экран
//            for (int i = 0; i < local[0]; i++) {
//                for (int j = 0; j < local[1]; j++) {
//                    for (int k = 0; k < local[2]; k++) {
//                        for (int c = 0; c < local[3]; c++) {
//                            std::cout << a[i][j][k][c] << ' ';
//                        }
//                        std::cout << std::endl;
//                    }
//                }
//            }
//        }
//    }

    if (soft_max_test)  {
        // тест показывает корректныю работу моей реализации soft_max

        double a[] = {3, 3.3, 2.2, 0.1, 0.11};
        int shape = 5;
        double* out;
        out = soft_max(a,shape);
        for (int i=0; i<shape; i++)
            std::cout << out[i] << ' ' ;
        std::cout << std::endl;
    }

    if (Batch_norm_test) {
        // провожу проверку корректности Batch norm
        // проверка показала корректность написания функции

        std::default_random_engine generator(time(NULL));       //генератор случайных чисел, сид устанавливается по времени
        std::normal_distribution<double> distribution(5.0, 20);
        const int length = 100000;
        double p[length] = {};

        for(int i=0; i<length; i++){
            p[i] = distribution(generator);
            distribution.reset();                       //сброс генератора на каждой итерации цикла
        }
        std::cout<< "Math expectation is equal " << math_expectatinon(p, length) << std::endl ;
        std::cout<< "Math variance is equal " << math_variance(p, length) << std::endl;
        std::cout<< "Math standadard deviation is equal " << sqrt(math_variance(p, length)) << std::endl;

        std::cout << std::endl << "we handle our data with batch_norm " << std::endl << std::endl;
        double* handle;
        handle = batch_norm(p, length);

        std::cout<< "Math expectation is equal " << math_expectatinon(handle, length) << std::endl ;
        std::cout<< "Math variance is equal " << math_variance(handle, length) << std::endl;
        std::cout<< "Math standadard deviation is equal " << sqrt(math_variance(handle, length)) << std::endl;

    }

    if(ReLu_test) {
        // провожу корректность  ReLu
        // работает корректно.

        std::default_random_engine generator(time(NULL));       //генератор случайных чисел, сид устанавливается по времени
        std::normal_distribution<double> distribution(0.0, 20);
        const int length = 10;
        double **p;
        p = new double*[length];
        for (int i=0; i<length; i++) {
            p[i] = new double[length];
        }
        //инициализация нормальным распределением
        for (int i=0; i< length; i++){
            for (int j=0; j<length; j++) {
                p[i][j] = distribution(generator);
                distribution.reset();
            }
        }
        double** result = new double*[length];
        for (int i=0; i<length; i++)
            result[i] = new double[length];
        result = relu(length, length, p);

        //вывод на экран
        for (int i=0; i<length; i++) {
            for (int j=0; j<length; j++) {
                std::cout << p[i][j] << ' ';
            }
            std::cout <<std::endl;
        }

        //вывод на экран __result__
        for (int i=0; i<length; i++) {
            for (int j=0; j<length; j++) {
                std::cout << result[i][j] << ' ';
            }
            std::cout <<std::endl;
        }

    }

    if(Conv_test) {
        // проведем проверку конволюционной операции
        // на вход подаем матрицу канала и матрицу фильтра.

        std::default_random_engine generator(time(NULL));       //генератор случайных чисел, сид устанавливается по времени
        std::normal_distribution<double> distribution(0.0, 2);
        const int length = 3;
        double **p, **result;
        p = new double*[length];
        result = new double*[length];
        for (int i=0; i<length; i++) {
            p[i] = new double[length];
            result[i] = new double[length];
        }
        //инициализация нормальным распределением
        for (int i=0; i< length; i++){
            for (int j=0; j<length; j++) {
                p[i][j] = distribution(generator);
                distribution.reset();
            }
        }
        //вывод на экран до
        for (int i=0; i< length; i++){
            for (int j=0; j<length; j++) {
                std::cout << p[i][j] << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << "AFTER USING OF CONVOLUTION" << std::endl << std::endl;
        double filter[3][3] = {
                        {0.1, 0, -0.1},
                        {0.1, 0, -0.1},
                        {0.1, 0, -0.1},
                        };

        double* intermediate[3];
        for (int i = 0; i<3; i++) intermediate[i] = filter[i];
        double** pp_filter = intermediate;

        result = depthwise_convolution(p, pp_filter, length, length, 3, 3, 1);
        //вывод на экран после
        for (int i=0; i< length; i++){
            for (int j=0; j<length; j++) {
                std::cout << result[i][j] << ' ';
            }
            std::cout << std::endl;
        }

    }
    if(Pool_test) {
        //произведена проверка указанная операция работает.

        if (scale_test) {
            double in[3] = {1, 2, 3};
            double w[3] = {-1, -1, -1};
            double bi[3] = {1, 1, 1};
            double *out;
            out = scale(in, w, bi, 3);
            for (int i = 0; i < 3; i++)
                std::cout << out[i] << std::endl;
        }
    }

    return 0;
}