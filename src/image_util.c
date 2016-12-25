#include "image_util.h"

const Pixel WHITE = {0xFF, 0xFF, 0xFF};

int isWhite(Pixel pixel) {
  if (pixel.red == WHITE.red &&
      pixel.green == WHITE.green &&
      pixel.blue == WHITE.blue) {
    return 0;
  } else {
    return -1;
  }
}
