#include "header.h"

static bool compare(char *builtin_str, char *arg) {
    int dif = strcmp(builtin_str, arg);

    if (dif == 0 || dif == 32)
        return true;
    return false;
}

int mx_valid_command(char **arg, int ac, t_builtin_command *command) {
	char *builtin_str[] = {"cd", "env", "pwd", "which", "echo", "export", "unset", "fg", "exit", "true", "false", NULL};
	int err = 0;

	if (compare(builtin_str[0], arg[0]) && strlen(arg[0]) == 2)
		mx_valid_flag_cd(command, arg, ac, &err);
	else if (compare(builtin_str[2], arg[0]) && strlen(arg[0]) == 3)
		mx_valid_flag_pwd(command, arg, ac, &err);
	else if (compare(builtin_str[4], arg[0]) && strlen(arg[0]) == 4)
	 	mx_valid_flag_echo(command, arg, ac);
	else if (compare(builtin_str[1], arg[0]) && strlen(arg[0]) == 3)
        mx_valid_flag_env(arg, ac, command, &err);
    else if (compare(builtin_str[3], arg[0]) && strlen(arg[0]) == 5)
        mx_which(arg, &err);
    else if (compare(builtin_str[5], arg[0]) && strlen(arg[0]) == 6)
        mx_command_export(command, arg, ac, &err);
    else if (compare(builtin_str[6], arg[0]) && strlen(arg[0]) == 5)
        mx_unset_command(command, ac, arg, &err);
    else if (compare(builtin_str[7], arg[0]) && strlen(arg[0]) == 2)
        mx_fg_command(command, arg, ac, &err);
    else if (compare(builtin_str[8], arg[0]) && strlen(arg[0]) == 4)
        mx_command_exit(command, &err, arg, ac);
    else if (compare(builtin_str[9], arg[0]) && strlen(arg[0]) == 4)
        err = 0;
    else if (compare(builtin_str[10], arg[0]) && strlen(arg[0]) == 5)
        err = 1;
    else
        err = 999;
    return err;
}


