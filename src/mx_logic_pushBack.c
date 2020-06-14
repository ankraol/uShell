#include "header.h"

static char *commandCut(char *line, int start, int end) {
    char *command = (char *)malloc(sizeof(char) * (end - start + 2));
    int i = start;
    int j = 0;

    for (; i < end && line[i] != '\0'; i++) {
        command[j] = line[i];
        j++;
    }
    command[j] = '\0';

    command = realloc(command, strlen(command));
    return command;
}

static t_queue *createList(char *line, int start, int end) {
    t_queue *list = (t_queue *)malloc(sizeof(t_queue));

    (*list).command = commandCut(line, start, end);
    if (line[end] != '\0')
        (*list).op = line[end + 1];
    else
        (*list).op = '-';
    (*list).next = NULL;
    return list;
}

void mx_logic_pushBack(t_queue **list, char *line, int start, int end) {
    t_queue *p = createList(line, start, end);
    t_queue *buf = *list;

     if ((*list) == NULL)
        *list = p;
    else {
        for (; buf->next; buf = buf->next);
        buf->next = p;
    }
}
