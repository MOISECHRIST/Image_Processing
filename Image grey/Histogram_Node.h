#ifndef HISTOGRAM_NODE
#define HISTOGRAM_NODE

typedef struct Histogram_Node
{
    int value;
    int frequency;
} Histogram_Node;

//Create a node of Image's Histogram
Histogram_Node create_node(int value);

//Increment Frequency of one node of image's histogram
void increment_frequency(Histogram_Node *);

#endif