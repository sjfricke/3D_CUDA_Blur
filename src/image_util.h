#ifndef IMAGE_UTIL_H
#define IMAGE_UTIL_H

#include <stdio.h>

//TODO see if there is a little/big eden issue
typedef struct Pixel {
  unsigned char blue;
  unsigned char green;
  unsigned char red;
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

extern const Pixel WHITE;

//returns 0 if WHITE, else -1
int isWhite(Pixel pixel);

#endif
