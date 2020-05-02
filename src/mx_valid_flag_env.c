#include "header.h"


 void mx_set_signal() {
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    setpgid(0, 0);
}

int mx_count_elem(char **av) {
    int i = 0;

    while (av[i])
        i++;
    return i;
}

int mx_child(char *command, t_builtin_command *my_command, char **new_env,
             char ***argv) {
    int val_ret = 0;

    mx_set_signal();
    if (my_command->execute == false) {
        if (execve(my_command->path_for_ex, *argv, new_env) == -1) {
            mx_mistake(command, argv, &(my_command->path_for_ex));
            val_ret = 1;
        }
    }
    if (my_command->execute == true) {
        if (execvp(my_command->path_for_ex, *argv) == -1) {
            mx_mistake(command, argv, &(my_command->path_for_ex));
            val_ret = 1;
        }
    }
    return val_ret;
}


void mx_valid_flag_env(char **arg, int ac, t_builtin_command *command) {

    if (ac == 1)
        mx_env_one();


    else if (ac > 1) {
        mx_env_two(arg, ac, command);
        }

}

