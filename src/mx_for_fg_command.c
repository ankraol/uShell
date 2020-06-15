 #include "header.h"

 static void name_check(char *name, t_builtin_command *command, int *err) {
    int n = 0;

    n = mx_get_peid_name(name, command->pid_ar);
    if (n != 0) {
        mx_wait_cont(&(command)->pid_ar, n, err);
    }
    else {
        mx_printerr("fg: job not found: ");
        mx_printerr(name);
        mx_printerr("\n");
        *err = 1;
    }
 }

static void first(t_builtin_command *command, char **arg, int i, int *err) {
    int n = 0;

    printf("DIGIT == %d, num = %d, num2 == %d\n", isdigit(*((int *)(&(arg[i][1])))-48), isdigit('l'), isdigit((int) 5));
    printf("DIGIT == %d, num = %d, num2 == %d\n", mx_isdigit(*((int *)(&(arg[i][1])))-48), mx_isdigit('l'), mx_isdigit((int) 5));
    printf("MY_NUM = %d\n", *((int *)(&(arg[i][1])))- 48);
    printf("ATOI -- %d\n", atoi(&(arg[i][1])));

    if (atoi(&(arg[i][1])) != 0) {
        printf("IN NUM \n");
        n = atoi(&(arg[i][1]));
        n = mx_get_peid(n, command->pid_ar);
        if (n != 0) {
            mx_wait_cont(&(command)->pid_ar, n, err);
        }
        else {
            mx_printerr("fg: ");
            mx_printerr(arg[i]);
            mx_printerr(": no such job\n");
            *err = 1;
        }
    }
    else {
        name_check(&(arg[i][1]), command, err);
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
                mx_wait_cont(&(com)->pid_ar, n, err);
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
