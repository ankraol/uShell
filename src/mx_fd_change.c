#include "header.h"

static void redirect(int oldfd, int newfd) {
    close(oldfd);
    dup(newfd);
    close(newfd);
}

// static void input_redirection(t_path *p, t_path *inp, char **task, char *path) {
//     int output;
//     int input;
//     pid_t pid;

//     for (; inp; inp = inp->next) {
//         output = open(p->file, O_RDWR | O_APPEND, S_IRUSR | S_IWUSR | S_ISUID);
//         input = open(inp->file, O_RDWR);
//         if (output == -1)
//             perror("ush");
//         else if (input == -1)
//             perror("ush");
//         else {
//             pid = fork();
//             if (pid == 0) {
//                 redirect(0, input);
//                 redirect(1, output);
//                 if (execvp(path, task) == -1)
//                     perror("lsh");
//             }
//         }
//     }
// }

void mx_fd_change(t_reddir *command, int pos, int in_fd) {
    t_path *p = command[pos].output;
    t_path *inp = command[pos].input;
    // char *str = NULL;
    // int size;
    char **task = NULL;
    char *path = NULL;
    pid_t pid;
    int status;
    int output;
    int input = 0;
    // char *buf = NULL;
    // FILE *stream;

    for(; p; p = p->next) {
        
        output = open(p->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_ISUID);
        if (output == -1)
            perror("ush");
        else {
            pid = fork();
            if (pid == 0) {
                redirect(0, in_fd);
                redirect(1, output);
                task = mx_strsplit(command[pos].task, ' ');
                path = mx_read_env(task[0]);
                if (execvp(path, task) == -1)
                    perror("lsh");
            }
            else {
                waitpid(pid, &status, WUNTRACED);
            }
            if (inp) {
                // input_redirection(p, inp, task, path);
                for (; inp; inp = inp->next) {
                    output = open(p->file, O_RDWR | O_APPEND, S_IRUSR | S_IWUSR | S_ISUID);
                    input = open(inp->file, O_RDWR);
                    if (output == -1)
                        perror("ush");
                    else if (input == -1)
                        perror("ush");
                    else {
                        pid = fork();
                        if (pid == 0) {
                            redirect(0, input);
                            redirect(1, output);
                            task = mx_strsplit(command[pos].task, ' ');
                            path = mx_read_env(task[0]);
                            if (execvp(path, task) == -1)
                                perror("lsh");
                        }
                    }
                }
            }
        }
    }
    // if (p->next) {
    //     str = mx_file_to_str(p->file);
    //     size = strlen(str);
    //     for (p = p->next; p; p = p->next) {
    //         output = open(p->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_ISUID);
    //         write(output, str, size);
    //     }
    // }
}
