#include "contour_detection.h"
#include "convolution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FiltreGradiant * RobertsFilter_init(){
    FiltreGradiant * filter=malloc(sizeof(FiltreGradiant));
    filter->filter_dim=2;

    filter->filter1[0][0]=1;
    filter->filter1[0][1]=0;
    filter->filter1[1][0]=0;
    filter->filter1[1][1]=-1;

    filter->filter2[0][0]=0;
    filter->filter2[0][1]=1;
    filter->filter2[1][0]=-1;
    filter->filter2[1][1]=0;

    return filter;
}

FiltreGradiant * PrewittFilter_init(){
    FiltreGradiant * filter=malloc(sizeof(FiltreGradiant));
    filter->filter_dim=3;

    filter->filter1[0][0]=-1;
    filter->filter1[0][1]=-1;
    filter->filter1[0][2]=-1;
    filter->filter1[1][0]=0;
    filter->filter1[1][1]=0;
    filter->filter1[1][2]=0;
    filter->filter1[2][0]=1;
    filter->filter1[2][1]=1;
    filter->filter1[2][2]=1;

    filter->filter2[0][0]=-1;
    filter->filter2[0][1]=0;
    filter->filter2[0][2]=1;
    filter->filter2[1][0]=-1;
    filter->filter2[1][1]=0;
    filter->filter2[1][2]=1;
    filter->filter2[2][0]=-1;
    filter->filter2[2][1]=0;
    filter->filter2[2][2]=1;

    return filter;
}

FiltreGradiant * SobelFilter_init(){
    FiltreGradiant * filter=malloc(sizeof(FiltreGradiant));
    filter->filter_dim=3;

    filter->filter1[0][0]=-1;
    filter->filter1[0][1]=-2;
    filter->filter1[0][2]=-1;
    filter->filter1[1][0]=0;
    filter->filter1[1][1]=0;
    filter->filter1[1][2]=0;
    filter->filter1[2][0]=1;
    filter->filter1[2][1]=2;
    filter->filter1[2][2]=1;

    filter->filter2[0][0]=-1;
    filter->filter2[0][1]=0;
    filter->filter2[0][2]=1;
    filter->filter2[1][0]=-2;
    filter->filter2[1][1]=0;
    filter->filter2[1][2]=2;
    filter->filter2[2][0]=-1;
    filter->filter2[2][1]=0;
    filter->filter2[2][2]=1;

    return filter;
}

FiltreLaplacient * first_LaplacienFilter_init(){
    FiltreLaplacient * filter=malloc(sizeof(FiltreLaplacient));
    filter->filter_dim=3;

    filter->filter[0][0]=0;
    filter->filter[0][1]=1;
    filter->filter[0][2]=0;
    filter->filter[1][0]=1;
    filter->filter[1][1]=-4;
    filter->filter[1][2]=1;
    filter->filter[2][0]=0;
    filter->filter[2][1]=1;
    filter->filter[2][2]=0;

    return filter;
}

FiltreLaplacient * second_LaplacienFilter_init(){
    FiltreLaplacient * filter=malloc(sizeof(FiltreLaplacient));
    filter->filter_dim=3;

    filter->filter[0][0]=1;
    filter->filter[0][1]=1;
    filter->filter[0][2]=1;
    filter->filter[1][0]=1;
    filter->filter[1][1]=-8;
    filter->filter[1][2]=1;
    filter->filter[2][0]=1;
    filter->filter[2][1]=1;
    filter->filter[2][2]=1;

    return filter;
}

grey_Image * compute_Gradiant(grey_Image * img, FiltreGradiant * filter){
    /*
    - Convolution avec le 1er filtre
    - Convolution avec le 2nd filtre
    - Somme des valeurs absolue des 2 convolutions 
    */

    grey_Image *gx=malloc(sizeof(grey_Image));
    grey_Image *gy=malloc(sizeof(grey_Image));
    grey_Image *img_res=malloc(sizeof(grey_Image));

    float ** filter1, **filter2;
    int i,j;

    filter1= (float **)malloc(sizeof(float)*filter->filter_dim);
    for(i=0; i<filter->filter_dim; i++)
        filter1[i]= (float *)malloc(sizeof(float)*filter->filter_dim);

    for(i=0; i<filter->filter_dim; i++)
        for(j=0; j< filter->filter_dim; j++)
            filter1[i][j]=filter->filter1[i][j];

    filter2= (float **)malloc(sizeof(float)*filter->filter_dim);
    for(i=0; i<filter->filter_dim; i++)
        filter2[i]= (float *)malloc(sizeof(float)*filter->filter_dim);

    for(i=0; i<filter->filter_dim; i++)
        for(j=0; j< filter->filter_dim; j++)
            filter2[i][j]=filter->filter2[i][j];

    gx=compute_Convolution(img, filter1, filter->filter_dim);
    gy=compute_Convolution(img, filter2, filter->filter_dim);

    for(i=0; i< img->longueur; i++){
        for(j=0;j<img->largeur; j++){
            if(gx->pixels[i][j]<0){
                gx->pixels[i][j]=(-1)*gx->pixels[i][j];
            }
            if(gy->pixels[i][j]<0){
                gy->pixels[i][j]=(-1)*gy->pixels[i][j];
            }
        }
    }
    img_res=image_addition(gx, gy);

    img_res->pixelmax=255;
    img_res->pixelmin=0;
    return img_res;
}

grey_Image * compute_Laplacien(grey_Image * img, FiltreLaplacient * filter){
    /*
    - Convolution avec le filtre du laplacien
    - Valeur absolue du laplacien de l'image 
    - Le contour correspond au passage sur le chiffre 0 du laplacien de l'image
    */

    grey_Image *img_res=malloc(sizeof(grey_Image));
    int i,j;
    float ** filter_;

    filter_= (float **)malloc(sizeof(float)*filter->filter_dim);
    for(i=0; i<filter->filter_dim; i++)
        filter_[i]= (float *)malloc(sizeof(float)*filter->filter_dim);

    for(i=0; i<filter->filter_dim; i++)
        for(j=0; j< filter->filter_dim; j++)
            filter_[i][j]=filter->filter[i][j];

    img_res=compute_Convolution(img, filter_, filter->filter_dim);
    

    for(i=0; i< img->longueur; i++){
        for(j=0;j<img->largeur; j++){
            if(img_res->pixels[i][j]<0){
                img_res->pixels[i][j]=(-1)*img_res->pixels[i][j];
            }
        }
    }

    img_res->pixelmax=255;
    img_res->pixelmin=0;
    return img_res;
}

grey_Image * seuillage_contours(grey_Image * img, int seuil){
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img->longueur;
    img_res->largeur=img->largeur;
    strcpy(img_res->version,img->version);
    int i,j;

    img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
    for(i = 0; i < img_res->longueur; i++)
        img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

    for(i=0; i< img->longueur; i++){
        for(j=0;j<img->largeur; j++){
            if(img_res->pixels[i][j]>seuil){
                img_res->pixels[i][j]=255;
            }
            else{
                img_res->pixels[i][j]=img->pixels[i][j];
            }
        }
    }
    
    img_res->pixelmax=255;
    img_res->pixelmin=0;
    return img_res;
}