#include "grey_Image.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){

    //Read image
    grey_Image *img=malloc(sizeof(grey_Image));
    grey_Image *img2=malloc(sizeof(grey_Image));
    grey_Image *img1=malloc(sizeof(grey_Image));
    char *image_name="3things.256.pgm";
    read_image(image_name, img);
    image_name="3objects.256.pgm";
    read_image(image_name, img1);
    int bins=30, grey_level=70, ech=1;
    Histogram hist;
    histogram_egalization(img);
    //Image summary
    printf("Image summary\n");
    printf(" - Version : %s\n - Dim : %d %d\n - Pixel max: %d\n - Pixel min : %d\n",img->version, img->longueur, img->largeur, img->pixelmax, img->pixelmin);
    printf(" - Version : %s\n - Dim : %d %d\n - Pixel max: %d\n - Pixel min : %d\n",img1->version, img1->longueur, img1->largeur, img1->pixelmax, img1->pixelmin);

    img2=image_subtraction(img,img1);
    save_image(img2,"image_sub_things_objects.pgm");

    img2=image_subtraction(img1,img);
    save_image(img2,"image_sub_objects_things.pgm");

    image_name="3things.256.pgm";
    read_image(image_name, img);
    img2=image_addition(img,img2);
    save_image(img2,"image_add_things_objects.pgm");
    return 0;
}