#include "header.h"

int mx_ush_execute(char *command) {
    pid_t pid;
    pid_t wpid;
    char **argv = mx_strsplit(command, ' ');
    char *path = mx_read_env(argv[0]);
    int status;
    
    pid = fork();
    if (pid == 0) {        
        if (execvp(path, argv) == -1)
            perror("lsh");
                exit(1);
    }
    else
    {
         wpid = waitpid(pid, &status, WUNTRACED);
        if (status != 0)
            return 1;
    }
    return 0;
}
