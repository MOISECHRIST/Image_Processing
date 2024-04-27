#include "histogram.h"

//Function for Histogram initialisation
Histogram init_Histogram(){
    Histogram hist;
    hist.total_freq=0;
    hist.freq_table={0};

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
    return hist;
}

//Display my histogram in the terminal 
void print_histogram(Histogram hist){
    
}