#ifndef PROG_13_ID3V2_H
#define PROG_13_ID3V2_H
#include <ntsid.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Setting.h"

#pragma pack(push, 1)

typedef union sync_size {
    __uint32_t size_32;
    __uint8_t bytes[4];
} sync_size;

typedef struct {
    unsigned char file_ID[3];
    __uint8_t version[2];
    __uint8_t flags;
    sync_size size;
} ID3v2_header;

typedef struct {
    sync_size size;
    char *data;
} ID3v2_extended_header;

typedef struct {
    unsigned char ID[4];
    sync_size size;
    __uint8_t flags[2];
} Frame_header;

typedef struct {
    Frame_header *header;
    char *data;
} Frame;

typedef struct {
    ID3v2_header *header;
    ID3v2_extended_header *ext_header;
    Frame **frames;
    int num_frames;
    int frames_size;
    int padding_size;
    char *padding;
}ID3v2_tag;

typedef struct MP3_file {
    char *file_name;
    ID3v2_tag *tag;
} MP3_file;

#pragma pack(pop)


MP3_file * read(Settings*);
void update(MP3_file*);
void free_MP3(MP3_file*);
int unsynchsafe(sync_size);
uint32_t synchsafe (uint32_t size);
void print_frame_data(Frame* frame);
void show_metadata(Settings*, MP3_file*);
void set_frame (Settings*, MP3_file*);
void get_frame (Settings*, MP3_file*, unsigned char [4]);

#endif //PROG_13_ID3V2_H
