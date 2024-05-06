#ifndef GREY_IMAGE_H
#define GREY_IMAGE_H
#include <stdio.h>
#include <stdlib.h>

#include "histogram.h"
// High size of grey
#define N 255

//Definition of the image structure
typedef struct grey_Image {
    int largeur;
    int longueur;
    char version[3];
    int pixelmax;
    int pixelmin;
    unsigned char **pixels;
} grey_Image;

//Read the image from file path
void read_image(char *, grey_Image *);

//save the image in pgm file
void save_image(grey_Image *);

//Display image
void display_image(grey_Image *);

//Compute the image's luminance
float luminance(grey_Image *);

//Compute the image's contrast as variance of pixels
float contrast_variance(grey_Image *);

//Compute the image's contrast as relative distance between min and max 
float contract_minmax(grey_Image *);

//Compute lineair processing with saturation
void linear_processing_with_saturation(grey_Image *, int, int); 

//Compute lineair processing
void linear_processing(grey_Image *);

//images addition 
grey_Image * image_addition(grey_Image *, grey_Image *);

//image subtraction 
grey_Image * image_subtraction(grey_Image *, grey_Image *);

//image multiplication with a ratio
grey_Image * image_multiplication(grey_Image *, float);

//Buid the image's histogram
Histogram build_histogram(grey_Image *);

//Compute the histogram egalization
grey_Image * histogram_egalization(grey_Image *);

#endif