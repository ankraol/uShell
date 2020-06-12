#include "header.h"

t_reddir *mx_taskCreate(char **arr, int i) {
    t_reddir *task = (t_reddir *)malloc(sizeof(t_reddir));

    task->task = mx_strdup(arr[i]);
    task->input = NULL;
    task->output = NULL;
    if (arr[i + 1])
        task->op = '|';
    else
        task->op = '-';
    return task;
}
