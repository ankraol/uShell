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
    t_path **output = NULL;
    t_path **input = NULL;
    int i = s;
    int q = 0;
    int j = 0;

    tasks->task = (char *)malloc(sizeof(char) * (f - s));
    // tasks->path = (t_path *)malloc(sizeof(t_path));
    // tasks->path->next = NULL;
    tasks->input = NULL;
    tasks->output = NULL;
    input = &tasks->input;
    output = &tasks->output;
        for (; command[i] != '>' && command[i] != '<' && i < f; i++, q++) {
            tasks->task[q] = command[i];
        }
        tasks->task[q] = '\0';
        tasks->task = realloc(tasks->task, strlen(tasks->task));
        for (; i < f; i++) {
            if (command[i] == '>'&& i < f) {
                if (!(*output)) {
                    *output = create_list(command, &i, f, s);
                }
                else {
                    for(; (*output)->next; output = &(*output)->next);
                    (*output)->next = (t_path *)malloc(sizeof(t_path));
                    (*output)->next->op = command[i];
                    i += 2;
                    (*output)->next->file = (char *)malloc(sizeof(char) * (f - s));
                    for (j = 0; i < f && command[i + 1] != '<' && command[i + 1] != '>'; i++, j++) {
                        (*output)->next->file[j] = command[i];
                    }
                    (*output)->next->file[j] = '\0';
                    (*output)->next->file = realloc((*output)->next->file, strlen((*output)->next->file));
                    (*output)->next->next = NULL;
                }
            }
            if (command[i] == '<' && i < f) {
                if (!(*input)) {
                    *input = create_list(command, &i, f, s);
                }
                else {
                    for(; (*input)->next; input = &(*input)->next);
                    (*input)->next = (t_path *)malloc(sizeof(t_path));
                    (*input)->next->op = command[i];
                    i += 2;
                    (*input)->next->file = (char *)malloc(sizeof(char) * (f - s));
                    for (j = 0; i < f && command[i + 1] != '<' && command[i + 1] != '>'; i++, j++) {
                        (*input)->next->file[j] = command[i];
                    }
                    (*input)->next->file[j] = '\0';
                    (*input)->next->file = realloc((*input)->next->file, strlen((*input)->next->file));
                    (*input)->next->next = NULL;
                }
            }
        }
}
