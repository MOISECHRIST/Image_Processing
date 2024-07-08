#ifndef CONTOUR_DETECTION_H
#define CONTOUR_DETECTION_H

#include "grey_Image.h"
#define M 3

typedef struct FiltreGradiant {
    int filter_dim;
    float filter1[M][M];
    float filter2[M][M];
} FiltreGradiant;

typedef struct FiltreLaplacient {
    int filter_dim;
    float filter[M][M];
} FiltreLaplacient;

FiltreGradiant * RobertsFilter_init();

FiltreGradiant * PrewittFilter_init();

FiltreGradiant * SobelFilter_init();

FiltreLaplacient * first_LaplacienFilter_init();

FiltreLaplacient * second_LaplacienFilter_init();

grey_Image * compute_Gradiant(grey_Image * img, FiltreGradiant * filter);

grey_Image * compute_Laplacien(grey_Image * img, FiltreLaplacient * filter);

grey_Image * seuillage_contours(grey_Image * img, int seuil);

#endif