#ifndef BINARY_IMAGE_H
#define BINARY_IMAGE_H

#include "grey_Image.h"

grey_Image * convert2Binary(grey_Image * img);

grey_Image * convert2Grey(grey_Image * img_bin);

grey_Image * compute_NotOp(grey_Image * img_bin);

grey_Image * compute_ANDOp(grey_Image * img_bin1, grey_Image * img_bin2);

grey_Image * compute_OROp(grey_Image * img_bin1, grey_Image * img_bin2);

int ** entry_BinaryFilter(int dim);

grey_Image * compute_Erosion(grey_Image * img_bin, int ** filter, int dim_filter);

grey_Image * compute_Dilatation(grey_Image * img_bin, int ** filter, int dim_filter);

grey_Image * compute_Ouverture(grey_Image * img_bin, int ** filter, int dim_filter);

grey_Image * compute_Fermeture(grey_Image * img_bin, int ** filter, int dim_filter);

// grey_Image * compute_BinImgAnnotation(grey_Image * img_bin);

#endif