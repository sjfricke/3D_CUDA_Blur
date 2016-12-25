#include <stdio.h>
#include <stdlib.h>
#include "bmp_decoder.h"

int decodeBMP(BMP_FILE *bmp_file, char* image_name){

  int offset;
  int pixel_count;
  unsigned char pixel_buffer[3];
  Pixel pixel;
  char pad_buf[4]; //TODO fread to empty pointer
  int i = 0;
  
  bmp_file->file_pointer = fopen(image_name, "r");
  if (bmp_file->file_pointer == NULL) {
    fprintf(stderr, "Can't open file");
    exit(1);
  }

  fread(bmp_file->header, sizeof(unsigned char), 54, bmp_file->file_pointer); // read the 54-byte header
  
  //check if bmp is 1,8,24,or 32bits
  bmp_file->bit_type = (short)bmp_file->header[28];
  
  if ( bmp_file->bit_type != 24 ) {
    printf("This is a %d bit bmp\nOnly accept 24 bit at the moment\n", bmp_file->bit_type);
    return -1;
  }

  //gather dimension details
  bmp_file->width = (int)bmp_file->header[18];
  bmp_file->height = (int)bmp_file->header[22];
  printf("Width: %d\nHeight: %d\n", bmp_file->width, bmp_file->height);

  //bmp files have padding to be 4-byte word aligned
  //save paddig value 0-3 in single byte in struct
  bmp_file->padding_count = 4- ((bmp_file->width * 3) % 4);
  printf("padding: %d\n", (int)bmp_file->padding_count);

  //finds out how much image data there is
  bmp_file->image_data = (Pixel*) malloc(sizeof(Pixel) * bmp_file->width * bmp_file->height);

  if (bmp_file->image_data == NULL) {
    printf("Why you no malloc correctly\n");
    return -1;
  }

  //init offset and count
  offset = 0;
  pixel_count = 0;
  while ( fread(pixel_buffer, 1, 3, bmp_file->file_pointer) == 3) {

   pixel.red = pixel_buffer[0];
   pixel.green = pixel_buffer[1];
   pixel.blue = pixel_buffer[2]; 
     
   *(bmp_file->image_data + pixel_count) = pixel;
   pixel_count++;

   //will skip alignment offset
   if (offset == (bmp_file->width-1) && bmp_file->padding_count > 0) {
     fread(pad_buf, 1, bmp_file->padding_count, bmp_file->file_pointer);
     //reads off 4-byte align offset
     offset = 0;
   } else {
     offset++;
   }
   
  }//while loop

 printf("Sucessful file read!\n");

 fclose(bmp_file->file_pointer);
 return 0;
}

int writeToBMP(BMP_FILE *bmp_file, char* file_name){

  FILE *out_file;
  int offset, i;
  char *padding;
  
  out_file = fopen(file_name, "wb");
  if (out_file == NULL) {
    fprintf(stderr, "Can't open write file");
    return -1;
  }

  //sets up padding for file, padding can be what ever
  padding = (char *) malloc(sizeof(char) * bmp_file->padding_count);
  
  fwrite( bmp_file->header, sizeof(bmp_file->header), 1, out_file); //writes back header

  offset = 0;
  for(i = 0; i < bmp_file->width * bmp_file->height; i++){

    fwrite((bmp_file->image_data + i), 3, 1,  out_file );

    if (offset == (bmp_file->width-1) && bmp_file->padding_count > 0) {
      fwrite(padding, (int)bmp_file->padding_count, 1, out_file);
      offset = 0;
    } else {
      offset++;
    }
  
  }

  fclose(out_file);
  return 0;
}
