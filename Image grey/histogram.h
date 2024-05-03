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

//Display my histogram in the terminal 
void print_histogram(Histogram, int);

//Display my histogram in file
void print_hist_in_file(Histogram hist);

#endif