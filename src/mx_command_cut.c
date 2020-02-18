#include "header.h"

t_path *create_list(char *command, int *i, int f, int s) {
    t_path *p = NULL;
    int j = 0;

    p = (t_path *)malloc(sizeof(t_path));
    p->op = command[(*i)];
    (*i) += 2;
    p->file = (char *)malloc(sizeof(char) * (f - s));
    for (; (*i) < f && command[(*i) + 1] != '<' && command[(*i) + 1] != '>'; (*i)++, j++) {
        p->file[j] = command[(*i)];
    }
    p->file[j] = '\0';
    p->file = realloc(p->file, strlen(p->file));
    p->next = NULL;
    return p;
}

void mx_command_cut(char *command, int s, int f, t_reddir *tasks) {
    t_path **p = NULL;
    int i = s;
    int q = 0;
    int j = 0;

    tasks->task = (char *)malloc(sizeof(char) * (f - s));
    tasks->path = (t_path *)malloc(sizeof(t_path));
    tasks->path->next = NULL;
    p = &tasks->path->next;
        for (; command[i] != '>' && command[i] != '<' && i < f; i++, q++) {
            tasks->task[q] = command[i];
        }
        tasks->task[q] = '\0';
        tasks->task = realloc(tasks->task, strlen(tasks->task));
        for (; i < f; i++) {
            if ((command[i] == '>' || command[i] == '<') && i < f) {
                if (!(*p)) {
                    *p = create_list(command, &i, f, s);
                    // (*p) = (t_path *)malloc(sizeof(t_path));
                    // (*p)->op = command[i];
                    // i += 2;
                    // (*p)->file = (char *)malloc(sizeof(char) * (f - s));
                    // for (j = 0; i < f && command[i + 1] != '<' && command[i + 1] != '>'; i++, j++) {
                    //     (*p)->file[j] = command[i];
                    // }
                    // (*p)->file[j] = '\0';
                    // (*p)->file = realloc((*p)->file, strlen((*p)->file));
                    // (*p)->next = NULL;
                }
                else {
                    for(; (*p)->next; p = &(*p)->next);
                    (*p)->next = (t_path *)malloc(sizeof(t_path));
                    (*p)->next->op = command[i];
                    i += 2;
                    (*p)->next->file = (char *)malloc(sizeof(char) * (f - s));
                    for (j = 0; i < f && command[i + 1] != '<' && command[i + 1] != '>'; i++, j++) {
                        (*p)->next->file[j] = command[i];
                    }
                    (*p)->next->file[j] = '\0';
                    (*p)->next->file = realloc((*p)->next->file, strlen((*p)->next->file));
                    (*p)->next->next = NULL;
                }
            }
        }
}
