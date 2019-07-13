//
// Created by pavel on 04.12.18.
//

#ifndef SECOND_IMPLEMENTATION_TENSOR_H
#define SECOND_IMPLEMENTATION_TENSOR_H
#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cassert>

#define R std::cout<<
#define E <<std::endl;
#define Eps 1e-5

typedef std::vector<int> vec;

template <class T>
class Tensor {
private:
    int batch, chanal, height, width;
    std::vector<T> _arr;
    vec current_tensor_shape() {
        vec result;
        result.push_back(this->batch);
        result.push_back(this->chanal);
        result.push_back(this->height);
        result.push_back(this->width);
        return result;
    }
    T math_expectation(Tensor *arg, int chenal) {
        T sum = 0.;
        for (int i=0; i<arg->height; i++) {
            for (int j=0; j<arg->width; j++) {
                sum += arg->get(0, chenal, i, j);
            }
        }

        bool do_we_need_full_information = false;
        if (do_we_need_full_information) {
            std::cout << "E_x = " << sum / (arg->height * arg->width) << std::endl;
        }
        return sum / (arg->height * arg->width);
        //return 1.;
    }
    T math_variance(Tensor *arg, int chenal) {
        T E_x = math_expectation(arg, chenal);
        T variance = 0.;
        for (int i=0; i<arg->height; i++) {
            for (int j=0; j<arg->width; j++) {
                variance += pow((arg->get(0, chenal, i, j) - E_x), 2);
            }
        }

        bool do_we_need_full_info = false;
        if (do_we_need_full_info) {
            std::cout << "D_x = " << variance / (arg->height * arg->width);
        }
        return variance / (arg->height * arg->width) + Eps;
    }

public:
    vec shape;

    Tensor(int _batch, int _chanal, int _height, int _width) : batch(_batch), chanal(_chanal), height(_height),
                                                               width(_width), _arr(_batch*_chanal*_height*_width, 0) {
        shape = current_tensor_shape();
    } // конструктор работает корректно

    ~Tensor() {             //TODO доделать деструктор
       //delete _arr;
       if (false) {
           R "deleted" E;
       }
    }

    T get(int _batch, int _chanal, int _height, int _width) {
        int position = _batch * (chanal*height*width) + _chanal * (height*width) + _height * width + _width;
        return _arr[position];
    } //проверил

    void set(int _batch, int _chanal, int _height, int _width, T value) {
        int position = _batch * (chanal*height*width) + _chanal * (height*width) + _height * width + _width;
        _arr[position] = value;
    } //проверил

    void ReLu(){
        /*
         *      часть операций проводимых тензором надо самим собой будет реализованна непосредственна в
         *      классе Tensor
         */
        T loop_value =0.;
        for (int i=0; i<this->shape[0]; i++) {
            for (int j=0; j<this->shape[1]; j++) {
                for (int k=0; k<this->shape[2]; k++) {
                    for (int l=0; l<this->shape[3]; l++){
                        loop_value = this->get(i, j, k, l);
                        loop_value = (loop_value <= 0.) ? 0. : loop_value;
                        this->set(i, j, k, l, loop_value);
                    }
                }
            }
        }
    } //проверил

    void Soft_max(){
        /*
         *      данную операцию тензор осуществляет над самим собой, не изменяя своих размерностей, соответственно
         *      данная операция будет реализована здесь
         *
         *      необходимым условием ее реализации будет равенство единице 1, 3, 4 размерности
         */
        if (this->shape[0] != 1 || this->shape[2] != 1 || this->shape[3] != 1)
            throw new std::string("Critical Error in Tenssor's shape< 0 , 2 or 3 dim. isn't equal 1"); //спросить про этот момент подробнее
        T denomenator =0.;
        for(int i=0; i<this->shape[1]; i++)
            denomenator += exp(this->get(0,i,0,0));

        for(int i=0; i<this->shape[1]; i++)
            this->set(0,i,0,0, exp(this->get(0, i, 0, 0))/denomenator);

        bool do_we_need_full_info = false;
        if (do_we_need_full_info) {
            T sum = 0.;
            for (int i = 0; i < this->shape[1]; i++)
                sum += this->get(0, i, 0, 0);
            std::cout << " denomenator = " << denomenator << std::endl;
            std::cout << "sum = " << sum;
        }
    } //проверил

