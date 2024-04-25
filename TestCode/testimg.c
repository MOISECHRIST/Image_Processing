#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10000

typedef struct grey_Image {
    int largeur;
    int longeur;
    char version[3];
    int pixelmax;
    int pixels[N][N];
} grey_Image;

void readPGM(const char* filename, grey_Image* img) {
    printf("ReadPGM\n");
    FILE* pgmFile;
    int i, j;

    pgmFile = fopen(filename, "rb");
    if (pgmFile == NULL) {
        perror("cannot open file to read");
        exit(EXIT_FAILURE);
    }
    
    
    printf("%s \n",img->version);
    fscanf(pgmFile, "%d", &img->largeur);
    fscanf(pgmFile, "%d", &img->longeur);
    fscanf(pgmFile, "%d", &img->pixelmax);

    fgetc(pgmFile); // Read white-space

    for (i = 0; i < img->longeur; ++i) {
        for (j = 0; j < img->largeur; ++j) {
            img->pixels[i][j] = fgetc(pgmFile);
            printf("%d ", img->pixels[i][j]);
        }
        printf("\n");
    }


    fclose(pgmFile);
}


int main() {
    printf("Debut");
    int i,j;
    grey_Image img;
    readPGM("image.pgm", &img);
    printf("Affichage");
    for (i = 0; i < img.longeur; ++i) {
        for (j = 0; j < img.largeur; ++j) {
            printf("%d ", img.pixels[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
