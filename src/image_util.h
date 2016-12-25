#ifndef IMAGE_UTIL_H
#define IMAGE_UTIL_H

#include <stdio.h>

typedef struct Pixel {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} Pixel;

typedef struct BMP_FILE {
  FILE* file_pointer;
  char header[54];
  short bit_type;
  int width;
  int height;
  unsigned char padding_count;
  Pixel* image_data;
} BMP_FILE;

#endif
