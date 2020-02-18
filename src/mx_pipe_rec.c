#include "header.h"

static void redirect(int oldfd, int newfd) {
    if (oldfd != newfd) {
        dup2(oldfd, newfd);
        close(oldfd);
    }
}

int mx_pipe_rec(t_reddir *command, int pos, int in_fd) {
    int status = 0;
    char **task = NULL;
    char *path = NULL;
    t_path *p = NULL;
    pid_t pid;
    int output;
    // int input;
    char *str;
    int size;

    if (command[pos].op == '-') {
        if (command[pos].path->next) {
            p = command[pos].path->next;
                if (p->op == '>') {
                    output = open(p->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_ISUID);
                    if (output == -1)
                        perror("ush");
                    else {
                        pid = fork();
                        if (pid == 0) {
                            redirect(in_fd, 0);
                            redirect(output, 1);
                            task = mx_strsplit(command[pos].task, ' ');
                            path = mx_read_env(task[0]);
                            if (execvp(path, task) == -1)
                                perror("lsh");
                        }
                        else {
                         waitpid(pid, &status, WUNTRACED);
                        }
                    }
                    if (p->next) {
                        str = mx_file_to_str(p->file);
                        size = strlen(str);
                        for (p = p->next; p; p = p->next) {
                            output = open(p->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_ISUID);
                            write(output, str, size);
                        }
                    }
                }

        }
        else {
            pid = fork();
            if (pid == 0) {
                redirect(in_fd, 0);
                task = mx_strsplit(command[pos].task, ' ');
                path = mx_read_env(task[0]);
                if (execvp(path, task) == -1)
                    perror("lsh");
            }
            else
            {
                waitpid(pid, &status, WUNTRACED);
            }
        }
    }
    else if (command[pos].op == '|'){
        // if (command[pos].path->next) {/*if there is some files reddirections*/
            // mx_fd_change(command[pos].path->next, command[pos].task, in_fd);
        // }
        if (command[pos].path->next) {
            p = command[pos].path->next;
                if (p->op == '>') {
                    output = open(p->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_ISUID);
                    if (output == -1)
                        perror("ush");
                    else {
                        pid = fork(); 
                            if (pid == 0) {
                                redirect(in_fd, 0);
                                redirect(output, 1);
                                task = mx_strsplit(command[pos].task, ' ');
                                path = mx_read_env(task[0]);
                                if(execvp(path, task) == -1)
                                    perror("ush");
                            }
                            else {
                                waitpid(pid, &status, WUNTRACED);
                            }
                    }
                    if (p->next) {
                        str = mx_file_to_str(p->file);
                        size = strlen(str);
                        for (p = p->next; p; p = p->next) {
                            write(1, "cycle\n", 7);
                            output = open(p->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_ISUID);
                            write(output, str, size);
                        }
                    }
                }
                // if (p->op == '<') {
                    // input = open(p->file, O_RDONLY);
                    // if (input == -1) {
                        // perror("ush");
                    // }
                // }
        }        
        int fd[2];
        pipe(fd);
        pid = fork();
        if (pid == 0) {
            close(fd[0]);
            redirect(in_fd, 0);
            redirect(fd[1], 1); /* write to fd[1] */
            task = mx_strsplit(command[pos].task, ' ');
            path = mx_read_env(task[0]);
            if (execvp(path, task) == -1) {
                perror("lsh");
            }
        }
        else {
            if (fd[1] != 1)
                close(fd[1]);
            if (in_fd != 0)
                close(in_fd); /* unused */
            mx_pipe_rec(command, pos + 1, fd[0]);
        }
    }
    return status;
}
