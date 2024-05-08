#include "grey_Image.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
     grey_Image *img=malloc(sizeof(grey_Image));
    read_image("image.pgm", img);
    Histogram hist=build_histogram(img);
    print_histogram(hist, 5);
    print_hist_in_file(hist);
    save_image(img);
    return 0;
}