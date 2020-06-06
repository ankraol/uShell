#include "header.h"

bool mx_zero_arr(char **str) {
    for (int i = 0; str[i] != NULL; i++) {
        if (str[i][0] != '\0')
            return true;
    }
    return false;
}

char *mx_make_logic_path(char **tmp2, char *tmp) {
    char *tmp1 = NULL;

    for (int i = 0; tmp2[i]; i++) {
        if (tmp2[i][0] != '\0') {
            tmp = mx_strjoin(tmp1, "/");
            if (tmp1 != NULL)
                mx_strdel(&tmp1);
            tmp1 = mx_strjoin(tmp, tmp2[i]);
            if (tmp != NULL)
                mx_strdel(&tmp);
        }
    }
    return tmp1;
}

void mx_change_pwd(char *tmp1, t_builtin_command *command, int *err, char **file) {
    if (chdir(tmp1) != 0) {
        if (mx_str_count(file) == 2)
            fprintf(stderr, "cd: no such file or directory: %s\n", file[1]);
        else
            fprintf(stderr, "cd: no such file or directory: %s\n", file[0]);
        *err = 1;
    }
    else if (command->cd->flag_P) {
        mx_strdel(&command->path->oldpwd);
        command->path->oldpwd = mx_strdup(command->path->pwdP);
        mx_strdel(&command->path->pwdL);
        command->path->pwdL = getcwd(NULL, 0);
    }
    else {
        mx_strdel(&command->path->oldpwd);
        command->path->oldpwd = mx_strdup(command->path->pwdL);
        mx_strdel(&command->path->pwdL);
        command->path->pwdL = mx_strdup(tmp1);
    }
    mx_strdel(&command->path->pwdP);
    command->path->pwdP = getcwd(NULL, 0);
}

void mx_cd_two_args(char **file, t_builtin_command *command, int *err) {
    if (strcmp(file[0], command->path->pwdP) == 0 || strcmp(command->path->pwdL, file[0]) == 0) {
        char *tmp = mx_strjoin(file[0], "/");
        char *tmp1 = mx_strjoin(tmp, file[1]);
        char **tmp2 = my_strsplit(tmp1, '/');

        mx_strdel(&tmp);
        mx_strdel(&tmp1);
        mx_change_path(tmp2);
        if (mx_zero_arr(tmp2))
            tmp1 = mx_make_logic_path(tmp2, tmp);
        else
            tmp1 = mx_strdup("/");
        mx_change_pwd(tmp1, command, err, file);
        mx_strdel(&tmp1);
    }
    else {
        fprintf(stderr, "cd: string not in pwd: %s\n", file[0]);
        *err = 1;
    }
}
