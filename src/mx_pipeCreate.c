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
    t_inc index;

    memset(&index, 0, sizeof(t_inc));
    for (; pipeArr[index.a]; index.a++) {
        if (isOutput(pipeArr[index.a]))
            mx_outputCreate(pipeArr, tasks, index.a);
        else {
            if(iSinput(pipeArr[index.a])) {
                mx_inputCreate(pipeArr, pipeArr[index.a], tasks, index);
            }
            else
                tasks[index.a] = mx_taskCreate(pipeArr, index.a);
        }
    }
    tasks[index.a] = NULL;
    mx_del_strarr(&pipeArr);
    return tasks;
}
