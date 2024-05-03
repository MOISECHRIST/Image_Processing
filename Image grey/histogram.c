#include "histogram.h"
#include <stdio.h>
#include <stdlib.h>

//Function for Histogram initialisation
Histogram init_Histogram(){
    Histogram hist;
    hist.total_freq=0;
    int i;
    for(i=0;i<N;i++)
        hist.freq_table[i]=0;

    return hist;
}
 
/*
Add a new node in my histogram
------------------------------
If the node exist, the function increment the frequence
If the node don't exist, the function add a new node in the histogram
*/
Histogram add_node(Histogram hist, int node){
    hist.freq_table[node]++;
    hist.total_freq++;
    return hist;
}

//Function returned a maximum frequency of histogram 
int maximum(Histogram hist){
    int maxi=0,i;
    for(i=0;i<N;i++){
        if(hist.freq_table[i]>maxi)
            maxi=hist.freq_table[i];
    }
    return maxi;
}

//Display my histogram in the terminal 
void print_histogram(Histogram hist, int xlim){
    int max_val=maximum(hist), i,j;
    for(i=max_val;i>=0;i--){
        /*if(i<10)
            printf("%d  ",i);
        else
            printf("%d ",i);*/
        for(j=0;j<N/xlim;j++){
            if(hist.freq_table[j]>=i){
                printf("*  ");
            }
            else{
                printf("   ");
            }
        }
        printf("\n");
    }
    for(i=0;i<N/xlim;i++){
        if(i<10)
            printf("%d  ",i);
        else
            printf("%d ",i);
    }
    printf("\n");
}

void print_hist_in_file(Histogram hist){
    const char *filename="hist_result.txt";
    FILE *file = fopen(filename, "w");
    if (file == NULL){
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        return;
    }
    int max_val=maximum(hist), i,j;
    for(i=max_val;i>=0;i--){
        /*if(i<10)
            fprintf(file,"%d  ",i);
        else
            fprintf(file,"%d ",i);*/
        for(j=0;j<N;j++){
            if(hist.freq_table[j]>=i){
                fprintf(file, "*  ");
            }
            else{
                fprintf(file, "   ");
            }
            
        }
        fprintf(file, "\n");
    }
    for(i=0;i<N;i++){
        if(i<10)
            fprintf(file,"%d  ",i);
        else
            fprintf(file,"%d ",i);
    }
    fprintf(file, "\n");
    fclose(file);
}