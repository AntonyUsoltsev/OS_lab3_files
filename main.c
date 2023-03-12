#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void reverse_dir_name(char *src_str, char *dest_str) {
    unsigned int len = strlen(src_str);
    int slash_pos = 0;
    for (int i = len; i > 0; i--){
        if (src_str[i] == '/'){
            slash_pos = i;
            break;
        }
    }
    strcpy(dest_str, src_str);
    for (int i = slash_pos + 1; i < len; i++) {
        dest_str[len + slash_pos - i] = src_str[i];
    }
}


void reverse_file(char *dir_name, char *file_name) {
  //  FILE *file = fopen();

}


int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
//   dir = opendir("./../testdir");
//   dir = opendir("./../");
    char *dir_name;
    if (argc > 0) {
        dir_name = argv[1];
    } else {
        dir_name = "/mnt/d/Antony/NSU_Education/4_Term/OS/lab3_files/testdir";
    }
    int len = strlen(dir_name);
    char *new_dir_name = malloc(sizeof (char ) * len);
    reverse_dir_name(dir_name,new_dir_name);
    if (strlen(dir_name)!= strlen(new_dir_name)){
        exit(1);
    }

    dir = opendir(dir_name);
    if (!dir) {
        perror("diropen");
        exit(1);
    }
    mkdir(new_dir_name,0777);

    while ((entry = readdir(dir)) != NULL) {
        printf("%lu - %s type:%d %d\n",
               entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
        if (entry->d_type == DT_REG) {
            reverse_file(dir_name, entry->d_name);
        }
    }


    closedir(dir);

//    FILE *file = fopen("./../testdir/testfile.txt", "r");
//    if (!file) {
//        perror("fileopen");
//        exit(1);
//    }
//    char a = (char) fgetc(file);
//    printf("%c", a);
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