#include "header.h"

static void redirect(int oldfd, int newfd) {
    if (oldfd != newfd) {
        close(oldfd);
        dup(newfd);
        close(newfd);
    }
}

void mx_fd_change(t_reddir *command, int pos, int in_fd, bool extInput, t_builtin_command *my_command) {
    t_path *p = command[pos].output;
    char **task = NULL;
    char *path = NULL;
    pid_t pid;
    int status;
    int output;

    for(; p; p = p->next) {
        if (extInput == false) {
            output = open(p->file, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_ISUID);
        }
        else if (extInput == true) {
            output = open(p->file, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_ISUID);
        }
        if (output == -1)
            perror("ush");
        else {
            pid = fork();
            if (pid == 0) {
                redirect(0, in_fd);
                redirect(1, output);
                task = mx_tokens(command[pos].task, ' ');
                path = mx_read_env(task[0], NULL, my_command);
                if (execvp(path, task) == -1) {
                    printf("TASK = %s\n", command[pos].task);
                    perror("lsh");
                }
            }
            else {
                close(output);
                waitpid(pid, &status, WUNTRACED);
            }
        }
    }
}
