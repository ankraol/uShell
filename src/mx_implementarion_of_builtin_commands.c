#include "header.h"
#include <stdio.h>

// void mx_struct_flag_env(char *av, t_builtin_command *command, char *flag) {
// 	for (int j = 1; av[j] ; j++) {
// 		if (av[j] == flag[0])
// 			command->env->flag_i = true;
// 		else if (av[j] == flag[1])
// 			command->env->flag_P = true;
// 		else if (av[j] == flag[3])
// 			command->env->flag_u = true;
// 		else {
// 			perror("env: illegal option --");
// 			char c = av[j];
// 			perror(&c);
// 			perror("usage: env [-i] [-P utilpath][-u name] [name=value ...] [utility [argument ...]]");
// 			perror("\n");
// 			exit(1);
// 		}
// 	}
// }

// void mx_valid_flag_env(t_builtin_command *command, char **arg, int ac) {
// 	char flag[] = "iPu";
// 	bool flag_priority = true;
// 	int count_files = 0;
// 	char **file = NULL;

// 	for(int i = 1; i < ac; i++) {
// 		if (flag_priority == true) {
// 			if (arg[i][0] == '-' && arg[i][1] != '-')
// 				mx_struct_flag_env(arg[i], command, flag);
// 			if (arg[i][0] != '-') {
// 				flag_priority = false;
// 				count_files++;
// 			}
// 			if (arg[i][0] == '-' && arg[i][1] == '-')
// 				flag_priority = false;
// 		}
// 		else if (!flag_priority)
// 			count_files++;
// 	}
// }


// void mx_struct_flag_which(char *av, t_builtin_command *command, char *flag) {
// 	for (int j = 1; av[j] ; j++) {
// 		if (av[j] == flag[0])
// 			command->which->flag_a = true;
// 		else if (av[j] == flag[1])
// 			command->which->flag_s = true;
// 		else {
// 			perror("which: bad option: ");
// 			char c = av[j];
// 			perror(&c);
// 			perror("\n");
// 			exit(1);
// 		}
// 	}
// }

// void mx_valid_flag_which(t_builtin_command *command, char **arg, int ac) {
// 	char flag[] = "as";
// 	bool flag_priority = true;
// 	int count_files = 0;
// 	char **file = NULL;

// 	for(int i = 1; i < ac; i++) {
// 		if (flag_priority == true) {
// 			if (arg[i][0] == '-' && arg[i][1] != '-')
// 				mx_struct_flag_which(arg[i], command, flag);
// 			if (arg[i][0] != '-') {
// 				flag_priority = false;
// 				count_files++;
// 			}
// 			if (arg[i][0] == '-' && arg[i][1] == '-')
// 				flag_priority = false;
// 		}
// 		else if (!flag_priority)
// 			count_files++;
// 	}
// }

// void mx_struct_flag_echo(char *av, t_builtin_command *command, char *flag) {
// 	for (int j = 1; av[j] ; j++) {
// 		if (av[j] == flag[0])
// 			command->echo->flag_n = true;
// 		else if (av[j] == flag[1])
// 			command->echo->flag_e = true;
// 		else if (av[j] == flag[1])
// 			command->echo->flag_E = true;
// 	}
// }

// void mx_valid_flag_echo(t_builtin_command *command, char **arg, int ac) {
// 	char flag[] = "neE";
// 	bool flag_priority = true;
// 	int count_files = 0;
// 	char **file = NULL;

// 	for(int i = 1; i < ac; i++) {
// 		if (flag_priority == true) {
// 			if (arg[i][0] == '-' && arg[i][1] != '-')
// 				mx_struct_flag_echo(arg[i], command, flag);
// 			if (arg[i][0] != '-') {
// 				flag_priority = false;
// 				count_files++;
// 			}
// 			if (arg[i][0] == '-' && arg[i][1] == '-')
// 				flag_priority = false;
// 		}
// 		else if (!flag_priority)
// 			count_files++;
// 	}
// }

bool mx_valid_command(char **arg, int ac, t_path_builtin *pwd, t_builtin_command *command) {
	char *builtin_str[] = {"cd", "env", "pwd", "which", "echo", "export",
	"unset", "fg", "exit", NULL};
	int err = 0;

	// command->env = (t_env *)malloc(sizeof(t_env));
	// command->which = (t_which *)malloc(sizeof(t_which));

	// memset(command->env, 0, sizeof(t_env));
	// memset(command->which, 0, sizeof(t_which));
	

	if (strcmp(builtin_str[0], arg[0]) == 0 && strlen(arg[0]) == 2) {
		mx_valid_flag_cd(command, arg, ac, pwd, &err);
		return true;
	}
	else if (strcmp(builtin_str[2], arg[0]) == 0 && strlen(arg[0]) == 3) {
		mx_valid_flag_pwd(command, arg, ac, &err, pwd);
		return true;
	}
	else if (strcmp(builtin_str[4], arg[0]) == 0 && strlen(arg[0]) == 4) {
		mx_valid_flag_echo(command, arg, ac);
		return true;
	}
	// else if (strcmp(builtin_str[1], arg[0]) == 0 && strlen(arg[0]) == 3)
	// 	mx_valid_flag_env(command, arg, ac);
	// else if (strcmp(builtin_str[3], arg[0]) == 0 && strlen(arg[0]) == 5)
	// 	mx_valid_flag_which(command, arg, ac);
	// else if (strcmp(builtin_str[5], arg[0]) == 0 && strlen(arg[0]) == 6)
	// 	mx_command_export();
	// else if (strcmp(builtin_str[6], arg[0]) == 0 && strlen(arg[0]) == 5)
	// 	mx_command_unset();
	// else if (strcmp(builtin_str[7], arg[0]) == 0 && strlen(arg[0]) == 2)
	// 	mx_command_fg();
	// else if (strcmp(builtin_str[8], arg[0]) == 0 && strlen(arg[0]) == 4)
	// 	mx_command_exit();
	return false;
}


