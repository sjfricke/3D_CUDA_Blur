#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "image_util.h"
#include "bmp_decoder.h"

int main(int argc, char* argv[]){

  BMP_FILE *bmp_file;
  char *file_name;
  char *out_file;
  int i;
  
  if (argc < 3){
    printf("Need to pass file as argument\n");
    return -1;
  }
  
  file_name = (char *) malloc(sizeof(char) * strlen(argv[1]));
  out_file = (char *) malloc(sizeof(char) * strlen(argv[2]));

  if (file_name == NULL || out_file == NULL ) {
    printf("File name not allocated\n");
    return -1;
  }

  file_name = argv[1];
  out_file = argv[2];

  bmp_file = malloc(sizeof(BMP_FILE) );
  if (bmp_file == NULL) {
    printf("Well something didn't work correctly\n");
    return -1;
  }

  if ( decodeBMP(bmp_file, file_name) != 0 ) {
    printf("Well thats not good, BMP file went bad\n");
    return -1;
  } else {

  }

  for(i = 0; i < bmp_file->height * bmp_file->width; i++){
    if(isWhite((Pixel) *(bmp_file->image_data + i)) != 0) {
      
      printf("Before: %6X\t ", *(bmp_file->image_data + i));  
      (*(bmp_file->image_data + i)).red = 0xFF;
      printf("After: %6X\n ", *(bmp_file->image_data + i));

    }
  }

  writeToBMP(bmp_file, out_file);
  //cleanup
  //TODO Free image data, currently causing issues
  //  free(bmp_file->image_data);
  free(bmp_file);
  return 0;
}
