#include "header.h"

void mx_struct_flag_echo(char *av, t_builtin_command *command, char *flag) {
	for (int j = 1; av[j] ; j++) {
		if (av[j] == flag[0])
			command->echo->flag_n = true;
		else if (av[j] == flag[1])
			command->echo->flag_e = true;
		else if (av[j] == flag[1])
			command->echo->flag_E = true;
	}
}


void mx_echo(char **file, t_builtin_command *command) {
	for (int i = 0; file[i]; i++) {
		printf("%s", file[i]);
		if (file[i + 1] != NULL)
			printf(" ");
		else if (!(command->echo->flag_n))
			printf("\n");
	}
}

char **mx_create_file_echo(char **av, int ac, int count_files, char **file) {
	bool flag_priority = true;
	file = (char **)malloc(sizeof(char *) * (count_files + 1));
	int g = 0;

	for(int i = 1; i < ac; i++) {
		if (flag_priority == true) {			
			if (av[i][0] != '-') {
				flag_priority = false;
				file[g++] = strdup(av[i]);
			}
			if (av[i][0] == '-' && av[i][1] == '-') {
				flag_priority = false;
				file[g++] = strdup(av[i]);
			}
		}
		else if (!flag_priority) {
			file[g++] = strdup(av[i]);
			flag_priority = false;
		}
	}
	file[count_files] = NULL;
	return file;
}

void mx_valid_flag_echo(t_builtin_command *command, char **arg, int ac) {
	char flag[] = "neE";
	bool flag_priority = true;
	int count_files = 0;
	char **file = NULL;

	command->echo = (t_echo *)malloc(sizeof(t_echo));
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
}
