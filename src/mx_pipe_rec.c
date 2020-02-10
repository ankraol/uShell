#include "header.h"

static void redirect(int oldfd, int newfd) {
    if (oldfd != newfd) {
        dup2(oldfd, newfd);
        close(oldfd);
    }
}

void mx_pipe_rec(char **argv, int pos, int in_fd) {
    char **task = NULL;
    char *path = NULL;
    pid_t pid;
    // pid_t wpid;
    // int status = 0;

    if (argv[pos+1] == NULL) {
        printf("afterred");
        redirect(in_fd, 0);
        task = mx_strsplit(argv[pos], ' ');
        path = mx_read_env(task[0]);
        if (execvp(path, task) == -1) {
            // return 1;
            perror("lsh");
        // printf("ENNNNNNDDDDD");
        }
        printf("ENNNNNNDDDDD");
        // status = mx_ush_execute(argv[pos]);
    }
    else {
        int fd[2];
        pipe(fd);
        pid = fork();
        if (pid == 0) {
            close(fd[0]);
            redirect(in_fd, 0);  /* read from in_fd */
            redirect(fd[1], 1); /* write to fd[1] */
            task = mx_strsplit(argv[pos], ' ');
            path = mx_read_env(task[0]);
            if (execvp(path, task) == -1) {
                // return 1;
                perror("lsh");
            }
            printf("ENNNNNNDDDDD");

            // status = mx_ush_execute(argv[pos]);
        }
        else {
            // printf("ENNNNNNDDDDD");

            close(fd[1]);
            close(in_fd); /* unused */
            mx_pipe_rec(argv, pos + 1, fd[0]);
            // printf("ENNNNNNDDDDD");
            // waitpid(pid, &status, WUNTRACED);
                // if (status != 0)
                    // return ;
        }
    }
    // return status;
}
