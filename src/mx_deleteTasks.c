#include "header.h"

static void deletePath(t_path **path) {
    t_path *p1 = *path;
    t_path *p2 = *path;

    for (; p1->next; p1 = p1->next);
    while (p1 != *path) {
        for (; p2->next != p1; p2 = p2->next);
        mx_strdel(&p1->file);
        free(p1);
        p1 = p2;
        p2 = *path;
    }
    mx_strdel(&(*path)->file);
    free(*path);
    *path = NULL;
}

void mx_deleteTasks(t_reddir ***tasks) {
    int i = 0;

    for ( ; (*tasks)[i]; i++) {
        mx_strdel(&(*tasks)[i]->task);
        if ((*tasks)[i]->output)
            deletePath(&(*tasks)[i]->output);
        if ((*tasks)[i]->input)
            deletePath(&(*tasks)[i]->input);
        free((*tasks)[i]);
        (*tasks)[i] = NULL;
    }
    free(*tasks);
    *tasks = NULL;
}
