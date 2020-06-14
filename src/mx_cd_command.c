#include "header.h"

void mx_change_envpwd(t_builtin_command *command) {
    if (command->cd->flag_P)
        setenv("PWD", command->path->pwdP, 1);
    else
        setenv("PWD", command->path->pwdL, 1);
    setenv("OLDPWD", command->path->oldpwd, 1);
}

void mx_valid_flag_cd(t_builtin_command *command, char **arg, int ac,
                        int *err) {
	char flag[] = "sP";
	bool flag_priority = true;
	int count_files = 0;
	char **file = NULL;

	memset(command->cd, 0, sizeof(t_cd));
	for(int i = 1; i < ac; i++) {
		if (flag_priority == true) {
			if (arg[i][0] == '-' && arg[i][1] != '-')
				mx_struct_flag_cd(arg[i], command, flag, err);
			if (strcmp(arg[i], "-") == 0)
				command->cd->arg_min = true;
			if (arg[i][0] != '-') {
				flag_priority = false;
				count_files++;
			}
			if (arg[i][0] == '-' && arg[i][1] == '-')
				flag_priority = false;
		}
		else if (!flag_priority)
			count_files++;
	}
	file = mx_create_file(arg, ac, count_files, file);
	mx_falid_files(file, count_files, command, err);
    mx_change_envpwd(command);
    mx_del_strarr(&file);
}


