#include "header.h"





int mx_ush_execute_env(char *command, t_builtin_command *my_command,
                       char **new_env, char *path) {
    pid_t pid;
    pid_t wpid;
    int number = 0;
    //t_pid_name *buf = *pid_ar;

    // if (mx_substitute(command) == 1) {
        // char **argv = mx_tokens(command, ' ');
        printf("FIRST = %s\n", command);
        char **argv = mx_tokenSplit(command);
        // mx_substitute(argv);
        printf("ARGUMENTS FOR COMMAND == %s\n", argv[1]);
        printf("COMMAND == %s\n", argv[0]);
        
        printf("Checkk\n");
        //printf("PATH == %s\n", path);
        int status;


        path = mx_read_env(argv[0], path, my_command);
        if (path == NULL) {
            mx_printerr("env: ");
            mx_printerr(command);
            mx_printerr(": No such file or directory\n");
;
            return 1;
        }
        
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
            // if (execvp(path, argv) == -1)
            //     perror("ushi");
            if (new_env == NULL)
                printf("NULL");
            if (execve(path, argv, new_env) == -1)
                mx_printerr("env: ");
                mx_printerr(command);
                mx_printerr(": No such file or directory\n");

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
