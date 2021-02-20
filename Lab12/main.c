#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Not enough arguments");
        exit(1);
    }

    int cur_arg = 1;
    FILE* directories_info = fopen("dir_info.txt", "w");
    while (cur_arg < argc) {
        mkdir(argv[cur_arg], 0755);
        fputs("/", directories_info);
        fputs(argv[cur_arg++], directories_info);
        fputs("\n", directories_info);
    }

    fclose(directories_info);
    return 0;
}