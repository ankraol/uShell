#include "header.h"

static void redirect(int oldfd, int newfd) {
    if (oldfd != newfd) {
        dup2(oldfd, newfd);
        close(oldfd);
    }
}

void mx_fd_change(t_reddir *command, int pos, int in_fd) {
    t_path *p = NULL;
    char *str = NULL;
    int size;
    char **task = NULL;
    char *path = NULL;
    pid_t pid;
    int status;
    int output;

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
