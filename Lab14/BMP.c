#include "BMP.h"

size_t get_gap_size(Bmp* bmp) {
    return bmp->bmf_header->bfOffBits - sizeof(Bit_map_file_header) -
           sizeof(Bit_map_info_header) - sizeof(Colour) * bmp->colour_table->num_colours;
}

size_t get_width_with_padding(Bmp* bmp) {
    return (int) ceil(bmp->bmi_header->biWidth * bmp->bmi_header->biBitCount / 8.f) +
            (4 - (((int) ceil(bmp->bmi_header->biWidth * bmp->bmi_header->biBitCount / 8.f) % 4) == 0 ? 4 :
                  ((int) ceil(bmp->bmi_header->biWidth * bmp->bmi_header->biBitCount / 8.f) % 4)));
}

size_t get_data_size(Bmp* bmp) {
    return bmp->bmi_header->biHeight * get_width_with_padding(bmp);
}

Bmp* read_bmp(char* filepath) {
    FILE* bmp_file = fopen(filepath, "rb");
    if (bmp_file == NULL)
        return NULL;

    Bmp* image = malloc(sizeof(Bmp));
    image->bmf_header = malloc(sizeof(Bit_map_file_header));
    image->bmi_header = malloc(sizeof(Bit_map_info_header));
    image->colour_table = malloc(sizeof(Bmb_colout_table));

    fread(image->bmf_header, sizeof(Bit_map_file_header), 1, bmp_file);
    fread(image->bmi_header, sizeof(Bit_map_info_header), 1, bmp_file);

    if (image->bmi_header->biBitCount <= 8)
        image->colour_table->num_colours = pow(2, image->bmi_header->biBitCount);
    else
        image->colour_table->num_colours = 0;
    image->colour_table->colours = malloc(sizeof(Colour) * image->colour_table->num_colours);
    fread(image->colour_table->colours, sizeof(Colour), image->colour_table->num_colours, bmp_file);

    image->gap = malloc(get_gap_size(image));
    fread(image->gap, get_gap_size(image), 1, bmp_file);

    image->data = malloc(sizeof(char) * get_data_size(image));
    fread(image->data, sizeof(char), get_data_size(image), bmp_file);

    fclose(bmp_file);

    return image;
}

void write_bmp(Bmp* image, char* filepath) {
    FILE* bmp_file = fopen(filepath, "w+");
    if (bmp_file == NULL)
        return;

    fwrite(image->bmf_header, sizeof(Bit_map_file_header), 1, bmp_file);
    fwrite(image->bmi_header, sizeof(Bit_map_info_header), 1, bmp_file);
    fwrite(image->colour_table->colours, sizeof(Colour), image->colour_table->num_colours, bmp_file);
    fwrite(image->gap, get_gap_size(image), 1, bmp_file);
    fwrite(image->data, sizeof(char), get_data_size(image), bmp_file);

    fclose(bmp_file);
}

Bmp* create_bmp (int height, int width, int bits_per_pixel) {
    Bmp *bmp;
    bmp = malloc(sizeof(Bmp));
    bmp->bmf_header = malloc(sizeof(Bit_map_file_header));
    bmp->bmi_header = malloc(sizeof(Bit_map_info_header));
    bmp->colour_table = malloc(sizeof(Bmb_colout_table));
    bmp->bmi_header->biBitCount = bits_per_pixel;
    bmp->bmi_header->biWidth = width;
    bmp->bmi_header->biHeight = height;

    if (bits_per_pixel <= 8) {
        bmp->colour_table->num_colours = pow(2, bits_per_pixel);
        bmp->colour_table->colours = malloc(sizeof(Colour) * bmp->colour_table->num_colours);

        if(bits_per_pixel == 1) {
            bmp->colour_table->colours[0].red = 255;      //белый
            bmp->colour_table->colours[0].green = 255;
            bmp->colour_table->colours[0].blue = 255;
            bmp->colour_table->colours[0].reserved = 0;

            bmp->colour_table->colours[1].red = 0;        //черный
            bmp->colour_table->colours[1].green = 0;
            bmp->colour_table->colours[1].blue = 0;
            bmp->colour_table->colours[1].reserved = 0;
        }
    }
    else
        bmp->colour_table->num_colours = 0;

    bmp->bmf_header->bfType[0] = 'B';
    bmp->bmf_header->bfType[1] = 'M';
    bmp->bmf_header->bfSize = sizeof(Bit_map_file_header) + sizeof(Bit_map_info_header) +
            sizeof(Colour) * bmp->colour_table->num_colours + get_data_size(bmp);
    bmp->bmf_header->bfReserved1 = 0;
    bmp->bmf_header->bfReserved2 = 0;
    bmp->bmf_header->bfOffBits = bmp->bmf_header->bfSize - get_data_size(bmp);
    bmp->bmi_header->biSize = 40;

    bmp->bmi_header->biPlanes = 1;

    bmp->bmi_header->biCompression = 0;
    bmp->bmi_header->biSizeImage = get_data_size(bmp);
    bmp->bmi_header->biXPelsPerMeter = 2835;
    bmp->bmi_header->biYPelsPerMeter = 2835;
    bmp->bmi_header->biClrUsed = 0;
    bmp->bmi_header->biClrImportant = 0;

    bmp->gap = malloc(0);
    bmp->data = malloc(get_data_size(bmp));

    srand(time(NULL));
    for (int i = 0; i < get_data_size(bmp); ++i)
        bmp->data[i] = rand();

    return bmp;
}

char** get_monochrome_data(Bmp* bmp) {
    char **data = malloc (bmp->bmi_header->biHeight * sizeof(char*));
    for (int i = 0; i < bmp->bmi_header->biHeight; ++i)
        data[i] = malloc (bmp->bmi_header->biWidth * sizeof(char*));
    if (bmp->bmi_header->biBitCount == 1) {
        size_t byte = 0;
        for (int height = 0; height < bmp->bmi_header->biHeight; ++height) {
            byte = height * get_width_with_padding(bmp);
            uint8_t extract = 0b10000000;
            for (int width = 0; width < bmp->bmi_header->biWidth; ++width) {
                if (!extract) {
                    extract = 0b10000000;
                    ++byte;
                }
                data[height][width] = (bmp->data[byte] & extract ? 1 : 0);
                extract >>= 1;
            }
        }
    }

    return data;
}

void set_monochrome_data(Bmp* bmp, char** data) {
    if (bmp->bmi_header->biBitCount == 1) {
        for (int height = 0; height < bmp->bmi_header->biHeight; ++height) {
            unsigned pos = 0;
            uint8_t put_byte = 0b11111111;
            uint8_t extract = 0b10000000;
            size_t byte = 0;
            for (int width = 0; width < bmp->bmi_header->biWidth; ++width) {
                if (!data[height][width])
                    put_byte ^= (extract >> pos);

                ++pos;
                if (pos == 8) {
                    bmp->data[height * get_width_with_padding(bmp) + byte] = put_byte;
                    ++byte;
                    pos = 0;
                    put_byte = 0b11111111;
                }
            }
            if (pos < 8 && pos != 0)
                bmp->data[height * get_width_with_padding(bmp) + byte] = put_byte;
        }
    }
}