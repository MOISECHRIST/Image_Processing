#include "grey_Image.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
    grey_Image *img=malloc(sizeof(grey_Image));
    grey_Image *img1=malloc(sizeof(grey_Image));
    char *image_name="image.pgm";
    char *image_output_name="img_output.pgm";
    read_image(image_name, img);
    img1=img;
    float cont_var = contrast_variance(img);
    float cont_minmax= contract_minmax(img);
    float lum=luminance(img);
    printf("Avant:\n");
    printf("Image Name : %s\n", image_name);
    printf("CONTRASTE :\n ->Variance : %f\n ->MinMax : %f\n",cont_var, cont_minmax);
    printf("LUMINANCE : %f\n\n",lum);

    linear_processing_with_saturation(img, 200, 20);

    cont_var = contrast_variance(img);
    cont_minmax= contract_minmax(img);
    lum=luminance(img);

    printf("Apres:\n");

    img = image_multiplication(img, 4.75);
    img=image_subtraction(img,img1);
    save_image(img,image_output_name);
    //Histogram hist=build_histogram(img);
    //print_histogram(hist, 5);
    //print_hist_in_file(hist);
    return 0;
}