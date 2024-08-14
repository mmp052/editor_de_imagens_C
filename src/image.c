#include "image.h"
#include <stdlib.h>
#include <string.h>

Image* create_image(int width, int height) {
    Image *image = (Image*)malloc(sizeof(Image));
    image->width = width;
    image->height = height;
    image->data = (unsigned char*)malloc(width * height * 3); // 3 bytes por pixel (RGB)
    return image;
}

void destroy_image(Image *image) {
    free(image->data);
    free(image);
}

void load_image(Image *image, const char *filepath) {
    // Implementação de carregamento de arquivo
}

void save_image(const Image *image, const char *filepath) {
    // Implementação de salvamento de arquivo
}