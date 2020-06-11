#include "header.h"

static void isQuote(bool *dQ, bool *sQ, bool *ap, char *line, int i) {
    if (line[i] == 96 && line[i - 1] != 92 && (*sQ) == false && (*dQ) == false) {
        if ((*ap) == false)
            *ap = true;
        else
            *ap = false;
    }
    else if (((line[i] == 34 && line[i - 1] != 92)
    || (i == 0 && line[i] == 34)) && (*sQ) == false) {
        if ((*dQ) == false)
            *dQ = true;
        else
            *dQ = false;
    }
    else if (line[i] == 39 && (*dQ) == false) {
        if ((*sQ) == false)
            *sQ = true;
        else
            *sQ = false;
    }
}

static bool extraSpaces(char *line) {
    bool dQ = false;
    bool sQ = false;
    bool ap = false;

    for (int i = 0; line[i] != '\0'; i++) {
        isQuote(&dQ, &sQ, &ap, line, i);
        if (dQ == false && sQ == false && ap == false) {
            if (line[i] == ' ' && line[i + 1] == ' ')
                return true;
        }
    }
    return false;
}

static bool onlySpaces (char *line, int i) {
    for(; line[i] != '\0'; i++) {
        if (line[i] != ' ')
            return false;
    }
    return true;
}

static char *deleteExtraSpaces(char *line) {
    char *newLine = (char *)malloc(sizeof(char) * strlen(line) + 1);
    bool dQ = false;
    bool sQ = false;
    bool ap = false;
    int j = 0;

    for (int i = 0; line[i] != '\0'; i++, j++) {
        isQuote(&dQ, &sQ, &ap, line, i);
            if (dQ == false && sQ == false && ap == false) {
                if (line[i] == ' ') {
                    if (onlySpaces(line, i) == true)
                        break;
                    else
                        for(; line[i + 1] == ' '; i++);
                }
            }
            newLine[j] = line[i];
    }
    newLine[j] = '\0';
    newLine = realloc(newLine, strlen(newLine) + 1);
    //printf("NEW LINE = %s\n", newLine);
    return newLine;
}

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
    // printf("COMMAND CUT --> %s\n", command);
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

static void pushBack(t_queue **list, char *line, int start, int end) {
    t_queue *p = createList(line, start, end);
    t_queue *buf = *list;

     if ((*list) == NULL)
        *list = p;
    else {
        for (; buf->next; buf = buf->next);
        buf->next = p;
    }

    

    // if ((*list) == NULL) {
    //     p = createList(line, start, end);
    // }
    // else
    // {
    //     for (; p->next; p = p->next);
    //     p->next = createList(line, start, end);
    // }
    
}

void mx_logicOp(char *line, t_queue **list) {
    //printf("\tFIRST PARSING ===> %s\n", line);
    char *newLine = NULL;
    bool sQ = false;
    bool dQ = false;
    bool ap = false;
    int start = 0;
    int i = 0;

    if (extraSpaces(line) == true) {
        newLine = deleteExtraSpaces(line);
        //mx_strdel(&line);
    }
    else {
        newLine = mx_strdup(line);
        //mx_strdel(&line);
    }
    // printf("LINE IN LOGICOP = %s\n", newLine);
    for (; newLine[i] != '\0'; i++) {
        if (newLine[i] == 34 || newLine[i] == 39 || newLine[i] == 96)
            isQuote(&dQ, &sQ, &ap, newLine, i);
        if (dQ == false && sQ == false && ap == false && ((newLine[i] == '&' && newLine[i + 1] == '&')
            || (newLine[i] == '|' && newLine[i + 1] == '|')))
            {
                pushBack(list, newLine, start, i - 1);
                for (;(newLine[i] == ' ' || newLine[i] == '&' || newLine[i] == '|')
                    && newLine[i] != '\0'; i++);
                start = i;
            }
    }
    //printf("NEWLINE = %s\n", newLine);
    pushBack(list, newLine, start, i);
    // t_queue *n = *list;
    // while (n) {
    //     printf("LIST IN OP -----  %s\n", n->command);
    //     n = n->next;
    // }
    mx_strdel(&newLine);
}

