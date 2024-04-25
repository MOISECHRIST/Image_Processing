#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct grey_Image {
    int largeur;
    int longeur;
    char version[3];
    int pixelmax;
    int pixelmin;
    int **pixels;
} grey_Image;


void readPGM(const char* filename, grey_Image* img) {
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
    int mini=img->pixelmax;
    for (i = 0; i < img->longeur; ++i) {
        for (j = 0; j < img->largeur; ++j) {
            img->pixels[i][j] = fgetc(pgmFile);
            if((img->pixels[i][j])<mini)
                mini=(img->pixels[i][j]);
        }
    }

    img->pixelmin=mini;


    fclose(pgmFile);
}

void printImage(grey_Image *img){
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

int main() {
    printf("Debut\n");
    grey_Image *img=malloc(sizeof(grey_Image));
    readPGM("image.pgm", img);
    printImage(img);
    return 0;
}
