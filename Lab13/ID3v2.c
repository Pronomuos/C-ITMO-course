#include "ID3v2.h"

int unsynchsafe(const sync_size size)
{
    uint32_t byte0 = size.bytes[0];
    uint32_t byte1 = size.bytes[1];
    uint32_t byte2 = size.bytes[2];
    uint32_t byte3 = size.bytes[3];

    return byte0 << 21 | byte1 << 14 | byte2 << 7 | byte3;
}

uint32_t synchsafe (uint32_t size) {
    sync_size s_size;
    s_size.size_32 = size;

    uint32_t byte0 = s_size.bytes[0] & 0x7f;
    uint32_t byte1 = s_size.bytes[1] & 0x7f;
    uint32_t byte2 = s_size.bytes[2] & 0x7f;
    uint32_t byte3 = s_size.bytes[3] & 0x7f;

    return byte0 << 24 | byte1 << 16 | byte2 << 8 | byte3;
}

char correct_frame(Frame_header *frameHeader) {
    if (frameHeader->ID[0] == 0 &&
        frameHeader->ID[1] == 0 &&
        frameHeader->ID[2] == 0 &&
        frameHeader->ID[3] == 0)
        return 0;
    return 1;
}

char correct_header_id (ID3v2_header *header) {
    if (header->file_ID[0] != 'I' &&
        header->file_ID[1] != 'D' &&
        header->file_ID[2] != '3')
        return 0;
    return 1;
}


MP3_file* read(Settings *s) {
    FILE  *file = fopen(s->file_name, "rb");
    if (file == NULL) {
        perror("Error while reading: the file doesn't exist!\n");
        exit(1);
    }
    MP3_file *mp3 = (MP3_file*) malloc(sizeof(MP3_file*));
    mp3->file_name = s->file_name;
    fseek(file, 0, SEEK_SET);
    mp3->tag = (ID3v2_tag*) malloc(sizeof(ID3v2_tag));
    mp3->tag->header = (ID3v2_header*) malloc(sizeof(ID3v2_header));
    fread(mp3->tag->header, sizeof(ID3v2_header), 1, file);
    if (!correct_header_id(mp3->tag->header)){
        perror("Incorrect ID3v2 tag!\n");
        exit(1);
    }
    if ((mp3->tag->header->flags >> 6) % 2) {
        mp3->tag->ext_header = (ID3v2_extended_header*) malloc(sizeof(ID3v2_extended_header));
        fread(mp3->tag->ext_header, sizeof(uint32_t), 1, file);
        int ext_size = unsynchsafe(mp3->tag->ext_header->size);
        mp3->tag->ext_header->data = (char*) malloc(ext_size * sizeof(char));
        fread(mp3->tag->ext_header->data, ext_size - sizeof(uint32_t), 1, file);
    }
    else
        mp3->tag->ext_header = NULL;

    int tag_size = unsynchsafe(mp3->tag->header->size);

    mp3->tag->num_frames = 0;
    mp3->tag->frames = NULL;
    while (ftell(file) <  tag_size + sizeof(ID3v2_header)) {
        Frame* cur_frame = (Frame*) malloc(sizeof(Frame));
        cur_frame->header = (Frame_header*) malloc(sizeof(Frame_header));
        fread(cur_frame->header, sizeof(Frame_header), 1, file);
        if (!correct_frame(cur_frame->header)) {
            mp3->tag->padding_size = tag_size - mp3->tag->frames_size;
            mp3->tag->padding = malloc (mp3->tag->padding_size);
            fread(mp3->tag->padding, sizeof(char),  mp3->tag->padding_size, file);
            break;
        }
        else {
            int frame_size = unsynchsafe(cur_frame->header->size);
            mp3->tag->frames_size += frame_size + sizeof(Frame_header);
            cur_frame->data = malloc(frame_size * sizeof(char));
            fread(cur_frame->data, sizeof(char), frame_size, file);
            mp3->tag->frames = realloc(mp3->tag->frames, ++mp3->tag->num_frames * sizeof(Frame));
            mp3->tag->frames[mp3->tag->num_frames - 1] = cur_frame;
        }
    }
    fclose(file);
    return mp3;
}

