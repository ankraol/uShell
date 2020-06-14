#include "header.h"

void mx_struct_flag_cd(char *av, t_builtin_command *command, char *flag,
                        int *err) {
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
