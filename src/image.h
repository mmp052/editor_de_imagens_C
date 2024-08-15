#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>

typedef struct {
    int width;
    int height;
    unsigned char *data;
} Image;

// Construtores e destrutores
Image* create_image(int width, int height);
void destroy_image(Image *image);

// Métodos
void load_jpeg(const char *filename);
void save_jpeg(const char *filename, unsigned char *data, int width, int height, int quality);

#endif