#include <stdio.h>
#include <stdlib.h>
#include "archieve.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        errno = E2BIG;
        perror("Error in main: not enough arguments.");
        exit(1);
    }
    char **file_names = malloc((argc - 4) * sizeof(char*));
    int  files_number = 0;
    char *arc_name = NULL;
    char create_flag = 0;
    char extract_flag = 0;
    char list_flag = 0;

    for (int i = 1; i < argc; i++) {
        switch (argv[i][2]) {
            case 'f':
                arc_name = argv[++i];
                break;
            case 'c':
                 create_flag = 1;
                 break;
            case 'e':
                extract_flag = 1;
                break;
            case 'l':
                list_flag = 1;
                break;
            default:
                file_names[files_number++] = argv[i];
                break;
        }
    }

    if (arc_name == NULL) {
        errno = E2BIG;
        perror("Error in main: not enough arguments.");
        exit(1);
    }

    if (create_flag)
         create_archive(arc_name, files_number, file_names);
    else if (extract_flag)
        extract_archive(arc_name);
    else if (list_flag)
        list_archive(arc_name);

}