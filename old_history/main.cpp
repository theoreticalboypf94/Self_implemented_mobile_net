#include <iostream>
#include "Tensor.h"
#include <cstdlib>
#include <ctime>

#include "Tensor.h"
#include "Layer.h"

int main() {

//    Tensor<float> img(1,3,224,224);
//    img.rff("../input/input_image.txt");
//    Tensor<float> layer0 = Layer(img, "python-nn-parser/TXT/conv-0.txt",
//            "python-nn-parser/TXT/SCALE-0.txt","python-nn-parser/TXT/BN-0.txt",32,3,3,3,2);
//    Tensor<float> layer1 = Layer(layer0, "python-nn-parser/TXT/conv-1.txt",
//                                 "python-nn-parser/TXT/SCALE-1.txt","python-nn-parser/TXT/BN-1.txt",32,1,3,3,1);

    std::vector<std::vector<float>> v
    = { {32,3,3,3,2},
        {32,1,3,3,1},
        {64,32,1,1,1},
        {64,1,3,3,2},
        {128,64,1,1,1},
        {128,1,3,3,1},
        {128,128,1,1,1},
        {128,1,3,3,2},
        {256,128,1,1,1},
        {256,1,3,3,1},
        {256,256,1,1,1},
        {256,1,3,3,2},
        {512,256,1,1,1},
        {512,1,3,3,1},
        {512,512,1,1,1},
        {512,1,3,3,1},
        {512,512,1,1,1},
        {512,1,3,3,1},
        {512,512,1,1,1},
        {512,1,3,3,1},
        {512,512,1,1,1},
        {512,1,3,3,1},
        {512,512,1,1,1},
        {512,1,3,3,2},
        {1024,512,1,1,1},
        {1024,1,3,3,1},
        {1024,1024,1,1,1}
    };
    std::vector<Tensor<float>> layer;
    std::string path_template_scale = "python-nn-parser/TXT/SCALE-",
            path_template_conv = "python-nn-parser/TXT/conv-",
            path_template_bn = "python-nn-parser/TXT/BN-",
            ending = ".txt", num, loop_s, loop_c, loop_b;

    //основная часть слоя
    Tensor<float> img(1,3,224,224);
    img.rff("../input/input_image.txt");
    for (int i=0; i<27; i++) {
        loop_s = path_template_scale + std::to_string(i) + ending;
        loop_b = path_template_bn + std::to_string(i) + ending;
        loop_c = path_template_conv + std::to_string(i) + ending;

        if (i==0){
            layer.push_back(Layer(img, loop_c, loop_s, loop_b,v[i][0],v[i][1],v[i][2],v[i][3],v[i][4]));
        }
        else {
            //layer[i] = Layer(layer[i - 1], loop_c, loop_s, loop_b, v[i][0], v[i][1], v[i][2], v[i][3], v[i][4]);
            layer.push_back(Layer(layer[i - 1], loop_c, loop_s, loop_b, v[i][0], v[i][1], v[i][2], v[i][3], v[i][4]));
        }
    }

    //3 последние операции
    Tensor<float> finish = AVG_POOL(layer.back());
    //finish.show();
    //fully connected
    Tensor<float> fully_connected(1000,1024,1,1);
    fully_connected.rff("python-nn-parser/TXT/conv-27.txt");
    finish = Conv(finish, fully_connected);
    //finish.show();
    Tensor<float> baies(1,1000,1,1);
    baies.rff("python-nn-parser/TXT/SCALE-27.txt");
    //baies.show();
    for (int i=0; i<1000; i++) {
        finish.set(0,i,0,0, finish.get(0,i,0,0) + baies.get(0,i,0,0));
    }
    finish.Soft_max();
    //finish.show();


    return 0;
}

