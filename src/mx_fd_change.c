#include "header.h"

static void redirect(int oldfd, int newfd) {
    if (oldfd != newfd) {
        close(oldfd);
        dup(newfd);
        close(newfd);
    }
}

static void in_fork(t_builtin_command *my_command, int pos, int in_fd, int output, t_reddir **command) {
    char **task = NULL;
    char *path = NULL;

    redirect(0, in_fd);
    redirect(1, output);

    task = mx_strsplit(command[pos]->task, ' ');
    path = mx_read_env(task[0], NULL, my_command);
    if (execvp(path, task) == -1) {
        mx_mistake(task[0], &task, &path, true);
        return;
    }
    mx_del_all(&task, &path);
}

static void open_file(bool extInput, char *file, int *output) {
    if (extInput == false) {
        *output = open(file, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR
                        | S_ISUID);
    }
    else if (extInput == true) {
        *output = open(file, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR 
                        | S_ISUID);
    }
}

void mx_fd_change(t_reddir **command, int pos, int in_fd, bool extInput, t_builtin_command *my_command) {
    t_path *p = command[pos]->output;
    pid_t pid;
    int status;
    int output;

    for(; p; p = p->next) {
        open_file(extInput, p->file, &output);
        if (output == -1)
                perror("ush: ");
        else {
            pid = fork();
            if (pid == 0) {
               in_fork(my_command, pos, in_fd, output, command);
            }
            else {
                close(output);
                waitpid(pid, &status, WUNTRACED);
            }
        }
    }
}
