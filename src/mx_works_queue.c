#include "header.h"

static bool extraCommand(char *line, int i) {
    for (int j = i + 1; line[j] != '\0'; j++) {
        if (line[j] != ' ')
            return false;
    }
    return true;
}

static void muteChar(bool *sQ, bool *dQ, bool *a, char *l, int i) {
    if (l[i] == 96 && l[i - 1] != 92 && (*sQ) == false && (*dQ) == false) {
        if ((*a) == false)
            *a = true;
        else
            *a = false;
    }
    else if (l[i] == 34 && l[i - 1] != 92 && (*a) == false && (*sQ) == false) {
        if ((*dQ) == false)
            *dQ = true;
        else
            *dQ = false;
    }
    else if (l[i] == 39 && (*a) == false && (*dQ) == false) {
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
        if (line[i] == ';' && !sQ && !dQ && !iSs) {
            if(extraCommand(line, i) == false && line[i + 1] != '\0')
                count += 1;
        }
    }
    return count;
}

void jobs_delete(t_list **jobs) {
    t_list *p1 = NULL;

    while ((*jobs)) {
        p1 = (*jobs)->next;
        mx_strdel(&((*jobs)->command));
        free(*jobs);
        *jobs = p1;
    }
}

t_queue **mx_works_queue(char *line) {
    int size = worksCount(line);
    t_list *jobs = mx_jobSplit(line);
    t_queue **list = NULL;
    int i = 0;
    t_list *p = jobs;

    if (p) {
        list = (t_queue **)malloc(sizeof(t_queue *) * (size + 1));
        for (; i < size && p; i++) {
            list[i] = NULL;
            mx_logicOp(p->command, &list[i]);
            p = (*p).next;
        }
        list[size] = NULL;
        jobs_delete(&jobs);
    }
    return list;
}
