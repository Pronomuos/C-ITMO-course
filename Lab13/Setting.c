#include "Setting.h"

Settings *set_settings(int argc, char **argv) {
    Settings *settings = (Settings *)malloc(sizeof(Settings));

    for (int i = 1; i < argc; ++i) {
        if (argv[i][2] == 'f') {
            settings->file_name = strpbrk(argv[i], "=") + 1;
        } else if (strcmp(argv[i], "--show") == 0) {
            settings->show_flag = 1;
        } else if (argv[i][2] == 'g') {
            settings->get_flag = 1;
            settings->prop_name = strpbrk(argv[i], "=") + 1;
        } else if (argv[i][2] == 's') {
            settings->set_flag = 1;
            settings->prop_name = strpbrk(argv[i], "=") + 1;
        } else if (argv[i][2] == 'v') {
            settings->prop_value = strpbrk(argv[i], "=") + 1;
        }
    }

    return settings;
}