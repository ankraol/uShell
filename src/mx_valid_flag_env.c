#include "header.h"


void mx_valid_flag_env(char **arg, int ac, t_builtin_command *command, t_path_builtin *pwd) {

    if (ac == 1)
        mx_env_one();


    else if (ac > 1) {
        mx_env_two(arg, ac, command, pwd);
        }

}

