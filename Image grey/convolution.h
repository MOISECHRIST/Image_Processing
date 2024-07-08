#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "grey_Image.h"

/*
The user entry the different element of filter
- dimension of filter
- Elements into the filter
 */
float ** entry_ConvFilter(int dim);

/*
The user entry the filter's dimensions
and the program return the mean filter of these dimensions 
 */
float ** create_MeanConvFilter(int dim);

grey_Image * compute_Convolution(grey_Image * img, float ** filter, int filter_dim);

grey_Image * compute_MedianConvolution(grey_Image * img, int filter_dim);

grey_Image * compute_MinConvolution(grey_Image * img, int filter_dim);

grey_Image * compute_MaxConvolution(grey_Image * img, int filter_dim);

#endif