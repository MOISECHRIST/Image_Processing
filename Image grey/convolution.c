#include "convolution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
The user entry the different element of filter
- dimension of filter
- Elements into the filter
 */
float ** entry_ConvFilter(int dim){
    float ** filter;
    int i,j;
    
    filter= (float **)malloc(sizeof(float)*dim);
    for(i=0; i<dim; i++)
        filter[i]= (float *)malloc(sizeof(float)*dim);

    for(i=0; i<dim; i++){
        for(j=0; j<dim; j++){
            printf("Entrer l'element %d de la colonne %d : ", j+1, i+1);
            scanf("%f", &filter[i][j]);
        }
    }
    return filter;
}

/*
The user entry the filter's dimensions
and the program return the mean filter of these dimensions 
 */
float ** create_MeanConvFilter(int dim){
    float ** filter;
    int i,j;

    filter= (float **)malloc(sizeof(float)*dim);
    for(i=0; i<dim; i++)
        filter[i]= (float *)malloc(sizeof(float)*dim);

    for(i=0; i<dim; i++){
        for(j=0; j<dim; j++){
            filter[i][j]=1/dim;
        }
    }
    return filter;
}

grey_Image * compute_Convolution(grey_Image * img, float ** filter, int filter_dim){

    if(filter_dim > img->largeur || filter_dim > img->longueur){
        printf("[ERROR]::Les dimensions du filtres ne doivent pas être supérieurs à celle de l'image...");
        exit(1);
    }
    int i,j,k, n, tmp=filter_dim/2;
    float calcul;
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img->longueur;
    img_res->largeur=img->largeur;
    strcpy(img_res->version,img->version);

    img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
    for(i = 0; i < img_res->longueur; i++)
        img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

    for (i = 0; i <= img->longueur; ++i) {
        for (j = 0; j <= img->largeur; ++j) {
            if(i >= img->longueur-tmp || i < tmp || j < tmp || j >= img->largeur-tmp){
                img_res->pixels[i][j]=0;
            }
            else{
                calcul=0;
                for(k=0; k<filter_dim; k++){
                    for(n=0; n<filter_dim; n++){
                        calcul+=filter[k][n]*img->pixels[i-tmp+k][j-tmp+n];
                    }
                }
                img_res->pixels[i][j]=calcul;
            }
        }
        
    }
    img_res->pixelmax=255;
    img_res->pixelmin=0;
    return img_res;
}

void init_vector(unsigned char * vector, int length){
    int i;
    for(i=0; i< length; i++){
        vector[i]=0;
    }
}

unsigned char compute_Median(unsigned char * vector, int length){
    unsigned char min_val;
    int min_id=0, i, j;
    for(i=0; i<length/2; i++){
        for(j=i+1; j<length; j++){
            if(vector[j]<vector[min_id]){
                min_id=j;
            }
        }
        if(min_id!=i){
            min_val=vector[min_id];
            vector[min_id]=vector[i];
            vector[i]=min_val;
        }
    }
    i=(length/2)-1;
    return vector[i];
}

grey_Image * compute_MedianConvolution(grey_Image * img, int filter_dim){
    if(filter_dim > img->largeur || filter_dim > img->longueur){
        printf("Les dimensions du filtres sont supérieurs à celle de l'image");
        return NULL;
    }
    int i,j,k, n, tmp=filter_dim/2;
    unsigned char *calcul=(unsigned char *)malloc(sizeof(unsigned char)*filter_dim*filter_dim);
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img->longueur;
    img_res->largeur=img->largeur;
    strcpy(img_res->version,img->version);

    img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
    for(i = 0; i < img_res->longueur; i++)
        img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

    for (i = 0; i <= img->longueur; ++i) {
        for (j = 0; j <= img->largeur; ++j) {
            if(i >= img->longueur-tmp || i < tmp || j < tmp || j >= img->largeur-tmp){
                img_res->pixels[i][j]=0;
            }
            else{
                init_vector(calcul, filter_dim*filter_dim);
                for(k=0; k<filter_dim; k++){
                    for(n=0; n<filter_dim; n++){
                        calcul[k*filter_dim+n]=img->pixels[i-tmp+k][j-tmp+n];
                    }
                }
                img_res->pixels[i][j]=compute_Median(calcul, filter_dim*filter_dim);
            }
        }
    }
    img_res->pixelmax=255;
    img_res->pixelmin=0;
    return img_res;

}

unsigned char compute_Extremum(unsigned char * vector, int length, int is_max){
    int ext_id=0, i, j;
    if(is_max==0){
        for(j=1; j<length; j++){
            if(vector[j]<vector[ext_id]){
                ext_id=j;
            }
        }
    }
    else{
        for(j=1; j<length; j++){
            if(vector[j]>vector[ext_id]){
                ext_id=j;
            }
        }
    }
    
    return vector[ext_id];
}

grey_Image * compute_MinConvolution(grey_Image * img, int filter_dim){
    if(filter_dim > img->largeur || filter_dim > img->longueur){
        printf("Les dimensions du filtres sont supérieurs à celle de l'image");
        return NULL;
    }
    int i,j,k, n, tmp=filter_dim/2;
    unsigned char *calcul=(unsigned char *)malloc(sizeof(unsigned char)*filter_dim*filter_dim);
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img->longueur;
    img_res->largeur=img->largeur;
    strcpy(img_res->version,img->version);

    img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
    for(i = 0; i < img_res->longueur; i++)
        img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

    for (i = 0; i <= img->longueur; ++i) {
        for (j = 0; j <= img->largeur; ++j) {
            if(i >= img->longueur-tmp || i < tmp || j < tmp || j >= img->largeur-tmp){
                img_res->pixels[i][j]=0;
            }
            else{
                init_vector(calcul, filter_dim*filter_dim);
                for(k=0; k<filter_dim; k++){
                    for(n=0; n<filter_dim; n++){
                        calcul[k*filter_dim+n]=img->pixels[i-tmp+k][j-tmp+n];
                    }
                }
                img_res->pixels[i][j]=compute_Extremum(calcul, filter_dim*filter_dim, 0);
            }
        }
    }

    img_res->pixelmax=255;
    img_res->pixelmin=0;
    return img_res;
}

grey_Image * compute_MaxConvolution(grey_Image * img, int filter_dim){
    if(filter_dim > img->largeur || filter_dim > img->longueur){
        printf("Les dimensions du filtres sont supérieurs à celle de l'image");
        return NULL;
    }
    int i,j,k, n, tmp=filter_dim/2;
    unsigned char *calcul=(unsigned char *)malloc(sizeof(unsigned char)*filter_dim*filter_dim);
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img->longueur;
    img_res->largeur=img->largeur;
    strcpy(img_res->version,img->version);

    img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
    for(i = 0; i < img_res->longueur; i++)
        img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

    for (i = 0; i <= img->longueur; ++i) {
        for (j = 0; j <= img->largeur; ++j) {
            if(i >= img->longueur-tmp || i < tmp || j < tmp || j >= img->largeur-tmp){
                img_res->pixels[i][j]=0;
            }
            else{
                init_vector(calcul, filter_dim*filter_dim);
                for(k=0; k<filter_dim; k++){
                    for(n=0; n<filter_dim; n++){
                        calcul[k*filter_dim+n]=img->pixels[i-tmp+k][j-tmp+n];
                    }
                }
                img_res->pixels[i][j]=compute_Extremum(calcul, filter_dim*filter_dim, 1);
            }
        }
    }

    img_res->pixelmax=255;
    img_res->pixelmin=0;
    return img_res;
}