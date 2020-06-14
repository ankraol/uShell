#include "header.h"

void mx_del_all(char ***argv, char **path) {
    if (*argv != NULL)
        mx_del_strarr(argv);
    if (*path != NULL)
        mx_strdel(path);
}

void mx_mistake(char *command, char ***argv, char **path, bool flag) {
    if (flag) {
        mx_printerr("ush: ");
        mx_printerr("command not found: ");
        mx_printerr(command);
        mx_printerr("\n");
    }
    else{
        mx_printerr("env: ");
        mx_printerr(command);
        mx_printerr(": No such file or directory\n");
    }
    mx_del_all(argv, path);
}
