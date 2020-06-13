#include "header.h"

static void pushBack(t_path **input, char *file) {
    t_path **p = input;

    if (!(*p)) {
        (*p) = (t_path *)malloc(sizeof(t_path));
        (*p)->file = mx_customDup(file);
        (*p)->op = '>';
        (*p)->next = NULL;
    }
    else {
        for (; (*p)->next; p = &(*p)->next);
        (*p)->next = (t_path *)malloc(sizeof(t_path));
        (*p)->next->file = mx_customDup(file);
        (*p)->next->op = '>';
        (*p)->next->next = NULL;
    }

}

static t_reddir *inputTask(char **pipeArr, char *command, int i) {
    t_reddir *task = (t_reddir *)malloc(sizeof(t_reddir));

    task->task = mx_customDup(command);
    task->input = NULL;
    task->output = NULL;
    if (pipeArr[i + 1])
        task->op = '|';
    else
        task->op = '-';
    return task;
}

void mx_inputCreate(char **pipeArr, char *outputArr, t_reddir **tasks, int i, int j) {
    char **inputArr = mx_customSplit(outputArr, '<');

    if (j == 0)
        tasks[i] = inputTask(pipeArr, inputArr[0], i);
    for (int k = 1; inputArr[k]; k++)
        pushBack(&tasks[i]->input, inputArr[k]);
    mx_del_strarr(&inputArr);
}
