#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include "../pixels/Pixel.hpp"
#include "../pixels/RGBPixel.hpp"
#include "../pixels/GSCPixel.hpp"


/* Mathematical procedures for equalizing the histogram of an image
*/
void calc_histogram(int histogram[], int **Y, int height, int width);
void calc_distributed_probability(double probability[], int histogram[], int size);
void calc_cumulative_probability(double probability[]);
void calc_new_luminocity(int new_luminocity[], double probability[]);
void calc_new_Y_values(int** Y, int new_luminocity[], int height, int width);
int clip(int value);

#endif