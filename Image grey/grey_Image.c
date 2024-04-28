#include "grey_Image.h"
#include <math.h>
#include <string.h>

//Read the image from file path
void read_image(char *filename, , grey_Image *img){
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
<<<<<<< HEAD
    int mini=img->pixelmax;
    for (i = 0; i < img->longeur; ++i) {
        for (j = 0; j < img->largeur; ++j) {
            img->pixels[i][j] = fgetc(pgmFile);
            if((img->pixels[i][j])<mini)
                mini=(img->pixels[i][j]);
=======

    int mini=255;
    for (i = 0; i < img->longeur; ++i) {
        for (j = 0; j < img->largeur; ++j) {
            img->pixels[i][j] = fgetc(pgmFile);
            if(mini>(img->pixels[i][j]))
                mini=img->pixels[i][j];
>>>>>>> 2ad3854c666482ad2cad41b27af60e2ca7388bc8
        }
    }

    img->pixelmin=mini;
<<<<<<< HEAD
=======

>>>>>>> 2ad3854c666482ad2cad41b27af60e2ca7388bc8

    fclose(pgmFile);
}

//save the image in pgm file
void save_image(grey_Image *){

}

//Display image
void display_image(grey_Image *img){
    int i,j;
    printf("%s \n",img->version);
    printf("%d %d\n", img->longeur, img->largeur);
    printf("%d %d\n", img->pixelmax, img->pixelmin);
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


//Compute the image's contrast as relative distance between min and max 
float contract_minmax(grey_Image *img){
    return (img->pixelmax-img->pixelmin)/(img->pixelmax+img->pixelmin);
}

//Compute lineair processing with saturation
<<<<<<< HEAD
grey_Image * linear_processing_with_saturation(grey_Image *img, int Smax, int Smin){
=======
void linear_processing_with_saturation(grey_Image *img, int Smax, int Smin){
    int res[255],i,j;
    for(i=0;i<255;i++){
        res[i]=255*(i-Smin)/(Smax-Smin);
    }
>>>>>>> 2ad3854c666482ad2cad41b27af60e2ca7388bc8

    img->pixelmin=(int)255*(img->pixelmin-Smin)/(Smax-Smin);
    img->pixelmax=(int)255*(img->pixelmax-Smin)/(Smax-Smin);

    for(i=0;i<img->largeur;i++){
        for(j=0;j<img->longueur;j++)
            img->pixels[i][j]=res[img->pixels[i][j]];
    }
}

//Compute lineair processing
<<<<<<< HEAD
grey_Image * linear_processing(grey_Image *img){

}

//Compute the histogram egalization
grey_Image * histogram_egalization(grey_Image *img){
=======
void  linear_processing(grey_Image *img){
    int Smin,Smax;
    Smin=img->pixelmin;
    Smax=img->pixelmax;
    linear_processing_with_saturation(img, Smax, Smin);
}

>>>>>>> 2ad3854c666482ad2cad41b27af60e2ca7388bc8

//image addition 
grey_Image * image_addition(grey_Image img1, grey_Image img2){
    if((img1->longueur!=img2->longueur)||(img1->largeur!=img2->largeur)){
        printf("[ERROR]::Les images n'ont pas les meme dimensions...");
        exit(1);
    }
    grey_Image img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img1->longueur;
    img_res->largeur=img1->largeur;
    strcpy(img_res->version,img1->version);
    int i,j;
    int mini=255,maxi=0;
    for(i=0;i<img_res->largeur;i++){
        for(j=0;j<img_res->largeur;j++){

            img_res->pixels[i][j]=(img1->pixels[i][j]+img2->pixels[i][j])>=255?255:(img1->pixels[i][j]+img2->pixels[i][j]);
            if(img_res->pixels[i][j]>maxi)
                maxi=img_res->pixels[i][j];
            if(img_res->pixels[i][j]<mini)
                mini=img_res->pixels[i][j];
        }
    }
    img_res->pixelmax=maxi;
    img_res->pixelmin=mini;
    return img_res;
}

<<<<<<< HEAD
//images addition 
grey_Image * image_addition(grey_Image *img1, grey_Image *img2){

}

//images subtraction 
grey_Image * image_subtraction(grey_Image  *img1, grey_Image  *img2){
=======
//image addition 
grey_Image * image_subtraction(grey_Image *img1, grey_Image *img2){
    if((img1->longueur!=img2->longueur)||(img1->largeur!=img2->largeur)){
        printf("[ERROR]::Les images n'ont pas les meme dimensions...");
        exit(1);
    }
    grey_Image img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img1->longueur;
    img_res->largeur=img1->largeur;
    strcpy(img_res->version,img1->version);
    int i,j;
    int mini=255,maxi=0;
    for(i=0;i<img_res->largeur;i++){
        for(j=0;j<img_res->largeur;j++){
>>>>>>> 2ad3854c666482ad2cad41b27af60e2ca7388bc8

            img_res->pixels[i][j]=(img1->pixels[i][j]-img2->pixels[i][j])<=0?0:(img1->pixels[i][j]+img2->pixels[i][j]);
            if(img_res->pixels[i][j]>maxi)
                maxi=img_res->pixels[i][j];
            if(img_res->pixels[i][j]<mini)
                mini=img_res->pixels[i][j];
        }
    }
    img_res->pixelmax=maxi;
    img_res->pixelmin=mini;
    return img_res;
}

//image multiplication with a ratio
<<<<<<< HEAD
grey_Image * image_multiplication(grey_Image *img, float){
=======
grey_Image * image_multiplication(grey_Image *img, float ratio){
    grey_Image img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img->longueur;
    img_res->largeur=img->largeur;
    strcpy(img_res->version,img->version);
    int i,j;
    int mini=255,maxi=0;
    for(i=0;i<img_res->largeur;i++){
        for(j=0;j<img_res->largeur;j++){
>>>>>>> 2ad3854c666482ad2cad41b27af60e2ca7388bc8

            img_res->pixels[i][j]=(int)(img->pixels[i][j]*ratio)>255?255:(img->pixels[i][j]*ratio);
            if(img_res->pixels[i][j]>maxi)
                maxi=img_res->pixels[i][j];
            if(img_res->pixels[i][j]<mini)
                mini=img_res->pixels[i][j];
        }
    }
    img_res->pixelmax=maxi;
    img_res->pixelmin=mini;
    return img_res;
}

//Buid the image's histogram
<<<<<<< HEAD
Histogram * build_histogram(grey_Image *img){
=======
Histogram build_histogram(grey_Image *img){
    Histogram hist=init_Histogram();
    int i,j;
    int node=0;
    for(i=0;i<img_res->largeur;i++){
        for(j=0;j<img_res->largeur;j++){
            node = img->pixels[i][j];
            hist=add_node(hist,node);
        }
    }
    return hist;
}
>>>>>>> 2ad3854c666482ad2cad41b27af60e2ca7388bc8

//Compute the histogram egalization
grey_Image * histogram_egalization(grey_Image *img){
    
}