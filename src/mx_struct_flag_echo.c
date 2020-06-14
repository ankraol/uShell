#include "header.h"

void mx_struct_flag_echo(char *av, t_builtin_command *command, char *flag) {
    for (int j = 1; av[j] ; j++) {
        if (av[j] == flag[0])
            command->echo->flag_n = true;
        else if (av[j] == flag[1])
            command->echo->flag_e = true;
        else if (av[j] == flag[2])
            command->echo->flag_E = true;
    }
}