    void Batch_norm_old() {         //кому война а тебе на ебало говна
        T E_x;
        T D_x;
        T value;

        for (int j=0; j<this->shape[1]; j++) {          // переход по каналам
            E_x = math_expectation(this, j);     // просто кому война а кому на ебало говна
            D_x = math_variance(this, j);
            for (int k=0; k<this->shape[2]; k++) {      // переход по строкам
                for (int l=0; l<this->shape[3]; l++){   // переход по столбцам
                    //value = (this->get(0, j, k, l) - E_x) / pow(D_x, 0.5);
                    value = (this->get(0, j, k, l) - (-0.002689603716135025)) / pow(Eps + 0.24141806364059448, 0.5);
                    this->set(0, j, k, l, value);
                }
            }
            bool do_we_need_full_information = true;
            if (do_we_need_full_information) {
                R "D_x = " << D_x E;
                R "E_x = "  << E_x E;
                R "*************" E;
            }
        }


    } //проверил;

    void Batch_norm(std::string path) {         //кому война а тебе на ебало говна
        std::ifstream ifile(path, std::ios::in);
        T num;
        // длина считываемого файла соответствует удвоенному числу каналов - первые значения это веса
        // вторые это bias (отступы)
        T gamma[this->shape[1]];
        T betha[this->shape[1]];
        T value;

        for (int i=0; i<this->shape[1]; i++){
            ifile >> num;
            //std::cout << " scale = " << num << ' ';
            gamma[i] = num;
            //R "gamma = " << gamma[i] E;
        }
        for (int i=0; i<this->shape[1]; i++) {
            ifile >> num;
            betha[i] = num;
            //R "betha = " << num E;
        }

        for (int j=0; j<this->shape[1]; j++) {          // переход по каналам
            for (int k=0; k<this->shape[2]; k++) {      // переход по строкам
                for (int l=0; l<this->shape[3]; l++){   // переход по столбцам
                    //value = (this->get(0, j, k, l) - E_x) / pow(D_x, 0.5);
                    value = (this->get(0, j, k, l) - gamma[j]) / pow(Eps + betha[j], 0.5);
                    this->set(0, j, k, l, value);
                }
            }

        }


    } //проверил;

    void rff(const std::string& path) {
        /*
         *  Read from file operation
         *  содержит единственный аргумент - путь к считываемому файлу
         */
        std::ifstream ifile(path);
        T num; int foo;
        assert(ifile.good());
        for (int i=0; i<this->shape[0]; i++) {
            for (int j=0; j<this->shape[1]; j++) {
                for (int k=0; k<this->shape[2]; k++) {
                    for (int l=0; l<this->shape[3]; l++){
                        ifile>> num;
                        //std::cout << num << ' ';
                        this->set(i,j,k,l,num);
                    }
                }
            }
        }
        ifile.close();

    }  //проверено - лучше указывать абсолютный путь

    void show() const {
        for (int i=0; i<batch*chanal*height*width; i++) {
            if (i % width == 0)
                std::cout << std::endl;
            if (i % (width*height) == 0)
                std::cout << "----------------------------------------------------\n";
            std::cout << _arr[i] << ' ';
        }
        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << "Parametrs:\n";
        std::cout << batch << ' ' << chanal << ' ' << height << ' ' << width << std::endl;
    } //проверил

    void show_final() const {
        for (int i=0; i<batch*chanal*height*width; i++) {
            if (i % width == 0)
                std::cout << std::endl;
            std::cout << _arr[i] << ' ';
        }
        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << "Parametrs:\n";
        std::cout << batch << ' ' << chanal << ' ' << height << ' ' << width << std::endl;
    } //проверил


    void scale(std::string path) {
        std::ifstream ifile(path, std::ios::in);
        T num;
        // длина считываемого файла соответствует удвоенному числу каналов - первые значения это веса
        // вторые это bias (отступы)
        T scale[this->shape[1]];
        T bias[this->shape[1]];
        for (int i=0; i<this->shape[1]; i++){
            ifile >> num;
            //std::cout << " scale = " << num << ' ';
            scale[i] = num;
        }
        for (int i=0; i<this->shape[1]; i++) {
            ifile >> num;
            bias[i] = num;
            //std::cout << " bias = " << num << ' ';
        }
        T value=0.;
        for (int i=0; i<this->shape[0]; i++){
            for (int j=0; j<this->shape[1]; j++){
                for (int k=0; k<this->shape[2]; k++){
                    for (int l=0; l<this->shape[3]; l++){
                        value = this->get(i,j,k,l)*scale[j] + bias[j];
                        this->set(i,j,k,l, value);
                    }
                }
            }
        }



    } //проверил

