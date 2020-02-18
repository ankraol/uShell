#include "header.h"

static void redirect(int oldfd, int newfd) {
    if (oldfd != newfd) {
        dup2(oldfd, newfd);
        close(oldfd);
    }
}

void mx_fd_change(t_path *reddir, char *command, int in_fd) {
    t_path *p = reddir;
    pid_t pid;
    int fd;
    int status;
    char **task = mx_strsplit(command, ' ');
    char *path = mx_read_env(task[0]);

    write(1, task[0], strlen(task[0]));
    write(1, "\n", 1);
    write(1, path, strlen(path));
    write(1, "\n", 1);
    for (; p; p = p->next) {
        if (!p->next) {
                fd = open(p->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_ISUID);
                if (fd == -1)
                    perror("ush");
                else {
                    pid = fork();
                    if (pid == 0) {
                        redirect(in_fd, 0);
                        redirect(fd, 1);
                        if(execvp(path, task) == -1)
                            perror("ush");
                        else {
                            waitpid(pid, &status, WUNTRACED);
                        }
                    }
                }
        }
        if (p->op == '>') {
            write(1, p->file, strlen(p->file));
            write(1, "\n", 1);
            write(1, &p->op, strlen(&p->op));
            write(1, "\n", 1);
            // pid = fork();
            // if (pid == 0) {
                fd = open(p->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_ISUID);
                if (fd == -1) {
                    perror("ush");
                    write(1, "TROUBLES WITH FD\n", 18);
                }
                else
                {
                    pid = fork();
                    if (pid == 0) {
                        write(1, "REDIRECTION\n", 13);
                        redirect(in_fd, 0);
                        redirect(fd, 1);
                        if (execvp(path, task) == -1) {
                            perror("ush");
                        }
                        // close(fd);
                        write(1, "SUCCESS\n", 9);
                    }
                // }
            // }
            // else
            // {
                // waitpid(pid, &status, WUNTRACED);
            // }
                }
            
                
        }
        else if (p->op == '<') {
            write(1, p->file, strlen(p->file));
            write(1, "\n", 1);
            write(1, &p->op, strlen(&p->op));
            write(1, "\n", 1);
            // pid = fork();
            // if (pid == 0) {
                fd = open(p->file, O_RDONLY);
                if (fd == -1) {
                    perror("ush");
                    write(1, "TROUBLES WITH FD\n", 18);
                }
                else
                {
                    pid = fork();
                    if (pid == 0) {
                        write(1, "INPUT REDIRECTION\n", 19);
                        redirect(fd, 0);
                        if (execvp(path, task) == -1) {
                            perror("ush");
                        }
                        // close(fd);
                        write(1, "SUCCESS\n", 9);
                    }
                                // else
            // {
                // waitpid(pid, &status, WUNTRACED);
            // }
                }
                
            // }
        }
    }
    // mx_strdel(line);
    // *line = direct->task;
    // return status;
}
