#include "header.h"




int mx_ush_execute(char *command) {
    pid_t pid;
    pid_t wpid;
    // if (mx_substitute(command) == 1) {
        char **argv = mx_tokens(command, ' ');
        // mx_substitute(argv);
        // printf("ARGUMENTS FOR COMMAND == %s\n", argv[1]);
        // printf("COMMAND == %s\n", argv[0]);
        char *path = mx_read_env(argv[0]);
        // printf("PATH == %s\n", path);
        int status;


        pid = fork();
        if (pid == 0) {
            //mx_printstr("start");
            if (execvp(path, argv) == -1)
                perror("ush");
                    exit(1);
        }
        else
        {
            wpid = waitpid(pid, &status, WUNTRACED);
            if (WIFEXITED(status))
                return 0;
            else if (WIFSTOPPED(status))//ctrl+Z
                mx_printstr("and now stop");
            else if (WTERMSIG(status)) { //ctrl+C
                mx_printstr("and now term");
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
