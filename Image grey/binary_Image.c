#include "binary_Image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

grey_Image * convert2Binary(grey_Image * img){
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img->longueur;
    img_res->largeur=img->largeur;
    strcpy(img_res->version,img->version);
    img_res->pixelmax=1;
    img_res->pixelmin=0;

    int i, j;
    for(i=0; i< img->longueur; i++){
        for(j=0;j<img->largeur; j++){
            if(img->pixels[i][j]>100){
                img_res->pixels[i][j]=1;
            }
            else{
                img_res->pixels[i][j]=0;
            }
        }
    }

    return img_res;
}

grey_Image * convert2Grey(grey_Image * img_bin){
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img_bin->longueur;
    img_res->largeur=img_bin->largeur;
    strcpy(img_res->version,img_bin->version);
    img_res->pixelmax=255;
    img_res->pixelmin=0;

    int i, j;
    for(i=0; i< img_bin->longueur; i++){
        for(j=0;j<img_bin->largeur; j++){
            if(img_bin->pixels[i][j]==1){
                img_res->pixels[i][j]=255;
            }
            else{
                img_res->pixels[i][j]=0;
            }
        }
    }

    return img_res;
}

grey_Image * compute_NotOp(grey_Image * img_bin){
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img_bin->longueur;
    img_res->largeur=img_bin->largeur;
    strcpy(img_res->version,img_bin->version);
    img_res->pixelmax=1;
    img_res->pixelmin=0;

    int i, j;
    for(i=0; i< img_bin->longueur; i++){
        for(j=0;j<img_bin->largeur; j++){
            img_res->pixels[i][j]=1-img_res->pixels[i][j];
        }
    }

    return img_res;
}

grey_Image * compute_ANDOp(grey_Image * img_bin1, grey_Image * img_bin2){
    if((img_bin1->longueur!=img_bin2->longueur)||(img_bin1->largeur!=img_bin2->largeur)){
        printf("[ERROR]::Les images n'ont pas les meme dimensions...");
        exit(1);
    }
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img_bin1->longueur;
    img_res->largeur=img_bin1->largeur;
    strcpy(img_res->version,img_bin1->version);
    int i,j;

    img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
    for(i = 0; i < img_res->longueur; i++)
        img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

    for(i=0;i<img_res->longueur;i++){
        for(j=0;j<img_res->largeur;j++){
            img_res->pixels[i][j]=img_bin1->pixels[i][j]==img_bin2->pixels[i][j] ? img_bin1->pixels[i][j] : 1;
        }
    }
    img_res->pixelmax=1;
    img_res->pixelmin=0;
    return img_res;
}

grey_Image * compute_OROp(grey_Image * img_bin1, grey_Image * img_bin2){
    if((img_bin1->longueur!=img_bin2->longueur)||(img_bin1->largeur!=img_bin2->largeur)){
        printf("[ERROR]::Les images n'ont pas les meme dimensions...");
        exit(1);
    }
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img_bin1->longueur;
    img_res->largeur=img_bin1->largeur;
    strcpy(img_res->version,img_bin1->version);
    int i,j;

    img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
    for(i = 0; i < img_res->longueur; i++)
        img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

    for(i=0;i<img_res->longueur;i++){
        for(j=0;j<img_res->largeur;j++){
            img_res->pixels[i][j] = (img_bin1->pixels[i][j]==0 ||  img_bin2->pixels[i][j]==0) ? 0 : 1;
        }
    }
    img_res->pixelmax=1;
    img_res->pixelmin=0;
    return img_res;
}

int ** entry_BinaryFilter(int dim){
    int ** filter;
    int i,j;
    
    filter= (int **)malloc(sizeof(int)*dim);
    for(i=0; i<dim; i++)
        filter[i]= (int *)malloc(sizeof(int)*dim);

    for(i=0; i<dim; i++){
        for(j=0; j<dim; j++){
            printf("Entrer l'element %d de la colonne %d [0/1] : ", j+1, i+1);
            scanf("%d", &filter[i][j]);
            while(filter[i][j] != 0 || filter[i][j] != 1){
                printf("[ERROR]::La valeur entrée doit être 0 ou 1\n");
                printf("Entrer l'element %d de la colonne %d [0/1] : ", j+1, i+1);
                scanf("%d", &filter[i][j]);
            }
        }
    }
    return filter;
}

