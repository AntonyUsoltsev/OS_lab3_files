#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define BUFF_SIZE 256

void reverse_dir_name(char *dest_str) {
    unsigned int len = strlen(dest_str);
    unsigned int slash_pos = 0;
    for (unsigned int i = len; i > 0; i--) {
        if (dest_str[i] == '/') {
            slash_pos = i;
            break;
        }
    }
    for (int i = 0; i < (len - slash_pos - 1) / 2; i++) {
        char tmp = dest_str[i + slash_pos + 1];
        dest_str[i + slash_pos + 1] = dest_str[len - i - 1];
        dest_str[len - i - 1] = tmp;
    }
}

void reverse_file_name(const char *src_str, char *dest_str) {
    unsigned int len = strlen(src_str);
    unsigned int dot_pos = -1;
    for (unsigned int i = len; i > 0; i--) {
        if (src_str[i] == '.') {
            dot_pos = i;
            break;
        }
    }
    strcpy(dest_str, src_str);
    for (int i = 0; i < dot_pos; i++) {
        dest_str[dot_pos - 1 - i] = src_str[i];
    }
}

char *concat_dir_and_file(const char *s1, const char *s2) {
    unsigned int len1 = strlen(s1);
    unsigned int len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (!result) {
        printf("Не удалось выделить память: result\n");
        exit(1);
    }
    strcpy(result, s1);
    strcpy(result + len1, "/");
    strcpy(result + len1 + 1, s2);
    return result;
}

void reverse_file_data(FILE *file_in, FILE *file_out) {
    fseek(file_in, 0L, SEEK_END);
    int file_size = (int) ftell(file_in);
    rewind(file_in);
    int count_blocks = file_size / BUFF_SIZE;
    if (file_size % BUFF_SIZE != 0) {
        count_blocks += 1;
    }
    for (int i = count_blocks; i > 0; i--) {
        char *buffer = (char *) calloc(sizeof(char), BUFF_SIZE);
        fseek(file_in, (i - 1) * BUFF_SIZE, SEEK_SET);
        unsigned int bytes_read = fread(buffer, sizeof(char), BUFF_SIZE, file_in);
        for (int j = 0; j < bytes_read / 2; j++) {
            char tmp = buffer[j];
            buffer[j] = buffer[bytes_read - j - 1];
            buffer[bytes_read - j - 1] = tmp;
        }
        fprintf(file_out, "%s", buffer);
        fflush(file_out);
        free(buffer);
    }
}

void reverse_file(const char *dir_name, const char *new_dir_name, const char *file_name) {
    char *file_path = concat_dir_and_file(dir_name, file_name);
    char *new_file_name = malloc(sizeof(char) * strlen(file_name));
    if (!new_file_name) {
        printf("Не удалось выделить память: new_file_name\n");
        exit(1);
    }
    reverse_file_name(file_name, new_file_name);
    char *new_file_path = concat_dir_and_file(new_dir_name, new_file_name);

    FILE *file_in = fopen(file_path, "r");
    if (!file_in) {
        printf("Не удалось открыть файл: file_in\n");
        exit(1);
    }
    FILE *file_out = fopen(new_file_path, "w");
    if (!file_out) {
        printf("Не удалось открыть файл: file_out\n");
        exit(1);
    }
    reverse_file_data(file_in, file_out);

    fclose(file_in);
    fclose(file_out);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    char *dir_name, *new_dir_name;
    int arg_len = (int) strlen(argv[1]);
    dir_name = (char *) malloc(sizeof(char) * (arg_len + 1));
    if (!dir_name) {
        printf("Не удалось выделить память: dir_name\n");
        exit(1);
    }
    new_dir_name = (char *) malloc(sizeof(char) * (arg_len + 1));
    if (!new_dir_name) {
        printf("Не удалось выделить память: new_dir_name\n");
        exit(1);
    }

    strcpy(dir_name, argv[1]);
    strcpy(new_dir_name, argv[1]);
    dir_name[arg_len] = '\0';
    new_dir_name[arg_len] = '\0';

    reverse_dir_name(new_dir_name);

    if (mkdir(new_dir_name, 0777) == -1){
        puts("Ошибка при создании директории");
        perror("mkdir");
        exit(1);
    }
    DIR *dir = opendir(dir_name);
    if (!dir) {
        perror("diropen");
        exit(1);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            reverse_file(dir_name, new_dir_name, entry->d_name);
        }
    }
    closedir(dir);
    free(dir_name);
    free(new_dir_name);
    return 0;
}

//DT_UNKNOWN (0) - тип файла неизвестен.
//DT_FIFO (1) - файл является именованным каналом (FIFO).
//DT_CHR (2) - файл является символьным устройством.
//DT_DIR (4) - файл является каталогом.
//DT_BLK (6) - файл является блочным устройством.
//DT_REG (8) - файл является обычным файлом.
//DT_LNK (10) - файл является символической ссылкой.
//DT_SOCK (12) - файл является сокетом.
//DT_WHT (14) - не используется.
