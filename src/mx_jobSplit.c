#include "header.h"

static void pushBack(t_list **jobs, char *multiColumn) {
    t_list **p = jobs;

    if ((*jobs) == NULL) {
        (*p) = (t_list *)malloc(sizeof(t_list));
        (*p)->command = mx_jobDup(multiColumn);
        // printf("dubbed command = %s\n", (*p)->command);
        (*p)->next = NULL;
    }
    else {
        for (; (*p)->next; p = &(*p)->next);
        (*p)->next = (t_list *)malloc(sizeof(t_list));
        (*p)->next->command = mx_jobDup(multiColumn);
        // printf("dubbed command = %s\n", (*p)->next->command);
        (*p)->next->next = NULL;
    }
}

t_list *mx_jobSplit(char *line) {
    t_list *jobs = NULL;
    char **multiColumn = mx_customSplit(line, ';');

    if (multiColumn) {
        for (int i = 0; multiColumn[i]; i++) {
            pushBack(&jobs, multiColumn[i]);
        }
        mx_del_strarr(&multiColumn);
    }
    return jobs;
}
