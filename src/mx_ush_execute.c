#include "header.h"


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
    //t_pid_name *buf = *pid_ar;

    // if (mx_substitute(command) == 1) {
        // char **argv = mx_tokens(command, ' ');
        char **argv = mx_tokenSplit(command);
        // mx_substitute(argv);
        printf("ARGUMENTS FOR COMMAND == %s\n", argv[1]);
        printf("COMMAND == %s\n", argv[0]);
        char *path = mx_read_env(argv[0]);
        printf("Checkk\n");
        //printf("PATH == %s\n", path);
        int status;

        
        bool builtin = mx_valid_command(argv, mx_count_elem(argv), pwd, my_command);
        
        if (!builtin) {

        pid = fork();
        // mx_push_back_pid(pid_ar, getpid());
            //  fprintf(stdout, "-----%d------\n", (*pid_ar)->pid);
            //         fflush(stdout);
        if (pid == 0) {
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
            setpgid(0, 0);
            //mx_push_back_pid(pid_ar, getpid());
           // fprintf(stdout, "-----%d------\n", (*pid_ar)->pid);
           //     fflush(stdout);
            //mx_printstr("start");
            if (execvp(path, argv) == -1)
                perror("ushi");
            // if (execve(path, argv, NULL) == -1)
            //     perror("ushi");

            exit(1);
        }
        else
        {
            setpgid(pid, pid);
            tcsetpgrp(1, pid);
            wpid = waitpid(pid, &status, WUNTRACED);
            if (WIFEXITED(status)) {
                tcsetpgrp(1, getpid());
                return 0;
            }
            else if (WIFSTOPPED(status)) {//ctrl+Z
                 //fprintf(stdout, "%d\n", wpid);
                //fflush(stdout);
                mx_printstr("and now stop");
                number = mx_get_pid_num(&my_command->pid_ar);
                printf("%d\n", number);
                mx_push_back_pid(&my_command->pid_ar, wpid, argv[0], number);
                tcsetpgrp(1, getpid());
                return 1;
            //    sleep(2);
            //    kill (wpid, SIGCONT);
            //    wpid = waitpid(pid, &status, WUNTRACED);
            // fprintf(stdout, "-----%d------\n", (*pid_ar)->pid);
            //     fflush(stdout);
                // (*pid_ar) = (*pid_ar)->next;
                // fprintf(stdout, "-----%d------\n", (*pid_ar)->pid);
                // fflush(stdout);
                // mx_printstr("and now stop2");
            }
             else if (WTERMSIG(status)) { //ctrl+C
                 mx_printstr("and now term");
                 sleep(2);
                 tcsetpgrp(1, getpid());
            //     fprintf(stdout, "%d\n", getpid());
            //     fflush(stdout);
             }
             if (status != 0) {
            //     //printf("%d", WTERMSIG(status));
            //     mx_printstr("status<0");
            tcsetpgrp(1, getpid());
                 return status;
             }
        // }

    }
    tcsetpgrp(1, getpid());
    return 0;
    }
    return 0;
}