void update(MP3_file *mp3) {
    FILE* file = fopen(mp3->file_name, "r+b");
    if (file == NULL) {
        perror("Error while updating: the file doesn't exist!\n");
        exit(1);
    }
    fwrite(mp3->tag->header, sizeof(ID3v2_header), 1, file);
    if (mp3->tag->ext_header != NULL)
        fwrite(mp3->tag->ext_header, sizeof(ID3v2_extended_header), 1, file);
    for (int i = 0; i < mp3->tag->num_frames; i++) {
        fwrite(mp3->tag->frames[i]->header, sizeof(Frame_header), 1, file);
        fwrite(mp3->tag->frames[i]->data, sizeof(char),
               unsynchsafe(mp3->tag->frames[i]->header->size), file);
    }
    fwrite(mp3->tag->padding, sizeof(char),  unsynchsafe(mp3->tag->header->size) - mp3->tag->frames_size, file);
    fclose(file);
}

void free_MP3(MP3_file *mp3) {
    free(mp3->tag->header);
    if (mp3->tag->ext_header != NULL) {
        free(mp3->tag->ext_header);
        free(mp3->tag->ext_header->data);
    }
    for (int i = 0; i < mp3->tag->num_frames; i++) {
        free(mp3->tag->frames[i]->header);
        //free(mp3->tag->frames[i]->data);
        free(mp3->tag->frames[i]);
    }
    free(mp3->tag->frames);
    free(mp3->tag->padding);
    free(mp3);
}

void print_frame_data(Frame *frame) {
    for (int i = 0; i < unsynchsafe(frame->header->size); i++)
        if (frame->data[i] >= 32 && frame->data[i] <= 126)
            printf("%c", frame->data[i]);
    printf("\n");
}

void show_metadata(Settings *s, MP3_file *mp3) {
    for (int i = 0; i < mp3->tag->num_frames; i++) {
        printf("[%s]:\t", mp3->tag->frames[i]->header->ID);
        print_frame_data(mp3->tag->frames[i]);
    }
}

void set_frame (Settings *s, MP3_file *mp3) {
    for (int i = 0; i < mp3->tag->num_frames; i++) {
        if (strcmp(mp3->tag->frames[i]->header->ID, s->prop_name) == 0) {
            mp3->tag->frames[i]->header->size.size_32 = synchsafe(strlen(s->prop_value));
            realloc(mp3->tag->frames[i]->data, unsynchsafe(mp3->tag->frames[i]->header->size) * sizeof(char));
            mp3->tag->frames[i]->data = s->prop_value;
            update(mp3);
            return;
        }
    }
    mp3->tag->frames = realloc(mp3->tag->frames, ++mp3->tag->num_frames * sizeof(Frame));
    mp3->tag->frames[mp3->tag->num_frames - 1] = malloc(sizeof(Frame));
    mp3->tag->frames[mp3->tag->num_frames - 1]->header = malloc(sizeof(Frame_header));
    mp3->tag->frames[mp3->tag->num_frames - 1]->header->ID[0] = s->prop_name[0];
    mp3->tag->frames[mp3->tag->num_frames - 1]->header->ID[1] = s->prop_name[1];
    mp3->tag->frames[mp3->tag->num_frames - 1]->header->ID[2] = s->prop_name[2];
    mp3->tag->frames[mp3->tag->num_frames - 1]->header->ID[3] = s->prop_name[3];
    mp3->tag->frames[mp3->tag->num_frames - 1]->header->size.size_32 = synchsafe(strlen(s->prop_value) * sizeof(char));
    mp3->tag->frames[mp3->tag->num_frames - 1]->header->flags[0] = 0;
    mp3->tag->frames[mp3->tag->num_frames - 1]->header->flags[1] = 0;
    mp3->tag->frames[mp3->tag->num_frames - 1]->data = (char*) malloc(strlen(s->prop_value));
    mp3->tag->frames[mp3->tag->num_frames - 1]->data = s->prop_value;
    mp3->tag->frames_size += strlen(s->prop_value) + sizeof(Frame_header);
    update(mp3);
}

void get_frame (Settings *s,  MP3_file *mp3, unsigned char prop_name [4]) {
    for (int i = 0; i < mp3->tag->num_frames; i++) {
        if (strcmp(mp3->tag->frames[i]->header->ID, prop_name) == 0) {
            print_frame_data(mp3->tag->frames[i]);
            return;
        }
    }
}