    T bastard_get(int i){
        return _arr[i];
    }
};

// операторы меняющие размер исходного тензора сегрегированны вне класса

// это оператор конволюции
template <class T>
Tensor<T> Conv (Tensor<T> &tensor, Tensor<T> &conv, int stride=1) {
    /*
     *      оператор умножения на деле является перегрузкой для конволюции в нейросети
     *      мне представляется разумным произвести разделение исполняемого кода на две
     *      части первая часть на те случаи где фильтр [x][1].. а картинка [1][x]..
     *      вторая часть на случай где фильтр [y][x].. а картинка [1][x]
     */

    Tensor<T> extended(tensor.shape[0],tensor.shape[1],tensor.shape[2]+2,tensor.shape[3]+2);
    //fill extended tensor
    for (int i=0; i<tensor.shape[0]; i++) {
        for (int j=0; j<tensor.shape[1]; j++) {
            for (int k=0; k<tensor.shape[2]+2; k++) {                                       //расширение изображения происходит только на уровне картинки
                for (int l=0; l<tensor.shape[3]+2; l++) {
                    if (k*l == 0 || k == tensor.shape[2]+1 || l == tensor.shape[3]+1) {
                        extended.set(i, j, k, l, 0.);
                    } else {
                        extended.set(i,j,k,l, tensor.get(i,j,k-1,l-1));
                    }

                }
            }
        }
    }                                                                                                                   // работает корректно
    //return extended;

    // корректно!
    if (conv.shape[1] == 1) {      //img [1][x][y][z] conv[x][1][3][3] ->result[1][x][y][z]    conv.shape[0] == extended.shape[1]  [3][3] - строго всегда
        Tensor<T> result(1, conv.shape[0], tensor.shape[2]/stride, tensor.shape[2]/stride);
        T conv_sum = 0.;

        for (int j=0; j<tensor.shape[1]; j++) {             //совпадает с batch фильтра с conv.shape[0]
            for (int k=0; k<extended.shape[2]-2; k+=stride) {
                for (int l=0; l<extended.shape[3]-2; l+=stride) {
                    conv_sum =0.;
                    for (int i1 = 0; i1 <conv.shape[2] ; ++i1) {
                        for (int i2 = 0; i2 <conv.shape[3] ; ++i2) {
                            conv_sum += extended.get(0, j, k+i1, l+i2) * conv.get(j, 0, i1, i2);

                            bool do_we_need_full_information = false;
                            if (do_we_need_full_information) {
                                std::cout <<"extended = " <<extended.get(0, j, k+i1, l+i2) << std::endl;
                                std::cout << "conv = " << conv.get(j, 0, i1, i2) << std::endl;
                            }
                        }
                    }
                    result.set(0, j, k/stride, l/stride, conv_sum); // перевожу (отображаю) в единицы страйдов
                }
            }
        }
        return result;      //работает корректно
    }
    else {   //  img[1][[x][y][z] conv[f][x][3][3] -> result[1][f][y][z]    conv.shape[1] == extended.shape[1]
        Tensor<T> result(1, conv.shape[0], tensor.shape[2]/stride, tensor.shape[3]/stride);
        Tensor<T> loop_result(1, conv.shape[0], tensor.shape[2]/stride, tensor.shape[3]/stride);
        T conv_sum = 0.;
        T value = 0.;

        if (conv.shape[2] != 1) {       //вроде корректно
            //наворачиваю
            for (int i = 0; i < conv.shape[0]; i++) {
                for (int j = 0; j < conv.shape[1]; j++) {
                    for (int k = 0; k < extended.shape[2] - 2; k += stride) {
                        for (int l = 0; l < extended.shape[3] - 2; l += stride) {
                            //операция конволюции на каждый пиксель
                            for (int i1 = 0; i1 < conv.shape[2]; ++i1) {
                                for (int i2 = 0; i2 < conv.shape[3]; ++i2) {
                                    conv_sum += extended.get(0, j, k + i1, l + i2) * conv.get(i, j, i1, i2);

                                    bool do_we_need_full_information = false;
                                    if (do_we_need_full_information) {
                                        std::cout << "extended = " << extended.get(0, j, k + i1, l + i2) << std::endl;
                                        std::cout << "conv = " << conv.get(i, j, i1, i2) << std::endl;
                                        std::cout << "conv_sum = " <<conv_sum << std::endl;
                                    }
                                }
                            }
                            value = loop_result.get(0, i, k / stride, l / stride) + conv_sum;                           //мы складываем поканальные значения
                            bool do_we_need_full_information2 = false;
                            if (do_we_need_full_information2) {
                                std::cout << "value = " << value << std::endl;
                                std::cout << i << ' ' <<  k/stride << ' ' << l/stride << std::endl;
                            }
                            loop_result.set(0, i, k / stride, l / stride, value);
                            conv_sum = 0.;
                        }
                    }
                }
            }
            // занесение результатов в окончательный выходной тензор
            for (int i=0; i<conv.shape[0]; i++) {
                for (int k=0; k < extended.shape[2] -2; k+=stride) {
                    for (int l = 0; l < extended.shape[3] - 2; l += stride) {
                        result.set(0, i, k/stride, l/stride, loop_result.get(0, i, k/stride, l/stride));
                    }
                }
            }
            return result;//вроде корректно
        }

        //вывожу наиболее массовый случай когда последние две размерности равны единице
        if (conv.shape[2] == 1) {
            Tensor<T> result(1, conv.shape[0], tensor.shape[2]/stride, tensor.shape[3]/stride);
            Tensor<T> loop_result(1, conv.shape[0], tensor.shape[2]/stride, tensor.shape[3]/stride);
            T conv_sum = 0.;
            T value = 0.;

            for (int i=0; i<conv.shape[0]; i++) {
                for (int j=0; j<conv.shape[1]; j++) {                       //conv.shape[1] == extended.shape[1]
                    for (int k=1; k<extended.shape[2]-1; k+=stride) {
                        for (int l=1; l<extended.shape[3]-1; l+=stride ) {
//                            conv_sum += extended.get(0, j, k, l) * conv.get(i, j, 0, 0);
//                            value = loop_result.get(0, i, k/stride, l/stride) + conv_sum;
//                            loop_result.set(0, i, k/stride, l/stride, value);
                            conv_sum = extended.get(0, j, k, l) * conv.get(i, j, 0, 0);
                            value = loop_result.get(0, i, k/stride-1, l/stride-1) + conv_sum;
                            loop_result.set(0, i, k/stride-1, l/stride-1, value);
                            bool do_we_need_full_information = false;
                            if (do_we_need_full_information) {
                                std::cout << "extended("<<j<<","<<k<<","<<l<<") = " << extended.get(0, j, k, l) << std::endl;
                                std::cout << "conv = " << conv.get(i, j, 0, 0) << std::endl;
                                std::cout << "loop("<<i<<","<<k<<","<<l<<") = "<< loop_result.get(0, i, k/stride, l/stride) << std::endl;
                            }
                            conv_sum = 0.;
                        }
                    }
                }
            }

            //std::cout <<"shape3 " << loop_result.shape[3] << std::endl;
            for (int i=0; i<conv.shape[0]; i++) {
                for (int k=0; k < extended.shape[2] -2; k+=stride) {
                    for (int l=0; l < extended.shape[3] - 2; l += stride) {
                        //std::cout << loop_result.get(0, i, k/stride, l/stride) << ' ';
                        result.set(0, i, k/stride, l/stride, loop_result.get(0, i, k/stride, l/stride));

                        bool do_we_need_full_information = false;
                        if (do_we_need_full_information) {
                            std::cout << "loop("<<i<<","<<k<<","<<l<<") = "<< loop_result.get(0, i, k/stride, l/stride)  << std::endl;
                        }
                    }
                }
            }
            return result;
        }

    }



}   //проверил на простых примерах вроде работает

template <class T>                              //проверка проведена
Tensor<T> AVG_POOL(Tensor<T> &tensor) {
    // tensor[][][7][7] -> tensor[][][1][1]
    T avg = 0.;
    T sum = 0.;
    Tensor<T> result(tensor.shape[0], tensor.shape[1], 1,1);
    for (int i=0; i<tensor.shape[0]; i++) {
        for (int j=0; j<tensor.shape[1]; j++) {
            for (int k=0; k<tensor.shape[2]; k++) {
                for (int l=0; l<tensor.shape[3]; l++) {
                    sum += tensor.get(i,j,k,l);
                    //std::cout << sum << ' ';
                }
            }
            avg = sum / 49.;
            //std::cout << std::endl << avg << std::endl;
            sum = 0.;
            result.set(i,j,0,0,avg);
            avg = 0.;
            //std::cout << result.get(i,j,0,0) << std::endl;
        }
    }

    return result;
}


#endif //SECOND_IMPLEMENTATION_TENSOR_H
