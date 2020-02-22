#include "header.h"

static int worksCount(char *line) {
    int count = 1;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ';')
            count += 1;
    }
    return count;
}

t_tree **mx_works_queue(char *line) {
    int size = worksCount(line);
    t_tree **queue = (t_tree **)malloc(sizeof(t_tree *) * (size + 1));
    char **jobs = mx_strsplit(line, ';');

    for (int i = 0; i < size; i++) {
        queue[i] = mx_parcing(jobs[i]);
    }
    queue[size] = NULL;
    return queue;
}
