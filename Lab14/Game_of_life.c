#include "Game_of_life.h"

Field* get_field (Bmp *bmp) {
    Field *field = malloc (sizeof(Field));
    field->height = bmp->bmi_header->biHeight;
    field->width = bmp->bmi_header->biWidth;
    field->data = malloc(field->height * sizeof(char*));
    for (int i = 0; i < field->height; i++)
        field->data[i] = malloc(field->width * sizeof(char));
    field->data = get_monochrome_data(bmp);

    return field;
}

Field* copy_field (Field *field) {
    Field *copy = malloc (sizeof(Field));
    copy->height = field->height;
    copy->width = field->width;
    copy->data = malloc(copy->height * sizeof(char*));
    for (int i = 0; i < copy->height; i++)
        copy->data[i] = malloc(copy->width * sizeof(char));
    for (int i = 0; i < field->height; ++i)
        for (int j = 0; j < field->width; ++j)
            copy->data[i][j] = field->data[i][j];

    return copy;
}

Game_of_life* create_game(char *file_name, char *dir_name, unsigned max_iter, unsigned dump_freq) {
    Game_of_life *game = malloc(sizeof(Game_of_life));

    char *pattern = ".+\\.bmp$";
    regex_t preg;
    regcomp(&preg, pattern, REG_EXTENDED);
    if (regexec(&preg, file_name, 0, 0, 0)) {
        errno = ENOEXEC;
        perror("Error while creating an instance of game of life. "
               "The file format is not bmp!");
        exit(EXIT_FAILURE);
    }

    FILE *bmp_file = fopen(file_name, "rb");
    if (bmp_file == NULL) {
        errno = EIO;
        perror("Error while creating an instance of game of life. "
               "The file does not exist!");
        exit(EXIT_FAILURE);
    }

    game->file_name = file_name;
    game->bmp = malloc(sizeof(Bmp));
    game->bmp = read_bmp(file_name);
    game->dir_name = dir_name;
    game->max_iter = max_iter;
    game->dump_freq = dump_freq;
    game->prev_state = malloc(sizeof(Field));
    game->cur_state = malloc(sizeof(Field));
    game->prev_state = NULL;
    game->cur_state = get_field(game->bmp);
    game->cur_iter = 0;

    return game;
}

char get_pixel(Field *field, unsigned height, unsigned width) {
    return field->data[height % field->height][width % field->width];
}

void set_pixel(Field *field, unsigned height, unsigned width, char value) {
    field->data[height % field->height][width % field->width] = value;
}

unsigned get_neighbours_number (Field *field, unsigned height, unsigned width) {
    unsigned count = get_pixel(field, height + 1, width + 0) +
                     get_pixel(field, height + 1, width + 1) +
                     get_pixel(field, height + 0, width + 1) +
                     get_pixel(field, height - 1, width + 0) +
                     get_pixel(field, height - 1, width - 1) +
                     get_pixel(field, height + 0, width - 1) +
                     get_pixel(field, height + 1, width - 1) +
                     get_pixel(field, height - 1, width + 1);

    return count;
}

Field* find_next_state (Field *field) {
    Field *next_field = copy_field(field);
    for (int i = 0; i < field->height; i++) {
        for (int j = 0; j < field->width; j++) {
            if ((get_pixel(field, i, j) && get_neighbours_number(field, i, j) == 2) ||
                    get_neighbours_number(field, i, j) == 3)
                set_pixel(next_field, i, j, 1);
            else
                set_pixel(next_field, i, j, 0);
        }
    }

    return next_field;
}

char no_life (Field *field) {
    for (int i = 0; i < field->height; ++i)
        for (int j = 0; j < field->width; ++j)
            if (field->data[i][j] == 1)
                return 0;

    return 1;
}

char state_not_changed (Game_of_life *game) {
    for (int i = 0; i < game->cur_state->height; ++i)
        for (int j = 0; j < game->cur_state->width; ++j)
            if (game->cur_state->data[i][j] != game->prev_state->data[i][j])
                return 0;

    return 1;
}

void print_state(Game_of_life *game) {
    char file_name[255], num [255];;
    strcpy(file_name, game->dir_name);
    sprintf(num, "%d", game->cur_iter);
    strcat(file_name, "/");
    strcat(file_name, num);
    strcat(file_name, ".bmp\0");
    set_monochrome_data(game->bmp, game->cur_state->data);
    write_bmp(game->bmp, file_name);
}

void print_states (Game_of_life *game) {
    while (!no_life(game->cur_state) &&
           (++game->cur_iter <= game->max_iter || game->max_iter == -1)) {
        if (game->prev_state != NULL)
            if (state_not_changed(game))
                break;
        game->prev_state = copy_field(game->cur_state);
        game->cur_state = find_next_state(game->cur_state);
        if (game->cur_iter % game->dump_freq == 0)
            print_state(game);
    }
}

void something (Game_of_life *game) {
    Field *field = copy_field(game->cur_state);
    set_monochrome_data(game->bmp, field->data);
    write_bmp(game->bmp, "output.bmp");
}