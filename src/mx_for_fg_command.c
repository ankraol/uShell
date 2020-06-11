 #include "header.h"

static void first(t_builtin_command *command, char **arg, int i, int *err) {
    int n = 0;

    n = atoi(&(arg[i][1]));
    n = mx_get_peid(n, command->pid_ar);
    if (n != 0) {
        mx_wait_cont(&(command)->pid_ar, n);
    }
    else {
        mx_printerr("fg: ");
        mx_printerr(arg[i]);
        mx_printerr(": no such job\n");
        *err = 1;
    }
}


void mx_for_fg_command(t_builtin_command *com, char **arg, int ac, int *err) {
    int n = 0;

    for(int i = 1; i < ac; i++) {
        if (arg[i][0] == '%')
            first(com, arg, i, err);
        else {
            n = mx_get_peid_name(arg[i], com->pid_ar);
            if (n != 0) {
                mx_wait_cont(&(com)->pid_ar, n);
            }
            else {
                mx_printerr("fg: job not found: ");
                mx_printerr(arg[i]);
                mx_printerr("\n");
                *err = 1;
            }
        }
    }
}
