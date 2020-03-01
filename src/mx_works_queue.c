#include "header.h"

static void muteChar(bool *sQ, bool *dQ, bool *iSs, char *line, int i) {
    if (line[i] == 96 && line[i - 1] != 92 && (*sQ) == false && (*dQ) == false) {
        if ((*iSs) == false)
            *iSs = true;
        else
            *iSs = false;
    }
    else if (line[i] == 34 && line[i - 1] != 92 && (*iSs) == false && (*sQ) == false) {
        if ((*dQ) == false)
            *dQ = true;
        else
            *dQ = false;
    }
    else if (line[i] == 39 && (*iSs) == false && (*dQ) == false) {
        if ((*sQ) == false)
            *sQ = true;
        else
            *sQ = false;
    }
}

static int worksCount(char *line) {
    int count = 1;
    bool sQ = false;
    bool dQ = false;
    bool iSs = false;

    for (int i = 0; line[i] != '\0'; i++) {
        muteChar(&sQ, &dQ, &iSs, line, i);
        if (line[i] == ';' && sQ == false && dQ == false && iSs == false)
            count += 1;
    }
    return count;
}

static bool onlySpaces(char *line, int st, int end) {
    for (int i = st; i < end; i++) {
        if (line[i] != ' ')
            return false;
    }
    return true;
}

static char *commandCut(char *line, int start, int end) {
    char *command = (char *)malloc(sizeof(char) * (end - start + 2));
    int q = 0;

    for (int i = start; i < end; i++) {
        if (i == start && line[i] == ' ')
            for (; line[i] == ' '; i++);
        if (onlySpaces(line, i, end) == false) {
            command[q] = line[i];
            q++;
        }
    }
    command[q] = '\0';
    command = realloc(command, strlen(command));
    return command;
}

static void pushBack(t_list **jobs, char *line, int start, int end) {
    t_list **p = jobs;

    if ((*jobs) == NULL) {
        (*p) = (t_list *)malloc(sizeof(t_list));
        (*p)->command = commandCut(line, start, end);
        (*p)->next = NULL;
    }
    else {
        for (; (*p)->next; *p = (*p)->next);
        (*p)->next = (t_list *)malloc(sizeof(t_list));
        (*p)->next->command = commandCut(line, start, end);
        (*p)->next->next = NULL;
    }
}

static t_list *jobsSplit(char *line) {
    t_list *jobs = NULL;
    bool sQ = false;
    bool dQ = false;
    bool iSs = false;
    int start = 0;
    int i = 0;

    for (; line[i] != '\0'; i++) {
        muteChar(&sQ, &dQ, &iSs, line, i);
        if (sQ == false && dQ == false && iSs == false && line[i] == ';') {
            // printf("PART ONE\n");
            pushBack(&jobs, line, start, i);
            start = i + 1;
        }
    }
    // printf("PART TWO\n");
    pushBack(&jobs, line, start, i);
    return jobs;
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
    // char **jobs = mx_strsplit(line, ';');
    t_list *jobs = jobsSplit(line);
    t_queue **list = (t_queue **)malloc(sizeof(t_queue *) * (size + 1));
    int i = 0;

    for (t_list *p = jobs; p && i < size; p = (*p).next, i++) {
        list[i] = NULL;
        // printf("jobSplit => %s\n", (*p).command);
        mx_logicOp((*p).command, &list[i]);
    }
    list[size] = NULL;

    // for (int i = 0; i < size; i++) {
        // list[i] = NULL;
        // mx_logicOp(jobs[i], &list[i]);
    // }
    // list[size] = NULL;
    return list;
}
