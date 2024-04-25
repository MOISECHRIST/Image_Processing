#include "grey_Image.h"
#include <math.h>

//Read the image from file path
grey_Image read_image(char *filename, , grey_Image *img){
    FILE* pgmFile;
    int i, j, tmp=0;

    pgmFile = fopen(filename, "rb");
    if (pgmFile == NULL) {
        perror("cannot open file to read");
        exit(EXIT_FAILURE);
    }
    
    fscanf(pgmFile, "%s\n", img->version);
    fscanf(pgmFile, "%d", &tmp);
    img->largeur=tmp;
    fscanf(pgmFile, "%d", &tmp);
    img->longeur=tmp;
    fscanf(pgmFile, "%d", &tmp);
    img->pixelmax=tmp;

    img->pixels = (int**)malloc(img->longeur * sizeof(int*));
    for(i = 0; i < img->longeur; i++)
        img->pixels[i] = (int*)malloc(img->largeur * sizeof(int));

    fgetc(pgmFile); // Read white-space

    for (i = 0; i < img->longeur; ++i) {
        for (j = 0; j < img->largeur; ++j) {
            img->pixels[i][j] = fgetc(pgmFile);
        }
    }


    fclose(pgmFile);
}

//Display image
void display_image(grey_Image *img){
    int i,j;
    printf("%s \n",img->version);
    printf("%d %d\n", img->longeur, img->largeur);
    printf("%d\n", img->pixelmax);
    for (i = 0; i < img->longeur; ++i) {
        for (j = 0; j < img->largeur; ++j) {
            printf("%d ", img->pixels[i][j]);
        }
        printf("\n");
    }
}

//Compute the image's luminance
float luminance(grey_Image *img){
    float lum=0;
    int i,j;
    for (i = 0; i < img->longeur; ++i) {
        for (j = 0; j < img->largeur; ++j) {
            lum+=img->pixels[i][j];
        }
    }

    return lum/(img->longeur*img->largeur);
}

//Compute the image's contrast as variance of pixels
float contrast_variance(grey_Image *img){
    float lum=luminance(img), cont=0;
    int i,j;
    for (i = 0; i < img->longeur; ++i) {
        for (j = 0; j < img->largeur; ++j) {
            cont+= pow((img->pixels[i][j]-lum),2);
        }
    }    
    return sqrt(cont/(img->longeur*img->largeur));
}

int find_min(grey_Image *){
    
}
//Compute the image's contrast as relative distance between min and max 
float contract_minmax(grey_Image){

}

//Compute lineair processing with saturation
grey_Image  linear_processing_with_saturation(grey_Image, int, int){

}

//Compute lineair processing
grey_Image  linear_processing(grey_Image){

}

//Compute the histogram egalization
grey_Image  histogram_egalization(grey_Image){

}

//image addition 
grey_Image  image_addition(grey_Image, grey_Image){

}

//image multiplication with a ratio
grey_Image  image_multiplication(grey_Image, float){

}

//Buid the image's histogram
Histogram build_histogram(grey_Image){

}