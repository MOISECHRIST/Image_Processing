#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#define N 255

typedef struct Histogram
{
    int total_freq;
    int freq_table[N];
} Histogram;


//Function for Histogram initialisation
Histogram init_Histogram();

/*
Add a new node in my histogram 
------------------------------
If the node exist, the function increment the frequence
If the node don't exist, the function add a new node in the histogram
*/
Histogram add_node(Histogram , int);


int maximum(Histogram);

//Display my histogram in the terminal 
void print_histogram(Histogram, int);

//Display my histogram in file
void print_hist_in_file(Histogram hist);

/*Display my histogram in the pgm file 
-------------------------------------
Histogram = the histogram
int = bins 
char = filename
int = grey level (value is between 0 and 255 If equal to 0 the color is black 
if equal to 255 the color is white. between the last two number the color is grey)
*/
void print_hist_into_pgm(Histogram, int, char *, int);

#endif