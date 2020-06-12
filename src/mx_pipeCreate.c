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

// static t_reddir *taskCreate(char **arr, int i) {
//     t_reddir *task = (t_reddir *)malloc(sizeof(t_reddir));

//     task->task = mx_strdup(arr[i]);
//     task->input = NULL;
//     task->output = NULL;
//     if (arr[i + 1])
//         task->op = '|';
//     else
//         task->op = '-';
//     return task;
// }

static void printList(t_reddir *tasks) {
    t_path *p1 = tasks->output;
    t_path *p2 = tasks->input;

    if (p1) {
        for(; p1; p1 = p1->next) {
            printf("%s\n", p1->file);
        }
    }
    if (p2) {
        for(; p2; p2 = p2->next) {
            printf("%s\n", p2->file);
        }
    }
}

t_reddir **mx_pipeCreate(char *line) {
    char **pipeArr = mx_customSplit(line, '|');
    int size = arrSize(pipeArr);
    t_reddir **tasks = (t_reddir **)malloc(sizeof(t_reddir*) * (size + 1));
    int i = 0;

    // printf("PIPE CREATE\n");
    for (; pipeArr[i]; i++) {
        if (isOutput(pipeArr[i]))
            mx_outputCreate(pipeArr, tasks, i);
        else {
            tasks[i] = mx_taskCreate(pipeArr, i);
            // printf("%s\n", tasks[i]->task);
        }
        printf("%s\n", tasks[i]->task);
        printf("LIST\n");
        printList(tasks[i]);
    }
    tasks[i] = NULL;
    mx_del_strarr(&pipeArr);
    return tasks;
}
