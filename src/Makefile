CC=gcc

main: image_util.o bmp_decoder.o bitmap_main.o
	$(CC) -o bitmap image_util.o bmp_decoder.o bitmap_main.o

clean:
	rm bitmap image_util.o bmp_decoder.o bitmap_main.o
