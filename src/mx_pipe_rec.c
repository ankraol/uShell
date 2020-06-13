#include "header.h"

static void redirect(int oldfd, int newfd) {
    if (oldfd != newfd) {
        dup2(oldfd, newfd);
        close(oldfd);
    }
}

static int for_child(t_reddir *command, int pos, int in_fd, t_builtin_command *my_command) {
    char **task = NULL;
    char *path = NULL;
    int ret = 0;

    close(0);
    dup(in_fd);
    close(in_fd);
    task = mx_strsplit(command[pos].task, ' ');
    path = mx_read_env(task[0], NULL, my_command);
    if (execvp(path, task) == -1) {
        mx_mistake(task[0], &task, &path, true);
        ret = 1;
    }
    mx_del_all(&task, &path);
    return ret;
}

static void parent(pid_t pid, int *val_ret) {
    pid_t wpid;
    int status = 0;

    wpid = waitpid(pid, &status, WUNTRACED);
    if (WIFEXITED(status))
        *val_ret = 0;
    else if (WIFSTOPPED(status)) {//ctrl+Z
        *val_ret = 146;
    }
    else if (WTERMSIG(status)) {//ctrl+C
        *val_ret = 130;
        mx_printstr("\n");
    }
    else if (status != 0)
        *val_ret = 1;
}
static int in_fork(t_builtin_command *my_command, int pos, int in_fd, int *fd, t_reddir *command) {
    char **task = NULL;
    char *path = NULL;

    redirect(in_fd, 0);
    redirect(fd[1], 1); /* write to fd[1] */
    task = mx_strsplit(command[pos].task, ' ');
    path = mx_read_env(task[0], NULL, my_command);
    if (execvp(path, task) == -1) {
        mx_mistake(task[0], &task, &path, true);
        return 1;
    }
    mx_del_all(&task, &path);
    return 0;
}
static int two_child(t_reddir *command, int pos, int in_fd, bool extInput, t_builtin_command *my_command) {
    pid_t pid;
    int fd[2];

    if (command[pos].output)
        mx_fd_change(command, pos, in_fd, extInput, my_command);
    pipe(fd);
    pid = fork();
    if (pid == 0) {
        if (in_fork(my_command, pos, in_fd, fd, command) == 1)
            return 1;
    }
    else {
        if (fd[1] != 1)
            close(fd[1]);
        if (in_fd != 0)
            close(in_fd); /* unused */
        mx_pipe_rec(command, pos + 1, fd[0], extInput, my_command);
    }
    return 0;
}

int mx_pipe_rec(t_reddir *command, int pos, int in_fd, bool extInput, t_builtin_command *my_command) {
    pid_t pid;
    int val_ret = 0;

    if (command[pos].op == false) {
        if (command[pos].output)
            mx_fd_change(command, pos, in_fd, extInput, my_command);
        else {
            pid = fork();
            if (pid == 0) {
                if (for_child(command, pos, in_fd, my_command) == 1)
                    return 1;
            }
            else
                parent(pid, &val_ret);
        }
    }
    else if (command[pos].op == true)
        if (two_child(command, pos, in_fd, extInput, my_command) == 1)
            return 1;
    return val_ret;
}
