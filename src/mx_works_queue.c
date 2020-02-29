#include "header.h"

static int worksCount(char *line) {
    int count = 1;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ';')
            count += 1;
    }
    return count;
}

// static void listPrint(t_queue *list) {
    // t_queue *p = list;
// 
    // for (; p; p = (*p).next) {
        // printf("command-%s,operand-%c\n", (*p).command, (*p).op);
    // }
// 
// }

t_queue **mx_works_queue(char *line) {
    int size = worksCount(line);
    char **jobs = mx_strsplit(line, ';');
    t_queue **list = (t_queue **)malloc(sizeof(t_queue *) * (size + 1));

    for (int i = 0; i < size; i++) {
        list[i] = NULL;
        mx_logicOp(jobs[i], &list[i]);
    }
    list[size] = NULL;
    return list;
}
