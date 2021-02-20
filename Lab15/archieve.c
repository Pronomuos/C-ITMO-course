#include "archieve.h"

Archive* create_archive (char* archive_name, unsigned files_number, char** file_names) {
    char *pattern = ".+\\.arc$";
    regex_t preg;
    regcomp(&preg, pattern, REG_EXTENDED);
    if (regexec(&preg, archive_name, 0, 0, 0)) {
        errno = ENOEXEC;
        perror("Error while creating archive file. "
               "The file name format is not arc!");
        exit(EXIT_FAILURE);
    }
    Archive* arch_file = malloc(sizeof(Archive));
    arch_file->archive_id[0] = 'A';
    arch_file->archive_id[1] = 'R';
    arch_file->archive_id[2] = 'C';
    arch_file->archive_id[3] = 'H';
    arch_file->archive_name = archive_name;
    arch_file->files_number = files_number;
    arch_file->files = malloc(files_number * sizeof(File));
    for (int i = 0; i < files_number; i++) {
        arch_file->files[i] = malloc(sizeof(File));
        arch_file->files[i] = read_file(file_names[i]);
    }

    write_archive(archive_name, arch_file);
    return arch_file;
}

Archive* read_archive(char* file_name) {

    char *pattern = ".+\\.arc$";
    regex_t preg;
    regcomp(&preg, pattern, REG_EXTENDED);
    if (regexec(&preg, file_name, 0, 0, 0)) {
        errno = ENOEXEC;
        perror("Error while reading archive file. "
               "The file format is not arc!");
        exit(EXIT_FAILURE);
    }
    FILE* file = fopen(file_name, "rb");
    if (file == NULL) {
        errno = EINVAL;
        perror("Error while reading an archive file : the file doesnt exist.");
        exit(EXIT_FAILURE);
    }
    Archive* arch = malloc(sizeof(Archive));
    fread(arch->archive_id, sizeof(char), 4, file);
    if (strncmp(arch->archive_id, "ARCH", 4) != 0) {
        errno = EINVAL;
        perror("Error while reading an archive file : wrong format of the file.");
        exit(EXIT_FAILURE);
    }
    fread(&arch->files_number, sizeof(unsigned), 1, file);
    arch->files = malloc(arch->files_number * sizeof(File*));
    for (int i = 0; i < arch->files_number; i++) {
        arch->files[i] = malloc(sizeof(File));
        fread(&arch->files[i]->file_name_size, sizeof(unsigned), 1, file);
        arch->files[i]->file_name = malloc(arch->files[i]->file_name_size * sizeof(char));
        fread(arch->files[i]->file_name, sizeof(char), arch->files[i]->file_name_size, file);
        fread(&arch->files[i]->file_size, sizeof(unsigned), 1, file);
        arch->files[i]->data = malloc(arch->files[i]->file_size * sizeof(char));
        fread(arch->files[i]->data, sizeof(char), arch->files[i]->file_size, file);
    }
    fclose(file);
    return arch;
}

void write_archive(char* archive_name, Archive* arch) {
    FILE* file = fopen(archive_name, "wb");
    fwrite(arch->archive_id, sizeof(char), 4, file);
    fwrite(&arch->files_number, sizeof(arch->files_number), 1, file);
    for (int i = 0; i < arch->files_number; i++) {
        fwrite(&arch->files[i]->file_name_size, sizeof(unsigned), 1, file);
        fwrite(arch->files[i]->file_name, sizeof(char), arch->files[i]->file_name_size, file);
        fwrite(&arch->files[i]->file_size, sizeof(unsigned), 1, file);
        fwrite(arch->files[i]->data, sizeof(char), arch->files[i]->file_size, file);
    }
    fclose(file);
}

void list_archive (char* archive_name) {
    Archive *arch_file = read_archive(archive_name);
    printf("Archive file %s:\n", archive_name);
    for (int i = 0; i < arch_file->files_number; ++i)
        printf("%s ", arch_file->files[i]->file_name);
}

void extract_archive(char* archive_name) {
    Archive *arch_file = read_archive(archive_name);
    for (int i = 0; i < arch_file->files_number; i++)
        write_file(arch_file->files[i]);
}
