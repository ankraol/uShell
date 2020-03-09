 #include "header.h"

static void first(t_builtin_command *command, char **arg, int i) {
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
    }
}


void mx_for_fg_command(t_builtin_command *command, char **arg, int ac) {
    int n = 0;

    for(int i = 1; i < ac; i++) {
        if (arg[i][0] == '%')
            first(command, arg, i);
        else {
            n = mx_get_peid_name(arg[i], command->pid_ar);
            if (n != 0) {
                mx_wait_cont(&(command)->pid_ar, n);
            }
            else {
                mx_printerr("fg: job not found: ");
                mx_printerr(arg[i]);
                mx_printerr("\n");
            }
        }
    }
}
