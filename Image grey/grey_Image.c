#include "grey_Image.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Read the image from file path
void read_image(char *filename,grey_Image *img){
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
    img->longueur=tmp;
    fscanf(pgmFile, "%d", &tmp);
    img->pixelmax=tmp;

    img->pixels = (unsigned char **)malloc(img->longueur * sizeof(unsigned char *));
    for(i = 0; i < img->longueur; i++)
        img->pixels[i] = (unsigned char*)malloc(img->largeur * sizeof(unsigned char));

    fgetc(pgmFile); // Read white-space

    int mini=255;
    for (i = 0; i < img->longueur; ++i) {
        for (j = 0; j < img->largeur; ++j) {
            img->pixels[i][j] = fgetc(pgmFile);
            if(mini>(img->pixels[i][j]))
                mini=img->pixels[i][j];
        }
    }

    img->pixelmin=mini;

    fclose(pgmFile);
}

//save the image in pgm file
void save_image(grey_Image *img, char *filename){
    FILE* pgmFile;
    pgmFile = fopen(filename, "wb");
    if (pgmFile == NULL) {
        perror("cannot open file to read");
        exit(EXIT_FAILURE);
    }

    fprintf(pgmFile,"%s\n",img->version);
    fprintf(pgmFile,"%d %d\n",img->largeur, img->longueur);
    fprintf(pgmFile,"%d\n",img->pixelmax);

    unsigned char *all_pixels=(unsigned char *)malloc(sizeof(unsigned char *)*(img->largeur * img->longueur));
    int i,j;
    for(i=0;i<img->longueur;i++){
        for(j=0;j<img->largeur;j++){
            all_pixels[i*img->largeur+j]=img->pixels[i][j];
        }
    }

    fwrite(all_pixels, sizeof(unsigned char), (img->largeur * img->longueur), pgmFile);
}

//Display image
void display_image(grey_Image *img){
    int i,j;
    printf("%s \n",img->version);
    printf("%d %d\n", img->longueur, img->largeur);
    printf("%d\n", img->pixelmax);
    for (i = 0; i < img->longueur; ++i) {
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
    for (i = 0; i < img->longueur; ++i) {
        for (j = 0; j < img->largeur; ++j) {
            lum+=img->pixels[i][j];
        }
    }

    return lum/(img->longueur*img->largeur);
}

//Compute the image's contrast as variance of pixels
float contrast_variance(grey_Image *img){
    float lum=luminance(img), cont=0;
    int i,j;
    for (i = 0; i < img->longueur; ++i) {
        for (j = 0; j < img->largeur; ++j) {
            cont+= pow((img->pixels[i][j]-lum),2);
        }
    }    
    return sqrt(cont/(img->longueur*img->largeur));
}


//Compute the image's contrast as relative distance between min and max 
float contract_minmax(grey_Image *img){
    return (img->pixelmax-img->pixelmin)/(img->pixelmax+img->pixelmin);
}

//Compute lineair processing with saturation
void linear_processing_with_saturation(grey_Image *img, int Smax, int Smin){
    int res[255],i,j;
    for(i=0;i<255;i++){
        if(i<=Smax && i>=Smin){
            res[i]=255*(i-Smin)/(Smax-Smin);
        }
        else{
            res[i]=i;
        }
    }

    img->pixelmin=img->pixelmin<=Smin?img->pixelmin:(int)255*(img->pixelmin-Smin)/(Smax-Smin);
    img->pixelmax=img->pixelmax>=Smax?img->pixelmax:(int)255*(img->pixelmax-Smin)/(Smax-Smin);

    for(i=0;i<img->largeur;i++){
        for(j=0;j<img->longueur;j++)
            img->pixels[i][j]=res[img->pixels[i][j]];
    }
}

//Compute lineair processing
void  linear_processing(grey_Image *img){
    int Smin,Smax;
    Smin=img->pixelmin;
    Smax=img->pixelmax;
    linear_processing_with_saturation(img, Smax, Smin);
}


//image addition 
grey_Image * image_addition(grey_Image *img1, grey_Image *img2){
    if((img1->longueur!=img2->longueur)||(img1->largeur!=img2->largeur)){
        printf("[ERROR]::Les images n'ont pas les meme dimensions...");
        exit(1);
    }
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img1->longueur;
    img_res->largeur=img1->largeur;
    strcpy(img_res->version,img1->version);
    int i,j;
    int mini=255,maxi=0;

    img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
    for(i = 0; i < img_res->longueur; i++)
        img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));
        
    for(i=0;i<img_res->longueur;i++){
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

//image addition 
grey_Image * image_subtraction(grey_Image *img1, grey_Image *img2){
    if((img1->longueur!=img2->longueur)||(img1->largeur!=img2->largeur)){
        printf("[ERROR]::Les images n'ont pas les meme dimensions...");
        exit(1);
    }
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img1->longueur;
    img_res->largeur=img1->largeur;
    strcpy(img_res->version,img1->version);
    int i,j;
    int mini=255,maxi=0;

    img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
    for(i = 0; i < img_res->longueur; i++)
        img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

    for(i=0;i<img_res->longueur;i++){
        for(j=0;j<img_res->largeur;j++){

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
grey_Image * image_multiplication(grey_Image *img, float ratio){
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img->longueur;
    img_res->largeur=img->largeur;
    strcpy(img_res->version,img->version);
    int i,j;
    int mini=255,maxi=0;
    
    img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
    for(i = 0; i < img_res->longueur; i++)
        img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

    for(i=0;i<img_res->longueur;i++){
        for(j=0;j<img_res->largeur;j++){

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
Histogram build_histogram(grey_Image *img){
    Histogram hist=init_Histogram();
    int i,j;
    int node=0;
    for(i=0;i<img->longueur;i++){
        for(j=0;j<img->largeur;j++){
            node = img->pixels[i][j];
            hist=add_node(hist,node);
        }
    }
    return hist;
}

//Compute the histogram egalization
void histogram_egalization(grey_Image *img){
    Histogram hist = build_histogram(img);
    int i,j;
    float densite[N];
    
    densite[0]=hist.freq_table[0];
    for(i=1;i<N;i++){
        densite[i]=densite[i-1]+hist.freq_table[i];
    }

    for(i=0;i<img->longueur;i++){
        for(j=0;j<img->largeur;j++){
            img->pixels[i][j]=(unsigned char)((int)(255*(densite[img->pixels[i][j]]/hist.total_freq)));
        }
    }
}