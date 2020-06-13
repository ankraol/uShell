#include "header.h"

static void execute(t_queue *work, t_builtin_command *my_command) {
    t_queue *p = work;
    int status;

    for (; p; p = (*p).next) {
        (*p).command = mx_tokenCut((*p).command, 0, mx_strlen((*p).command));
        (*p).command = mx_substitute((*p).command, my_command);
        status = mx_redirection((*p).command, my_command);
        if (((*p).op == '&' && status == 1)
            || ((*p).op == '|' && status == 0))
            {
                p = (*p).next;
            }
    }
}

int mx_subExec(t_builtin_command *my_command, char *line) {
    int fd[2];
    t_queue **work = NULL;
    pid_t pid;

    pipe(fd);
    pid = fork();
    if (pid == 0) {
        close(1);
        dup(fd[1]);
        close(fd[1]);
        work = mx_works_queue(line);
        for (int i = 0; work[i]; i++) {
            execute(work[i], my_command);
        }
        exit(0);
    }
    else
        close(fd[1]);
    mx_strdel(&line);
    return fd[0];
}
