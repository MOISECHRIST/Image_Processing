#include "grey_Image.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){

    //Read image
    grey_Image *img=malloc(sizeof(grey_Image));
    grey_Image *img1=malloc(sizeof(grey_Image));
    char *image_name="aerial.512.pgm";
    read_image(image_name, img);
    
    //Image summary
    printf("Image summary\n");
    printf(" - Version : %s\n - Dim : %d %d\n - Pixel max: %d\n - Pixel min : %d\n",img->version, img->longueur, img->largeur, img->pixelmax, img->pixelmin);
    img1=img;
    int bins=30, grey_level=70;
    Histogram hist;

    //Compute Luminance and Contraste of raw image
    float cont_var = contrast_variance(img);
    float cont_minmax= contract_minmax(img);
    float lum=luminance(img);
    hist=build_histogram(img);
    printf("Before: raw pgm image\n");
    printf("Image Name : %s\n", image_name);
    printf("CONTRASTE :\n ->Variance : %f\n ->MinMax : %f\n",cont_var, cont_minmax);
    printf("LUMINANCE : %f\n\n",lum);
    print_hist_into_pgm(hist, bins, "histogram_raw_img.pgm",grey_level);
    
    //Compute linear processing with saturation of my image
    linear_processing_with_saturation(img, 150, 50);
    
    //Compute Luminance and Contraste of new image with saturation
    cont_var = contrast_variance(img);
    cont_minmax= contract_minmax(img);
    lum=luminance(img);
    printf("After: linear processing with saturation\n");
    printf("Image Name : %s\n", image_name);
    printf("CONTRASTE :\n ->Variance : %f\n ->MinMax : %f\n",cont_var, cont_minmax);
    printf("LUMINANCE : %f\n\n",lum);
    save_image(img,"image_saturation.pgm");
    hist=build_histogram(img);
    print_hist_into_pgm(hist, bins, "histogram_saturation_img.pgm",grey_level);

    //Compute histogram egalization
    histogram_egalization(img1);
   
    //Compute Luminance and Contraste of new image with histogram egalization
    cont_var = contrast_variance(img1);
    cont_minmax= contract_minmax(img1);
    lum=luminance(img1);
    printf("After: histogram egalization\n");
    printf("Image Name : %s\n", image_name);
    printf("CONTRASTE :\n ->Variance : %f\n ->MinMax : %f\n",cont_var, cont_minmax);
    printf("LUMINANCE : %f\n\n",lum);
    save_image(img1,"image_hist_egal.pgm");
    hist=build_histogram(img1);
    print_hist_into_pgm(hist, bins, "histogram_egalization_img.pgm",grey_level);

    return 0;
}