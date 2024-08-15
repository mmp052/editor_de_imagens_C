#include "image.h"
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>

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

// void load_image(Image *image, const char *filepath) {
//     // Implementação de carregamento de arquivo
// }

void load_jpeg(const char *filename) {
    FILE *infile = fopen(filename, "rb");
    if (!infile) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", filename);
        return;
    }

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int num_channels = cinfo.output_components;
    unsigned long data_size = width * height * num_channels;

    printf("%d\n", width);

    unsigned char *data = (unsigned char*)malloc(data_size);
    while (cinfo.output_scanline < height) {
        unsigned char *buffer_array[1];
        buffer_array[0] = data + (cinfo.output_scanline) * width * num_channels;
        jpeg_read_scanlines(&cinfo, buffer_array, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    // Aqui, você pode manipular os dados da imagem armazenados em 'data'
    free(data);
}

// void save_image(const Image *image, const char *filepath) {
//     // Implementação de salvamento de arquivo
// }

void save_jpeg(const char *filename, unsigned char *data, int width, int height, int quality) {
    FILE *outfile = fopen(filename, "wb");
    if (!outfile) {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", filename);
        return;
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3; // 3 para RGB
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    while (cinfo.next_scanline < cinfo.image_height) {
        unsigned char *row_pointer[1];
        row_pointer[0] = &data[cinfo.next_scanline * width * 3];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);
}