#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "image_util.h"
#include "bmp_decoder.h"

int main(int argc, char* argv[]){

  BMP_FILE *bmp_file;
  char *file_name;
  int i;
  
  if (argc < 2){
    printf("Need to pass file as argument\n");
    return -1;
  }
  
  file_name = (char *) malloc(sizeof(char) * strlen(argv[1]));

  if (file_name == NULL ) {
    printf("File name not allocated\n");
    return -1;
  }

  file_name = argv[1];

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

  //  for(i = 0; i < 88; i++){
  //  printf("%X\t", *(bmp_file->image_data + i));
  // }
  //printf("\n\ndata:\n%d\t%d\n", bmp_file->width, bmp_file->height);


  //cleanup
  //TODO Free image data, currently causing issues
  //  free(bmp_file->image_data);
  free(bmp_file);
  return 0;
}
