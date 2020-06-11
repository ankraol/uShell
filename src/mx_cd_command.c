#include "header.h"

void mx_struct_flag_cd(char *av, t_builtin_command *command, char *flag, int *err) {
	for (int j = 1; av[j] ; j++) {
		if (av[j] == flag[0])
			command->cd->flag_s = true;
		else if (av[j] == flag[1])
			command->cd->flag_P = true;
		else if (av[j] > 47 && av[j] < 58) {
            fprintf(stderr, "cd: no such entry in dir stack\n");
            *err = 1;
        }
		else {
			fprintf(stderr, "cd: no such file or directory: -%c\n", av[j]);
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
				file[g++] = mx_strdup(av[i]);
			}
			if (av[i][0] == '-' && av[i][1] == '-')
				flag_priority = false;
		}
		else if (!flag_priority) {
			file[g++] = mx_strdup(av[i]);
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

void mx_home(t_builtin_command *command) {
    struct passwd *pw = getpwuid(getuid());

    if (command->cd->flag_P) {
        mx_strdel(&command->path->oldpwd);
        command->path->oldpwd = mx_strdup(command->path->pwdP);
    }
    else {
        mx_strdel(&command->path->oldpwd);
        command->path->oldpwd = mx_strdup(command->path->pwdL);
    }
    mx_strdel(&command->path->pwdP);
    command->path->pwdP = mx_strdup(pw->pw_dir);
    mx_strdel(&command->path->pwdL);
    command->path->pwdL = mx_strdup(pw->pw_dir);
    chdir(pw->pw_dir);
}

void mx_print_min(char *pwd) {
    struct passwd *pw = getpwuid(getuid());

    if (strstr(pwd, pw->pw_dir) != NULL) {
        int len = strlen(pw->pw_dir);

        printf("~");
        printf("%s\n", pwd + len);
    }
    else
        printf("%s\n", pwd);
}

void mx_cd_flag_min(t_builtin_command *command) {
    chdir(command->path->oldpwd);

    mx_print_min(command->path->oldpwd);

    if (command->cd->flag_P) {
        mx_swap_str(&command->path->oldpwd, &command->path->pwdP);
        command->path->pwdP = getcwd(NULL, 0);
        mx_strdel(&command->path->pwdL);
        command->path->pwdL = mx_strdup(command->path->pwdP);
    }
    else {
        mx_swap_str(&command->path->oldpwd, &command->path->pwdL);
        mx_strdel(&command->path->pwdP);
        command->path->pwdP = getcwd(NULL, 0);
    }
}

void mx_falid_files(char **file, int count_files, t_builtin_command *command, int *err) {
    char *path = NULL;

    if (count_files > 2) {
        fprintf(stderr, "cd: too many arguments\n");
        *err = 1;
    }
    else if (count_files == 2)
        mx_cd_two_args(file, command, err);
    else if (command->cd->arg_min)
        mx_cd_flag_min(command);
    else if (!(command->cd->arg_min) && (count_files == 0 || strcmp(file[0], "~") == 0))
        mx_home(command);
	else {
		path = mx_cd_logic(file, command, err);
		if (path != NULL)
            mx_change_pwd(path, command, err, file);
        mx_strdel(&path);
	}
}

void mx_change_envpwd(t_builtin_command *command) {
    if (command->cd->flag_P)
        setenv("PWD", command->path->pwdP, 1);
    else
        setenv("PWD", command->path->pwdL, 1);
    setenv("OLDPWD", command->path->oldpwd, 1);
}

void mx_valid_flag_cd(t_builtin_command *command, char **arg, int ac, int *err) {
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


