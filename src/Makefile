CC=gcc

main: image_util.o bmp_decoder.o bitmap_cuda.o
	$(CC) -o bitmap_cuda image_util.o bmp_decoder.o bitmap_cuda.o

clean:
	rm bitmap_cuda image_util.o bmp_decoder.o bitmap_cuda.o
