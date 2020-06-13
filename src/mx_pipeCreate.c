#include "header.h"

static bool isOutput(char *pipeArr) {
    for (int i = 0; pipeArr[i] != '\0'; i++) {
        if (pipeArr[i] == '>')
            return true;
    }
    return false;
}

static int arrSize(char **arr) {
    int i = 0;

    for ( ; arr[i]; i++);
    return i;
}

static bool iSinput(char *command) {
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '<')
            return true;
    }
    return false;
}

t_reddir **mx_pipeCreate(char *line) {
    char **pipeArr = mx_customSplit(line, '|');
    int size = arrSize(pipeArr);
    t_reddir **tasks = (t_reddir **)malloc(sizeof(t_reddir*) * (size + 1));
    int i = 0;

    for (; pipeArr[i]; i++) {
        if (isOutput(pipeArr[i]))
            mx_outputCreate(pipeArr, tasks, i);
        else {
            if(iSinput(pipeArr[i]))
                mx_inputCreate(pipeArr, pipeArr[i], tasks, i, 0);
            else
                tasks[i] = mx_taskCreate(pipeArr, i);
        }
    }
    tasks[i] = NULL;
    mx_del_strarr(&pipeArr);
    return tasks;
}
