#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void reverse_dir_name( char *dest_str) {
    unsigned int len = strlen(dest_str);
    int slash_pos = 0;
    for (int i = len; i > 0; i--) {
        if (dest_str[i] == '/') {
            slash_pos = i;
            break;
        }
    }
    //strcpy(dest_str, src_str);
    for (int i = 0 ; i < (len - slash_pos -1)/2 ; i++) {
        //strcpy(dest_str[len + slash_pos - i],src_str[i]);
        char tmp = dest_str[i + slash_pos + 1];
        dest_str[i + slash_pos + 1] = dest_str[len - i - 1];
        dest_str[len - i - 1] = tmp;
    }
}

void reverse_file_name(const char *src_str,  char *dest_str) {
    unsigned int len = strlen(src_str);
    int dot_pos = -1;
    for (int i = len; i > 0; i--) {
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
    strcpy(result, s1);
    strcpy(result + len1, "/");
    strcpy(result + len1 + 1, s2);
    return result;
}

void reverse_file(const char *dir_name, const char *new_dir_name, const char *file_name) {
    char *file_path = concat_dir_and_file(dir_name, file_name);
    FILE *file_in = fopen(file_path, "r");

    char *new_file_name = malloc(sizeof(char) * strlen(file_name));
    reverse_file_name(file_name, new_file_name);
    char *new_file_path = concat_dir_and_file(new_dir_name, new_file_name);
    FILE *file_out = fopen(new_file_path, "w");

    fseek(file_in, 0L, SEEK_END);
    int file_size = ftell(file_in);
    rewind(file_in);
    char *buffer = malloc(file_size * sizeof(char));
    fread(buffer, sizeof(char), file_size, file_in);

    // Переворачивание содержимого
    for (int i = 0; i < file_size / 2; i++) {
        char tmp = buffer[i];
        buffer[i] = buffer[file_size - i - 1];
        buffer[file_size - i - 1] = tmp;
    }

    fwrite(buffer, sizeof(char), file_size, file_out);

    free(buffer);
    fclose(file_in);
    fclose(file_out);
}

int main(int argc, char *argv[]) {
//   dir = opendir("./../testdir");
//   dir = opendir("./../");

    int arg_len = strlen(argv[1]);
    char *dir_name = (char *)malloc(sizeof(char) * (arg_len + 1));
    char *new_dir_name = ( char *)  malloc(sizeof(char) * (arg_len + 1));

    if (argc > 1) {
        strcpy(dir_name , argv[1]);
        strcpy(new_dir_name , argv[1]);
        dir_name[arg_len] = '\0';
        new_dir_name[arg_len] = '\0';
    } else {
        dir_name = "/mnt/d/Antony/NSU_Education/4_Term/OS/lab3_files/testdir";
    }

    reverse_dir_name(new_dir_name);
    mkdir(new_dir_name, 0777);

    DIR* dir = opendir(dir_name);
    if (!dir) {
        perror("diropen");
        exit(1);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%lu - %s type:%d %d\n",
               entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
        if (entry->d_type == DT_REG) {
            reverse_file(dir_name, new_dir_name, entry->d_name);
        }
    }
    closedir(dir);
    free(dir_name);
    free(new_dir_name);
    return 0;
};

//DT_UNKNOWN (0) - тип файла неизвестен.
//DT_FIFO (1) - файл является именованным каналом (FIFO).
//DT_CHR (2) - файл является символьным устройством.
//DT_DIR (4) - файл является каталогом.
//DT_BLK (6) - файл является блочным устройством.
//DT_REG (8) - файл является обычным файлом.
//DT_LNK (10) - файл является символической ссылкой.
//DT_SOCK (12) - файл является сокетом.
//DT_WHT (14) - не используется.