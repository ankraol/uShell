#include "header.h"

void mx_struct_flag_cd(char *av, t_builtin_command *command, char *flag, int *err) {
	for (int j = 1; av[j] ; j++) {
		if (av[j] == flag[0])
			command->cd->flag_s = true;
		else if (av[j] == flag[1])
			command->cd->flag_P = true;
		else if (av[j] > 47 && av[j] < 58)
			fprintf(stderr, "cd: no such entry in dir stack\n");
		else {
			fprintf(stderr, "cd: no such file or directory: ");
			char c = av[j];
			fprintf(stderr, "%c" ,c);
			fprintf(stderr, "\n");
			*err = 1;
		}
	}
}

char **mx_create_file(char **av, int ac, int count_files, char **file) {
	bool flag_priority = true;
	file = (char **)malloc(sizeof(char *) * (count_files + 1));
	int g = 0;

	for(int i = 1; i < ac; i++) {
		if (flag_priority == true) {			
			if (av[i][0] != '-') {
				flag_priority = false;
				file[g++] = strdup(av[i]);
			}
			if (av[i][0] == '-' && av[i][1] == '-')
				flag_priority = false;
		}
		else if (!flag_priority) {
			file[g++] = strdup(av[i]);
			flag_priority = false;
		}
	}
	file[count_files] = NULL;
	return file;
}


void mx_swap_str(char **str1, char **str2) {
	char *tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

void mx_command_cd(char **file, int *err, t_builtin_command *command, t_path_builtin *pwd) {
	if (command->cd->arg_min) {
		if (command->cd->flag_P) {
			mx_swap_str(&pwd->oldpwd, &pwd->pwdP);
			printf("%s\n", pwd->pwdP);
		}
		else {
			mx_swap_str(&pwd->oldpwd, &pwd->pwdL);
			printf("%s\n", pwd->pwdL);
		}
	}
	 if (chdir(pwd->pwdL) != 0) {
		fprintf(stderr, "cd: no such file or directory: %s\n", file[0]);
		*err = 1;
	}
	if (!(command->cd->arg_min)) {
		if (command->cd->flag_P) {
			free(pwd->oldpwd);
			pwd->oldpwd = strdup(pwd->pwdP);
		}
		free(pwd->pwdP);
		pwd->pwdP = mx_strnew(PATH_MAX);
		getcwd(pwd->pwdP, PATH_MAX);
	}
}

void mx_falid_files(char **file, int count_files, t_builtin_command *command,
	t_path_builtin *pwd, int *err) {

	if (count_files > 2) {
		fprintf(stderr, "cd: too many arguments\n");
		*err = 1;
	}
	else if (count_files == 2) {
		fprintf(stderr, "cd: string not in pwd: ");
		fprintf(stderr, "%s\n", file[0]);
		*err = 1;
	}
	else if (!(command->cd->arg_min) && (count_files == 0 || strcmp(file[0], "~") == 0)) {
		if (command->cd->flag_P) {
			free(pwd->oldpwd);
			pwd->oldpwd = strdup(pwd->pwdP);
		}
		else {
			free(pwd->oldpwd);
			pwd->oldpwd = strdup(pwd->pwdL);
		}
		free(pwd->pwdP);
		pwd->pwdP = strdup(getenv("HOME"));
		free(pwd->pwdL);
		pwd->pwdL = strdup(getenv("HOME"));
		chdir(getenv("HOME"));
	}
	else if (command->cd->arg_min)
		mx_command_cd(&pwd->oldpwd, err, command, pwd);
	else {
		mx_cd_logic(file, command, err, pwd);
		mx_command_cd(file, err, command, pwd);
	}
}

void mx_valid_flag_cd(t_builtin_command *command, char **arg, int ac, t_path_builtin *pwd, int *err) {
	char flag[] = "sP";
	bool flag_priority = true;
	int count_files = 0;
	char **file = NULL;

	command->cd = (t_cd *)malloc(sizeof(t_cd));
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
	mx_falid_files(file, count_files, command, pwd, err);
}