grey_Image * compute_Erosion(grey_Image * img_bin, int ** filter, int filter_dim){
    if(filter_dim > img_bin->largeur || filter_dim > img_bin->longueur){
        printf("[ERROR]::Les dimensions du filtres ne doivent pas être supérieurs à celle de l'image...");
        exit(1);
    }
    int i,j,k, n, calcul, tmp=filter_dim/2, nb_1filter;
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img_bin->longueur;
    img_res->largeur=img_bin->largeur;
    strcpy(img_res->version,img_bin->version);

    img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
    for(i = 0; i < img_res->longueur; i++)
        img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

    for (i = 0; i <= img_bin->longueur; ++i) {
        for (j = 0; j <= img_bin->largeur; ++j) {
            if(i >= img_bin->longueur-tmp || i < tmp || j < tmp || j >= img_bin->largeur-tmp){
                img_res->pixels[i][j]=0;
            }
            else{
                calcul=0;
                nb_1filter=0;
                for(k=0; k<filter_dim; k++){
                    for(n=0; n<filter_dim; n++){
                        if(filter[k][n]==1){
                            nb_1filter++;
                            if(filter[k][n]==img_bin->pixels[i-tmp+k][j-tmp+n]){
                                calcul++;
                            }
                        }
                    }
                }
                if(calcul==nb_1filter){
                    img_res->pixels[i][j]=1;
                }
                else{
                    img_res->pixels[i][j]=0;
                }
            }
        }  
    }
    img_res->pixelmax=1;
    img_res->pixelmin=0;
    return img_res;
}

grey_Image * compute_Dilatation(grey_Image * img_bin, int ** filter, int filter_dim){
    if(filter_dim > img_bin->largeur || filter_dim > img_bin->longueur){
        printf("[ERROR]::Les dimensions du filtres ne doivent pas être supérieurs à celle de l'image...");
        exit(1);
    }
    int i,j,k, n, calcul, tmp=filter_dim/2;
    grey_Image * img_res=malloc(sizeof(grey_Image));
    img_res->longueur=img_bin->longueur;
    img_res->largeur=img_bin->largeur;
    strcpy(img_res->version,img_bin->version);

    img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
    for(i = 0; i < img_res->longueur; i++)
        img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

    for (i = 0; i <= img_bin->longueur; ++i) {
        for (j = 0; j <= img_bin->largeur; ++j) {
            if(i >= img_bin->longueur-tmp || i < tmp || j < tmp || j >= img_bin->largeur-tmp){
                img_res->pixels[i][j]=0;
            }
            else{
                calcul=0;
                for(k=0; k<filter_dim; k++){
                    for(n=0; n<filter_dim; n++){
                        if(filter[k][n]==1){
                            if(filter[k][n]==img_bin->pixels[i-tmp+k][j-tmp+n]){
                                calcul++;
                            }
                        }
                    }
                }
                if(calcul>0){
                    for(k=0; k<filter_dim; k++){
                        for(n=0; n<filter_dim; n++){
                            if(filter[k][n]==1){
                                img_res->pixels[i-tmp+k][j-tmp+n]=1;
                            }
                            else{
                                img_res->pixels[i-tmp+k][j-tmp+n]=img_bin->pixels[i-tmp+k][j-tmp+n];
                            }
                        }
                    }
                }
                else{
                    for(k=0; k<filter_dim; k++){
                        for(n=0; n<filter_dim; n++){
                            img_res->pixels[i-tmp+k][j-tmp+n]=img_bin->pixels[i-tmp+k][j-tmp+n];
                        }
                    }
                }
            }
        }  
    }
    img_res->pixelmax=1;
    img_res->pixelmin=0;
    return img_res;
}

grey_Image * compute_Ouverture(grey_Image * img_bin, int ** filter, int filter_dim){
    if(filter_dim > img_bin->largeur || filter_dim > img_bin->longueur){
        printf("[ERROR]::Les dimensions du filtres ne doivent pas être supérieurs à celle de l'image...");
        exit(1);
    }
    grey_Image * img_res=malloc(sizeof(grey_Image));

    img_res=compute_Erosion(img_bin, filter, filter_dim);
    img_res=compute_Dilatation(img_res, filter, filter_dim);


    return img_res;
}

