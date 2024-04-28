#include "grey_Image.h"

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#define N 255

typedef struct Histogram
{
    int total_freq;
    int freq_table[N];
} Histogram;


//Function for Histogram initialisation
extern Histogram init_Histogram();

/*
Add a new node in my histogram 
------------------------------
If the node exist, the function increment the frequence
If the node don't exist, the function add a new node in the histogram
*/
extern void add_node(Histogram , int);

//Display my histogram in the terminal 
extern void print_histogram(Histogram);


#endif