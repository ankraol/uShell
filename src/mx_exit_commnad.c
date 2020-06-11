#include "header.h"


void mx_command_exit(t_builtin_command *com, int *err, char **argv, int ac) {
    if (com->pid_ar != NULL) {
        mx_printerr("ush: you have suspended jobs.\n");
        *err = 1;
        return;
    }
    if (ac == 1) {
        com->trig = true;
    }
    else {
        if (ac > 2) {
            mx_printerr("ush: exit: too many arguments\n");
            *err = 1;
        }
        else {
           com->exit_code = atoi(argv[1]);
           com->trig = true;
        }
    }
}