grey_Image * compute_Fermeture(grey_Image * img_bin, int ** filter, int filter_dim){
    if(filter_dim > img_bin->largeur || filter_dim > img_bin->longueur){
        printf("[ERROR]::Les dimensions du filtres ne doivent pas être supérieurs à celle de l'image...");
        exit(1);
    }
    grey_Image * img_res=malloc(sizeof(grey_Image));


    img_res=compute_Dilatation(img_bin, filter, filter_dim);
    img_res=compute_Erosion(img_res, filter, filter_dim);

    return img_res;
}

// grey_Image * first_Round(grey_Image * img_bin){
//     int tmp=1, i,j, max_col=0;
//     grey_Image * img_res=malloc(sizeof(grey_Image));
//     img_res->longueur=img_bin->longueur;
//     img_res->largeur=img_bin->largeur;
//     strcpy(img_res->version,img_bin->version);

//     img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
//     for(i = 0; i < img_res->longueur; i++)
//         img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

//     img_res->pixels=img_bin->pixels;

//     for (i = 0; i <= img_bin->longueur; ++i) {
//         for (j = 0; j <= img_bin->largeur; ++j) {
//             if(img_res->pixels[i][j]==1){
//                 if(i-1<0 && j-1<0){
//                     max_col=1;
//                     img_res->pixels[i][j]=max_col;
//                 }
//                 else{
//                     if(i-1<0 && j-1>=0){
//                         if(img_res->pixels[i][j-1]==0){
//                             img_res->pixels[i][j]= max_col+1;
//                             max_col++;
//                         }
//                         else{
//                             img_res->pixels[i][j]= img_res->pixels[i][j-1];
//                         }
//                     }
//                     else{
//                         if(i-1>=0 && j-1<0){
//                             if(img_res->pixels[i-1][j]==0){
//                                 img_res->pixels[i][j]= max_col+1;
//                                 max_col++;
//                             }
//                             else{
//                                 img_res->pixels[i][j]= img_res->pixels[i-1][j];
//                             }
//                         }
//                         else{
//                             if(img_res->pixels[i-1][j]==0 && img_res->pixels[i][j-1]==0){
//                                 img_res->pixels[i][j]= max_col+1;
//                                 max_col++;
//                             }
//                             else{
//                                 img_res->pixels[i][j]= img_res->pixels[i-1][j] > img_res->pixels[i][j-1] ? img_res->pixels[i][j-1] : img_res->pixels[i-1][j];
//                             }
//                         }
//                     }
//                 }
//             }
//         }  
//     }
//     img_res->pixelmax=max_col;
//     img_res->pixelmin=0;
//     return img_res;
// }

// grey_Image * second_Round(grey_Image * img_bin){
//     int tmp=1, i,j, max_col=img_bin->pixelmax;
//     grey_Image * img_res=malloc(sizeof(grey_Image));
//     img_res->longueur=img_bin->longueur;
//     img_res->largeur=img_bin->largeur;
//     strcpy(img_res->version,img_bin->version);

//     img_res->pixels = (unsigned char **)malloc(img_res->longueur * sizeof(unsigned char *));
//     for(i = 0; i < img_res->longueur; i++)
//         img_res->pixels[i] = (unsigned char*)malloc(img_res->largeur * sizeof(unsigned char));

//     img_res->pixels=img_bin->pixels;

//     for (i = img_bin->longueur-1; i >= 0; i--) {
//         for (j = img_bin->largeur-1; j >=0; j--) {
//             if(img_res->pixels[i][j]==1){
//                 if(i+1>img_bin->longueur-1 && j+1<=img_bin->largeur-1){
                    
//                 }
//                 else{
//                     if(i-1>=0 && j-1<0){
//                         if(img_res->pixels[i-1][j]==0){
//                             img_res->pixels[i][j]= max_col+1;
//                             max_col++;
//                         }
//                         else{
//                             img_res->pixels[i][j]= img_res->pixels[i-1][j];
//                         }
//                     }
//                     else{
//                         if(img_res->pixels[i-1][j]==0 && img_res->pixels[i][j-1]==0){
//                             img_res->pixels[i][j]= max_col+1;
//                             max_col++;
//                         }
//                         else{
//                             img_res->pixels[i][j]= img_res->pixels[i-1][j] > img_res->pixels[i][j-1] ? img_res->pixels[i][j-1] : img_res->pixels[i-1][j];
//                         }
//                     }
//                 }
//             }
//         }  
//     }
//     img_res->pixelmax=max_col;
//     img_res->pixelmin=0;
//     return img_res;
// }

// grey_Image * compute_BinImgAnnotation(grey_Image * img_bin){

// }
