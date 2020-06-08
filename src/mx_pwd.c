#include "header.h"

void mx_struct_flag_pwd(char *av, t_builtin_command *command, char *flag, int *err) {
	for (int j = 1; av[j] ; j++) {
		if (av[j] == flag[0])
			command->pwd->flag_L = true;
		else if (av[j] == flag[1])
			command->pwd->flag_P = true;
		else {
			fprintf(stderr, "pwd: bad option: ");
			char c = av[j];
			fprintf(stderr, "%c\n", c);
			*err = 1;
		}
	}
}

void mx_valid_flag_pwd(t_builtin_command *command, char **arg, int ac, int *err) {
	char flag[] = "LP";
	bool flag_priority = true;
	int count_files = 0;
	command->pwd = (t_pwd *)malloc(sizeof(t_pwd));
	memset(command->pwd, 0, sizeof(t_pwd));

	for(int i = 1; i < ac; i++) {
		if (flag_priority == true) {
			if (arg[i][0] == '-' && arg[i][1] != '-')
				mx_struct_flag_pwd(arg[i], command, flag, err);
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
	if (count_files > 0) {
        fprintf(stderr, "pwd: too many arguments\n");
        *err = 1;
    }
	if (command->pwd->flag_P || command->cd->flag_P)
		printf("%s\n", command->path->pwdP);
	else
		printf("%s\n", command->path->pwdL);
    free(command->pwd);
}
