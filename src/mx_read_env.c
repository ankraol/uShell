#include "header.h"

static int check(char *path) {
    if (path[0] == 'P' && path[1] == 'A'
    && path[2] == 'T' && path[3] == 'H') {
        return 0;
    }
    return 1;
}

char *mx_read_env(char *file) {
    extern char **environ;
    char **all_path;
    char *bin_str;
    char **bin_arr;
    DIR *dir = NULL;
    char *exe = NULL;
    int flag = 0;
    char *last_path = NULL;
    int i = 0;
    int pl = 0;

    // printf("***%s\n" , environ[15]);
    for (; check(environ[pl]) == 1; pl++);
    all_path = mx_strsplit(environ[pl], '=');
    bin_str = strdup(all_path[1]);
    bin_arr = mx_strsplit(bin_str, ':');
    mx_del_strarr(&all_path);
    mx_strdel(&bin_str);

    for(i = 0; bin_arr[i]; i++) {
        dir = opendir(bin_arr[i]);
        struct dirent *entry;
        if (dir != NULL) {
            entry = readdir(dir);
            while (entry) {
                if (strcmp(entry->d_name, file) == 0) {
                    exe = strdup(entry->d_name);
                    flag = 1;
                    break;
                }
                entry = readdir(dir);
            }
        }
        closedir(dir);
        if (flag == 1)
            break;
    }
    last_path = mx_strjoin(bin_arr[i], "/");
    last_path = mx_strjoin_two(last_path, file);
    return last_path;

}
