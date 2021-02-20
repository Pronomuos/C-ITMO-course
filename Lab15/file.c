#include "file.h"

int64_t get_file_size(const char* file_name){
    int64_t _file_size = 0;
    struct stat _file_stat_buff;
    int fd = open(file_name, O_RDONLY);
    if(fd == -1) {
        _file_size = -1;
    }
    else {
        if ((fstat(fd, &_file_stat_buff) != 0) || (!S_ISREG(_file_stat_buff.st_mode)))
            _file_size = -1;
        else
            _file_size = _file_stat_buff.st_size;

        close(fd);
    }
    return _file_size;
}

void write_file(File* file) {
    FILE* input = fopen(file->file_name, "wb");
    if (input == NULL) {
        errno = EINVAL;
        perror("Error while writing a file : the file doesnt exist.");
        exit(EXIT_FAILURE);
    }
    fwrite(file->data, file->file_size, 1, input);
    fclose(input);
}


File* read_file(char *file_name) {
    FILE* input = fopen(file_name, "rb");
    if (input == NULL) {
        errno = EINVAL;
        perror("Error while reading a file : the file doesnt exist.");
        exit(EXIT_FAILURE);
    }
    File* file = malloc(sizeof(File));
    file->file_name_size = strlen(file_name) + 1;
    file->file_name = malloc(file->file_name_size * sizeof(char));
    strcpy(file->file_name, file_name);
    file->file_name[file->file_name_size - 1] = '\0';
    file->file_size = get_file_size(file_name);
    file->data = malloc(file->file_size * sizeof(char));
    fread(file->data, file->file_size, 1, input);
    fclose(input);
    return file;
}
