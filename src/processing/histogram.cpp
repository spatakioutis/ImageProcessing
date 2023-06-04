#include "histogram.hpp"

void calc_histogram(int histogram[], int **Y, int height, int width){
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
            histogram[Y[i][j]]++;
}

void calc_distributed_probability(double probability[], int histogram[], int size){
    for (int i=0; i<Pixel::MAX_LUMINOCITY+1; i++){
        probability[i] = ((double)histogram[i]) / size; 
    }
}

void calc_cumulative_probability(double probability[]){
    for (int i=1; i<Pixel::MAX_LUMINOCITY+1; i++){
        probability[i] += probability[i-1];
    }
}

void calc_new_luminocity(int new_luminocity[], double probability[]){
    for (int i=0; i<Pixel::MAX_LUMINOCITY; i++){
        new_luminocity[i] = probability[i] * Pixel::MAX_YUV_LUMINOCITY;
    }
}

void calc_new_Y_values(int** Y, int new_luminocity[], int height, int width){
    for (int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            Y[i][j] = new_luminocity[ Y[i][j] ];
        }
    }
}

int clip(int value){
    if (value < 0)
        return 0;
    else if (value > 255)
        return 255;
    return value;
}
