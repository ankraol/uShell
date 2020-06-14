#include "header.h"

char *if_program(char *file, struct stat sb) {

    if ((sb.st_mode & S_IFREG) == S_IFREG)
        return strdup(file);
    else {
        mx_printerr("ush: permission denied:");
        mx_printerr(file);
        mx_printerr("\n");
        return NULL;
    }
}

char *is_path(char *path, char *file) {
    char *last_path = NULL;
    struct stat sb;

    last_path = mx_strjoin(path, "/");
    last_path = mx_strjoin_two(last_path, file);
    if (lstat(last_path, &sb) < 0) {
        mx_strdel(&last_path);
        return NULL;
    }
    return last_path;
}

char *mx_read_env(char *file, char *path, t_builtin_command *my_command) {
    char *last_path = NULL;
    struct stat sb;

    if (lstat(file, &sb) >= 0)
        last_path = if_program(file, sb);
    else {
        if (path != NULL) {
            last_path = is_path(path, file);
        }
        else {
            last_path = mx_no_path(file, my_command); 
        }
    }
    return last_path;

}
