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


int mx_ush_execute(char *command, t_path_builtin *pwd, t_builtin_command *my_command) {
    pid_t pid;
    pid_t wpid;
    int number = 0;

        char *path = NULL;

        int status;
        char **argv = mx_tokenSplit(command);


        bool builtin = mx_valid_command(argv, mx_count_elem(argv), pwd, my_command);
        
        if (!builtin) {
        path = mx_read_env(argv[0], NULL, my_command);
        if (path == NULL) {
            mx_printerr("ush: command not found: ");
            mx_printerr(command);
            mx_printerr("\n");
            mx_del_strarr(&argv);
            return 1;
        }
        
        pid = fork();
        if (pid == 0) {
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
            setpgid(0, 0);
            if (execvp(path, argv) == -1)
                perror("ushi");
            mx_del_strarr(&argv);
            exit(1);
        }
        else
        {
            setpgid(pid, pid);
            tcsetpgrp(1, pid);
            wpid = waitpid(pid, &status, WUNTRACED);
            if (WIFEXITED(status)) {
                tcsetpgrp(1, getpid());
                mx_del_strarr(&argv);
                return 0;
            }
            else if (WIFSTOPPED(status)) {//ctrl+Z
                number = mx_get_pid_num(&my_command->pid_ar);
                mx_push_back_pid(&my_command->pid_ar, wpid, argv[0], number);
                tcsetpgrp(1, getpid());
                mx_del_strarr(&argv);
                return 1;

            }
             else if (WTERMSIG(status)) { //ctrl+C
 
                 tcsetpgrp(1, getpid());
             }
             if (status != 0) {

            tcsetpgrp(1, getpid());
                mx_del_strarr(&argv);
                 return status;
             }
        // }

    }
    tcsetpgrp(1, getpid());
    mx_del_strarr(&argv);
    return 0;
    }
    mx_del_strarr(&argv);
    return 0;
}
