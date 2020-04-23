#include "header.h"

static void inside_dir(char *file, char *bin_dir, int *flag) {
    struct dirent *entry;
    DIR *dir = NULL;

    dir = opendir(bin_dir);
    if (dir != NULL) {
        entry = readdir(dir);
        while (entry) {
            if (strcmp(entry->d_name, file) == 0) {
                *flag = 1;
                break;
            }
            entry = readdir(dir);
        }
        closedir(dir);
    }
}

static char *find_in_dir(char **bin_arr, char *file) {
    int i = 0;
    int flag = 0;
    char *last_path = NULL;

    for(i = 0; bin_arr[i]; i++) {
        inside_dir(file, bin_arr[i], &flag);
        if (flag == 1)
            break;
    }
    if (flag == 0)
        return NULL;
    last_path = mx_strjoin(bin_arr[i], "/");
    last_path = mx_strjoin_two(last_path, file);    
    return last_path;
}

char *mx_no_path(char *file, t_builtin_command *my_command) {
    char *name = getenv("PATH");
    char **bin_arr = NULL;
    char *last_path = NULL;

    if (name != NULL)
        bin_arr = mx_strsplit(name, ':');
    else {
        if (my_command->unset_path == true)
            return NULL;
        else {
            bin_arr = (char **)malloc(sizeof(char *) * 3);
            bin_arr[0] = strdup("/usr/bin");
            bin_arr[1] = strdup("/bin");
            bin_arr[2] = NULL;
        }
    }
    last_path = find_in_dir(bin_arr, file);
    mx_del_strarr(&bin_arr);
    return last_path;
}
