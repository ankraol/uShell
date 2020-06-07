#include "header.h"


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


int mx_valid_command(char **arg, int ac, t_builtin_command *command) {
	char *builtin_str[] = {"cd", "env", "pwd", "which", "echo", "export",
	"unset", "fg", "exit", NULL};
	int err = 0;

	if (strcmp(builtin_str[0], arg[0]) == 0 && strlen(arg[0]) == 2) {
		mx_valid_flag_cd(command, arg, ac, &err);
	}
	else if (strcmp(builtin_str[2], arg[0]) == 0 && strlen(arg[0]) == 3) {
		mx_valid_flag_pwd(command, arg, ac, &err);
		return 0;
	}
	 else if (strcmp(builtin_str[4], arg[0]) == 0 && strlen(arg[0]) == 4) {
	 	mx_valid_flag_echo(command, arg, ac);
	 	return 0;
	 }
	else if (strcmp(builtin_str[1], arg[0]) == 0 && strlen(arg[0]) == 3) {
        mx_valid_flag_env(arg, ac, command);
        return 0;
    }
	else if (strcmp(builtin_str[3], arg[0]) == 0 && strlen(arg[0]) == 5) {
		mx_which(arg, 0);
        return 0;
    }
	else if (strcmp(builtin_str[5], arg[0]) == 0 && strlen(arg[0]) == 6) {
		mx_command_export(command, arg, ac);
        return 0;
    }
	else if (strcmp(builtin_str[6], arg[0]) == 0 && strlen(arg[0]) == 5) {
		mx_unset_command(command, ac, arg);
        return 0;
    }
	else if (strcmp(builtin_str[7], arg[0]) == 0 && strlen(arg[0]) == 2) {
		mx_fg_command(command, arg, ac);
        return 0;
    }
	// else if (strcmp(builtin_str[8], arg[0]) == 0 && strlen(arg[0]) == 4)
	// 	mx_command_exit();
	return 1;
}


