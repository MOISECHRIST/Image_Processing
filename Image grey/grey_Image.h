#include "histogram.h"

#ifndef GREY_IMAGE_H
#define GREY_IMAGE_H

//Size of image
#define N 255

//Definition of the image structure
typedef struct  grey_Image
{
    int largeur;
    int longeur;
    int pixels[N][N];

} grey_Image;

//Read the image from file path
grey_Image read_image(char *);

//Display image
void display_image(grey_Image);

//Compute the image's luminance
float luminance(grey_Image);

//Compute the image's contrast as variance of pixels
float contrast_variance(grey_Image);

//Compute the image's contrast as relative distance between min and max 
float contract_minmax(grey_Image);

//Compute lineair processing with saturation
grey_Image  linear_processing_with_saturation(grey_Image, int, int); 

//Compute lineair processing
grey_Image  linear_processing(grey_Image);

//Compute the histogram egalization
grey_Image  histogram_egalization(grey_Image);

//image addition 
grey_Image  image_addition(grey_Image, grey_Image);

//image multiplication with a ratio
grey_Image  image_multiplication(grey_Image, float);

//Buid the image's histogram
Histogram build_histogram(grey_Image);

#endif