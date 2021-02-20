#ifndef PROG_14_GAME_OF_LIFE_H
#define PROG_14_GAME_OF_LIFE_H

#include "BMP.h"
#include <string.h>
#include <regex.h>
#include "errno.h"

typedef struct {
    char     **data;
    unsigned height;
    unsigned width;
}Field;

typedef struct {
    Bmp       *bmp;
    char      *file_name;
    char      *dir_name;
    unsigned  max_iter;
    unsigned  dump_freq;
    unsigned  cur_iter;
    Field     *cur_state;
    Field     *prev_state;
}Game_of_life;

Game_of_life* create_game(char*, char*, unsigned, unsigned);
void print_states (Game_of_life*);
void something (Game_of_life*);


#endif //PROG_14_GAME_OF_LIFE_H
