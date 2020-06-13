#include "header.h"

static bool isInput(char *outputArr) {
    for (int i = 0; outputArr[i] != '\0'; i++) {
        if (outputArr[i] == '<')
            return true;
    }
    return false;
}

static void pushBack(t_path **output, char *file) {
    t_path **p = output;

    if (!(*p)) {
        (*p) = (t_path *)malloc(sizeof(t_path));
        (*p)->file = mx_customDup(file);
        (*p)->op = '>';
        (*p)->next = NULL;
    }
    else {
        for (; (*p)->next; p = &(*p)->next);
        (*p)->next = (t_path *)malloc(sizeof(t_path));
        (*p)->next->file = mx_customDup (file);
        (*p)->next->op = '>';
        (*p)->next->next = NULL;
    }

}

static t_reddir *outputTask(char **pipeArr, char *command, int i) {
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

void mx_outputCreate(char **pipeArr, t_reddir **tasks, int i) {
    char **outputArr = mx_customSplit(pipeArr[i], '>');

    for (int j = 0; outputArr[j]; j++) {
        if (isInput(outputArr[j]))
            mx_inputCreate(pipeArr ,outputArr[j], tasks, i, j);
        else if (j == 0)
            tasks[i] = outputTask(pipeArr, outputArr[j], i);
        else
            pushBack(&tasks[i]->output, outputArr[j]);
    }
    mx_del_strarr(&outputArr);
}
