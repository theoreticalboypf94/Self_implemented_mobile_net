//
// Created by pavel on 23.11.18.
//

#ifndef IMPLEMENTATION_AVG_POOL_H
#define IMPLEMENTATION_AVG_POOL_H

#define SHAPE  7

double avg_pool(double input[SHAPE][SHAPE]){
    /*
     *
     */
    double mean =0.;
    for(int i=0; i<SHAPE; i++) {
        for(int j=0; j<SHAPE; j++) {
            mean += input[i][j];
        }
    }
    mean = mean / (SHAPE * SHAPE);
    return mean;
}
#endif //IMPLEMENTATION_AVG_POOL_H
