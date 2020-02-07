#include "header.h"

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

    all_path = mx_strsplit(environ[13], '=');
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
