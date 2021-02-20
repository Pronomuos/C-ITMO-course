#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "BMP.h"
#include "Game_of_life.h"
#include "time.h"
#include "errno.h"

int main(int argc, char* argv[]) {

 Bmp *bmp = create_bmp(96, 96, 1);
    write_bmp(bmp, "test.bmp");

    char *file_name = NULL;
    char *dir_name = NULL;
    unsigned max_iter = -1;
    unsigned dump_freq = 1;
    char *end;

    if (argc < 5) {
        errno = E2BIG;
        perror("Error in main: not enough arguments.");
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--input") == 0) {
            if (++i < argc)
                file_name = argv[i];
            else {
                errno = EINVAL;
                perror("Error in argument --input.");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "--output") == 0) {
            if (++i < argc)
                dir_name = argv[i];
            else {
                errno = EINVAL;
                perror("Error in argument --output.");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "--max_iter") == 0) {
            if (++i < argc)
                max_iter = strtol(argv[i], &end, 10);
            else {
                errno = EINVAL;
                perror("Error in argument --max_iter.");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "--dump_freq") == 0) {
            if (++i < argc)
                dump_freq = strtol(argv[i], &end, 10);
            else {
                errno = EINVAL;
                perror("Error in argument --dump_freq.");
                exit(1);
            }
        }
    }
    if (file_name == NULL || dir_name == NULL) {
            errno = EINVAL;
            perror("Error in file and dir names.");
            exit(1);
    }

    mkdir(dir_name, 0755);
    Game_of_life *game = create_game(file_name, dir_name, max_iter, dump_freq);
    print_states(game);
    return 0;
}
