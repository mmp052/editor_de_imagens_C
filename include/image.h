#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    int width;
    int height;
    unsigned char *data;
} Image;

// Construtores e destrutores
Image* create_image(int width, int height);
void destroy_image(Image *image);

// Métodos
void load_image(Image *image, const char *filepath);
void save_image(const Image *image, const char *filepath);

#endif