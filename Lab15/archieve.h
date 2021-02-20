#ifndef PROG_15_ARCHIEVE_H
#define PROG_15_ARCHIEVE_H

#include "file.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "errno.h"

#pragma pack(push, 1)

typedef struct {
    char     archive_id [4];
    char     *archive_name;
    unsigned files_number;
    File     **files;
} Archive;

#pragma pack(pop)

Archive* create_archive (char*, unsigned, char**);
Archive* read_archive (char*);
void write_archive(char*, Archive*);
void list_archive (char*);
void extract_archive(char*);


#endif //PROG_15_ARCHIEVE_H
