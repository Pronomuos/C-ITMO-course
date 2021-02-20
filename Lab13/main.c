#include <stdio.h>
#include "ID3v2.h"
#include "Setting.h"

int main(int argc, char **argv)
{
    Settings *settings = set_settings(argc, argv);
    MP3_file *mp3 = read(settings);
    if (settings->show_flag) {
        show_metadata(settings, mp3);
    } else if (settings->get_flag) {
        get_frame(settings, mp3, settings->prop_name);
    } else if (settings->set_flag) {
        set_frame(settings, mp3);
    }


    return 0;
}