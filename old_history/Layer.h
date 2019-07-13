//
// Created by pavel on 04.12.18.
//

#ifndef SECOND_IMPLEMENTATION_LAYER_H
#define SECOND_IMPLEMENTATION_LAYER_H
#include "Tensor.h"

template<class T>
Tensor<T> Layer(Tensor<T> &input,
        std::string path_conv,
        std::string path_scale,
        std::string path_BN,
        int conv_batch,
        int conv_chanal,
        int conv_width,
        int conv_height,
        int stride) {

    Tensor<T> conv(conv_batch, conv_chanal, conv_width, conv_height);
    conv.rff(path_conv);

    Tensor<T> after_conv = Conv(input,conv,stride);             //конволюция работает Превосходно


    after_conv.Batch_norm(path_BN);                                    //вот тут начинаются расхождения
    after_conv.scale(path_scale);
    after_conv.ReLu();
    //R " good run " E;
    return after_conv;
}

#endif //SECOND_IMPLEMENTATION_LAYER_H
