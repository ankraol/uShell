#include "header.h"

static int dir_count(char *command) {
    int count = 0;

    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '|') {
            count++;
        }
    }
    return count;
}

static t_reddir *pipe_check(char *command) {
    int size = dir_count(command);
    t_reddir *tasks = (t_reddir *)malloc(sizeof(t_reddir) * (size + 2));
    int start = 0;
    int q = 0;
    int i = 0;

    for (; command[i] != '\0'; i++) {
        if (command[i] == '|') {
            tasks[q].input = NULL;
            tasks[q].output = NULL;
            mx_command_cut(command, start, i, &tasks[q]);
            tasks[q].op = command[i];
            i++;
            start = i;
            q++;
        }
    }
    tasks[q].input = NULL;
    tasks[q].output = NULL;
    mx_command_cut(command, start, i, &tasks[q]);
    tasks[q].op = '-';
    return tasks;
}



int mx_redirection(char *command) {
    t_reddir *tasks = pipe_check(command);
    int status = 2;
    int input;
    bool extInput = false;

    if (tasks[0].op == '|' || tasks[0].output || tasks[0].input) {
        if (tasks[0].op == '|' || tasks[0].output) {
            status = mx_pipe_rec(tasks, 0, 0, extInput);
        }
        for (int i = 0; tasks[i - 1].op != '-'; i++) {
            if (tasks[i].input) {
                t_path *p = tasks[i].input;
                for (; p;  p = p->next) {
                    input = open(p->file, O_RDONLY);
                    if (input == -1)
                        perror("ush");
                    extInput = true;
                    mx_pipe_rec(tasks, i, input, extInput);
                    extInput = false;
                    close(input);
                }
            }
        }
        for (int i = 0; tasks[i - 1].op != '-'; i++) {
            if (tasks[i].output != NULL) {
                if (tasks[i].output->next) {
                    char *str = mx_file_to_str(tasks[i].output->file);
                    int size = strlen(str);
                    t_path *p = tasks[i].output->next;
                    for (; p;  p = p->next) {
                        int output = open(p->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_ISUID);
                        if (output == -1) {
                            perror("ush");
                        }
                        else {
                            write(output, str, size);
                        }
                        close(output);
                    }
                }
            }
        }
    }
    else {
        status = mx_ush_execute(tasks[0].task);
    }
    return status;
}
