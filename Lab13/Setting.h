#ifndef PROG_13_SETTING_H
#define PROG_13_SETTING_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"


typedef struct tagSettings {
    char *file_name;
    char show_flag;
    char get_flag;
    char set_flag;
    unsigned char *prop_name;
    char *prop_value;
} Settings;


Settings *set_settings(int, char**);

#endif //PROG_13_SETTING_H
