#ifndef PROG_14_BMP_H
#define PROG_14_BMP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "time.h"

#pragma pack(push, 1)

typedef struct  {
    char bfType[2];
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} Bit_map_file_header;

typedef struct {
    uint32_t    biSize;
    signed int  biWidth;
    signed int  biHeight;
    uint16_t    biPlanes;
    uint16_t    biBitCount;
    uint32_t    biCompression;
    uint32_t    biSizeImage;
    signed int  biXPelsPerMeter;
    signed int  biYPelsPerMeter;
    uint32_t    biClrUsed;
    uint32_t    biClrImportant;
} Bit_map_info_header;

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t reserved;
} Colour;

typedef struct {
    int     num_colours;
    Colour *colours;
} Bmb_colout_table;


typedef struct {
    Bit_map_file_header  *bmf_header;
    Bit_map_info_header  *bmi_header;
    Bmb_colout_table     *colour_table;
    char                 *gap;
    char                 *data;
} Bmp;

#pragma pack(pop)

Bmp* read_bmp(char* filepath);
void write_bmp(Bmp* image, char* filepath);
Bmp* create_bmp (int, int, int);
char** get_monochrome_data(Bmp* bmp);
void set_monochrome_data(Bmp* bmp, char** data);

#endif //PROG_14_BMP_H
