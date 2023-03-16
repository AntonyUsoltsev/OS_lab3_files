#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 256

int main(int argc, char *argv[]) {
    if (argc < 2) {
        puts("Too few args");
        exit(1);
    }
    puts(argv[0]);
  //  puts("dfd");
//   a)
    if (strcmp(argv[0], "./task2_a") == 0) {
        if (mkdir(argv[1], 0777) == -1) {
            puts("Error while creating directory");
            perror("mkdir");
            exit(1);
        }
    }
//   b)
    else if (strcmp(argv[0], "./task2_b") == 0) {
        DIR *dir = opendir(argv[1]);
        if (!dir) {
            perror("diropen");
            exit(1);
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("%lu - %s type:%d %d\n", entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
        }
    }
//    c)
    else if (strcmp(argv[0], "./task2_c") == 0) {
        if (remove(argv[1]) == -1) {
            puts("Error while removing directory");
            perror("rmdir");
            exit(1);
        }
    }
//    d)
    else if (strcmp(argv[0], "./task2_d") == 0) {
        FILE *file = fopen(argv[1], "wb+");
        if (!file) {
            puts("Error while creating file");
            perror("createfile");
            fclose(file);
            exit(1);
        }
        fclose(file);
    }
//    e)
    else if (strcmp(argv[0], "./task2_e") == 0) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            puts("Error while opening file");
            perror("openfile");
            fclose(file);
            exit(1);
        }
        char *buffer = (char *) calloc(sizeof(char), BUFF_SIZE);
        while (fread(buffer, sizeof(char), BUFF_SIZE, file) > 0) {
            puts(buffer);
        }
        fclose(file);
    }
//    f)
    else if (strcmp(argv[0], "./task2_f") == 0) {
        if (remove(argv[1]) == -1) {
            puts("Error while removing file");
            perror("rmfile");
            exit(1);
        }
    }
//    g)
    else if (strcmp(argv[0], "./task2_g") == 0) {
        if (symlink(argv[1], "symlink_file") != 0) {
            puts("Error while creating symlink");
            perror("crsymlink");
            exit(1);
        }
    }
//    h)
    else if (strcmp(argv[0], "./task2_h") == 0) {
        char *buffer = (char *) calloc(sizeof(char), BUFF_SIZE);
        readlink(argv[1], buffer, BUFF_SIZE);
        puts(buffer);


    }
//    i)
    else if (strcmp(argv[0], "./task2_h") == 0) {
        char *buffer = (char *) calloc(sizeof(char), BUFF_SIZE);
        readlink(argv[1], buffer, BUFF_SIZE);
        puts(buffer);

        FILE *file = fopen(argv[1], "r");
        if (!file) {
            puts("Error while opening file");
            perror("openfile");
            fclose(file);
            exit(1);
        }
        char *buf = (char *) calloc(sizeof(char), BUFF_SIZE);
        while (fread(buf, sizeof(char), BUFF_SIZE, file) > 0) {
            puts(buf);
        }
        fclose(file);


    }else {
        puts("hi3");
    }
//    char *dir_name, *new_dir_name;
//    int arg_len = (int) strlen(argv[1]);
//    dir_name = (char *) malloc(sizeof(char) * (arg_len + 1));
//    if (!dir_name) {
//        printf("Не удалось выделить память: dir_name\n");
//        exit(1);
//    }
//    new_dir_name = (char *) malloc(sizeof(char) * (arg_len + 1));
//    if (!new_dir_name) {
//        printf("Не удалось выделить память: new_dir_name\n");
//        exit(1);
//    }
//
//    strcpy(dir_name, argv[1]);
//    strcpy(new_dir_name, argv[1]);
//    dir_name[arg_len] = '\0';
//    new_dir_name[arg_len] = '\0';
//
//  //  reverse_dir_name(new_dir_name);
//    mkdir(new_dir_name, 0777);
//
//    DIR *dir = opendir(dir_name);
//    if (!dir) {
//        perror("diropen");
//        exit(1);
//    }
//
//    struct dirent *entry;
//    while ((entry = readdir(dir)) != NULL) {
//        if (entry->d_type == DT_REG) {
//        //    reverse_file(dir_name, new_dir_name, entry->d_name);
//        }
//    }
//    closedir(dir);
//    free(dir_name);
//    free(new_dir_name);
    return 0;
}