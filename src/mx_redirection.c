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
    // t_path *p = NULL;
    int status = 2;

    if (tasks[0].op == '|' || tasks[0].output) {
        status = mx_pipe_rec(tasks, 0, 0);
    }
    else {
        status = mx_ush_execute(tasks[0].task);
    }
    return status;
}
