#include "Histogram_Node.h"
#include "grey_Image.h"

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

//The histogram is a binary tree for storage optimisation
typedef struct Histogram
{
    Histogram_Node node;
    Histogram *left;
    Histogram *rightnode;
} Histogram;


//Function for Histogram initialisation
Histogram init_Histogram();


/*
Add a new node in my histogram 
------------------------------
If the node exist, the function increment the frequence
If the node don't exist, the function add a new node in the histogram
*/
void add_node(Histogram *, Histogram_Node);

//Display my histogram in the terminal 
void print_histogram(Histogram *);


#endif