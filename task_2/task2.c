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

//  a) создать каталог, указанный в аргументе;
    if (strcmp(argv[0], "./task2_a") == 0) {
        if (mkdir(argv[1], 0777) == -1) {
            puts("Error while creating directory");
            perror("mkdir");
            exit(1);
        }
    }

//  b) вывести содержимое каталога, указанного в аргументе;
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

//  c) удалить каталог, указанный в аргументе;
    else if (strcmp(argv[0], "./task2_c") == 0) {
        if (remove(argv[1]) == -1) {
            puts("Error while removing directory");
            perror("rmdir");
            exit(1);
        }
    }

//  d) создать файл, указанный в аргументе;
    else if (strcmp(argv[0], "./task2_d") == 0) {
        FILE *file = fopen(argv[1], "wb+");
        if (!file) {
            puts("Error while creating file");
            perror("create_file");
            fclose(file);
            exit(1);
        }
        fclose(file);
    }

//  e) вывести содержимое файла, указанного в аргументе;
    else if (strcmp(argv[0], "./task2_e") == 0) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            puts("Error while opening file");
            perror("open_file");
            fclose(file);
            exit(1);
        }
        char *buffer = (char *) calloc(sizeof(char), BUFF_SIZE);
        while (fread(buffer, sizeof(char), BUFF_SIZE, file) > 0) {
            puts(buffer);
        }
        fclose(file);
    }

//  f) удалить файл, указанный в аргументе;
    else if (strcmp(argv[0], "./task2_f") == 0) {
        if (remove(argv[1]) == -1) {
            puts("Error while removing file");
            perror("rm_file");
            exit(1);
        }
    }

//  g) создать символьную ссылку на файл, указанный в аргументе;
    else if (strcmp(argv[0], "./task2_g") == 0) {
        if (symlink(argv[1], "symlink_file") != 0) {
            puts("Error while creating symlink");
            perror("cr_symlink");
            exit(1);
        }
    }

//  h) вывести содержимое символьной ссылки, указанный в аргументе;
    else if (strcmp(argv[0], "./task2_h") == 0) {
        char *buffer = (char *) calloc(sizeof(char), BUFF_SIZE);
        if (readlink(argv[1], buffer, BUFF_SIZE) == -1) {
            puts("Error while reading symlink");
            perror("read_symlink");
            exit(1);
        }
        puts(buffer);
    }

//  i) вывести содержимое файла, на который указывает символьная ссылка,  указанная в аргументе;
    else if (strcmp(argv[0], "./task2_i") == 0) {
        char *buffer = (char *) calloc(sizeof(char), BUFF_SIZE);
        if (readlink(argv[1], buffer, BUFF_SIZE) == -1) {
            puts("Error while reading symlink");
            perror("read_symlink");
            exit(1);
        }
        puts(buffer);
        FILE *file = fopen(buffer, "r");
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


    }

//  j) удалить символьную ссылку на файл, указанный в аргументе;
    else if (strcmp(argv[0], "./task2_j") == 0) {
        if (remove(argv[1]) == -1) {
            puts("Error while removing symlink");
            perror("rm_symlink");
            exit(1);
        }
    }

//  k) создать жесткую ссылку на файл, указанный в аргументе;
    else if (strcmp(argv[0], "./task2_k") == 0) {
        if (link(argv[1], "hardlink_file") != 0) {
            puts("Error while creating hardlink");
            perror("cr_hardlink");
            exit(1);
        }
    }
//  l) удалить жесткую ссылку на файл, указанный в аргументе;
    else if (strcmp(argv[0], "./task2_l") == 0) {
        if (remove(argv[1]) == -1) {
            puts("Error while removing hardlink");
            perror("rm_hardlink");
            exit(1);
        }
    }

//  m) вывести права доступа к файлу, указанному в аргументе и количество жестких ссылок на него;
    else if (strcmp(argv[0], "./task2_m") == 0) {
        struct stat fileStat;
        if (stat(argv[1], &fileStat) < 0) {
            perror("Error: cannot make stat file");
            exit(1);
        }
        printf("Count of hardlinks: %lu\n", fileStat.st_nlink);

        printf("Permissions: ");
        printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n");
    }

//  n) изменить права доступа к файлу, указанному в аргументе.
    else if (strcmp(argv[0], "./task2_n") == 0) {
//        4: read permission
//        2: write permission
//        1: execute permission
        if (chmod(argv[1], 0700) == -1) {
            perror("Error changing file permissions");
            return 1;
        }
    }
    else {
        puts("Unknown program");
    }
    return 0;
}