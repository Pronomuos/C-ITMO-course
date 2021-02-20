#ifndef PROG_15_FILE_H
#define PROG_15_FILE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "errno.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#pragma pack(push, 1)

typedef struct {
    unsigned short file_name_size;
    char          *file_name;
    unsigned       file_size;
    char          *data;
} File;

#pragma pack(pop)

File* read_file(char*);
void write_file(File*);


#endif //PROG_15_FILE_H
