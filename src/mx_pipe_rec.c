#include "header.h"

static void redirect(int oldfd, int newfd) {
    if (oldfd != newfd) {
        dup2(oldfd, newfd);
        close(oldfd);
    }
}

int mx_pipe_rec(t_reddir *command, int pos, int in_fd, bool extInput, t_builtin_command *my_command) {
    int status = 0;
    char **task = NULL;
    char *path = NULL;
    pid_t pid;
    pid_t wpid;
    int val_ret = 0;
    int number = 0;


    if (command[pos].op == '-') {
        if (command[pos].output) {
            mx_fd_change(command, pos, in_fd, extInput, my_command);
        }
        else {
            pid = fork();
            if (pid == 0) {
                close(0);
                dup(in_fd);
                close(in_fd);
                task = mx_strsplit(command[pos].task, ' ');
                path = mx_read_env(task[0], NULL, my_command);
                if (execvp(path, task) == -1) {
                    perror("psh");
                }
            }
            else
            {
                wpid = waitpid(pid, &status, WUNTRACED);
                if (WIFEXITED(status))
                    val_ret = 0;
                else if (WIFSTOPPED(status)) {//ctrl+Z
                    number = mx_get_pid_num(&my_command->pid_ar);
                    mx_push_back_pid(&my_command->pid_ar, wpid, "test", number);
                    val_ret = 146;
                }
                else if (WTERMSIG(status)) {//ctrl+C
                    val_ret = 130;
                    mx_printstr("\n");
                }
                else if (status != 0)
                    val_ret = 1;
            }
        }
    }
    else if (command[pos].op == '|') {
        if (command[pos].output) {
            mx_fd_change(command, pos, in_fd, extInput, my_command);
        }
        int fd[2];
        pipe(fd);
        pid = fork();
        if (pid == 0) {
            redirect(in_fd, 0);
            redirect(fd[1], 1); /* write to fd[1] */
            task = mx_strsplit(command[pos].task, ' ');
            path = mx_read_env(task[0], NULL, my_command);
            if (execvp(path, task) == -1) {
                perror("ush");
            }
        }
        else {
            if (fd[1] != 1)
                close(fd[1]);
            if (in_fd != 0)
                close(in_fd); /* unused */
            mx_pipe_rec(command, pos + 1, fd[0], extInput, my_command);
        }
    }
    return status;
}
