#include "header.h"

int print_e(char *str, int *i) {
    if (str[0] == '\\' && str[1] == 'b' && ++(*i) > 0)
        return '\b';
    else if (str[0] == '\\' && str[1] == 't' && ++(*i) > 0)
        return '\t';
    else if (str[0] == '\\' && str[1] == 'n' && ++(*i) > 0)
        return '\n';
    else if (str[0] == '\\' && str[1] == 'v' && ++(*i) > 0)
        return '\v';
    else if (str[0] == '\\' && str[1] == 'f' && ++(*i) > 0)
        return '\f';
    else if (str[0] == '\\' && str[1] == 'r' && ++(*i) > 0)
        return '\r';
    else if (str[0] == '\\' && str[1] == 'e' && ++(*i) > 0)
        return '\033';
    return -1;
}

void mx_print_E(char **file) {
    for (int i = 0; file[i]; i++) {
        mx_printstr(file[i]);
        if (file[i + 1] != NULL)
            mx_printstr(" ");
    }
}

void mx_print_e(char **file, int *err) {
    char tmp;

    for (int i = 0; file[i]; i++) {
        for (int j = 0; file[i][j] != '\0'; j++) {
            if (file[i][j] == '\\' && file[i][j + 1] == '\\')
                tmp = '\\';
            else if (file[i][j] == '\\' && file[i][j + 1] == '0')
                tmp = '\0';
            else if (file[i][j] == '\\' && file[i][j + 1] == 'a' && ++j > 0)
                tmp = '\a';
            else if ((tmp = print_e(&file[i][j], &j)) != -1);
            else if (file[i][j] == '\\' && file[i][j + 1] == 'c' && ++j > 0)
                *err = 0;
            else
                tmp = file[i][j];
            write(1, &tmp, 1);
        }
        if (file[i + 1] != NULL)
            write(1, " ", 1);
    }
}

void mx_echo(char **file, t_builtin_command *command) {
    int err = 1;

    if (command->echo->flag_E)
        mx_print_E(file);
    else
        mx_print_e(file, &err);
    if (!(command->echo->flag_n) && (err == 1))
        write(1, "\n", 1);
}

void mx_valid_flag_echo(t_builtin_command *command, char **arg, int ac) {
    char flag[] = "neE";
    bool flag_priority = true;
    int count_files = 0;
    char **file = NULL;

    memset(command->echo, 0, sizeof(t_echo));
    for(int i = 1; i < ac; i++) {
        if (flag_priority == true) {
            if (arg[i][0] == '-' && arg[i][1] != '-')
                mx_struct_flag_echo(arg[i], command, flag);
            if (arg[i][0] != '-') {
                flag_priority = false;
                count_files++;
            }
            if (arg[i][0] == '-' && arg[i][1] == '-') {
                flag_priority = false;
                count_files++;
            }
        }
        else if (!flag_priority)
            count_files++;
    }
    file = mx_create_file_echo(arg, ac, count_files, file);
    mx_echo(file, command);
    mx_del_strarr(&file);
}
