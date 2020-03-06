#include "header.h"




int mx_ush_execute(char *command, t_pid_name **pid_ar) {
    pid_t pid;
    pid_t wpid;
    //t_pid_name *buf = *pid_ar;

    // if (mx_substitute(command) == 1) {
        char **argv = mx_tokens(command, ' ');
        // mx_substitute(argv);
        // printf("ARGUMENTS FOR COMMAND == %s\n", argv[1]);
        // printf("COMMAND == %s\n", argv[0]);
        char *path = mx_read_env(argv[0]);
        // printf("PATH == %s\n", path);
        int status;


        pid = fork();
        // mx_push_back_pid(pid_ar, getpid());
        //  fprintf(stdout, "-----%d------\n", (*pid_ar)->pid);
        //         fflush(stdout);
        if (pid == 0) {
            mx_push_back_pid(pid_ar, getpid());
            fprintf(stdout, "-----%d------\n", (*pid_ar)->pid);
                fflush(stdout);
            //mx_printstr("start");
            if (execvp(path, argv) == -1)
                perror("ushi");
            exit(1);
        }
        else
        {
            wpid = waitpid(pid, &status, WUNTRACED);
            if (WIFEXITED(status))
                return 0;
            else if (WIFSTOPPED(status)) {//ctrl+Z
                mx_printstr("and now stop");
            // fprintf(stdout, "-----%d------\n", (*pid_ar)->pid);
            //     fflush(stdout);
                (*pid_ar) = (*pid_ar)->next;
                fprintf(stdout, "-----%d------\n", (*pid_ar)->pid);
                fflush(stdout);
                mx_printstr("and now stop2");
            }
            else if (WTERMSIG(status)) { //ctrl+C
                mx_printstr("and now term");
                fprintf(stdout, "%d\n", getpid());
                fflush(stdout);
            }
            if (status != 0) {
                //printf("%d", WTERMSIG(status));
                mx_printstr("status<0");
                return status;
            }
        // }
    }
    return 0;
}
