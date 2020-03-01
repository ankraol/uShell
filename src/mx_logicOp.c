#include "header.h"

static void isQuote(bool *dQ, bool *sQ, char *line, int i) {
        if (((line[i] == 34 && line[i - 1] != 92)
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

    for (int i = 0; line[i] != '\0'; i++) {
        isQuote(&dQ, &sQ, line, i);
        if (dQ == false && sQ == false) {
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
    int j = 0;

    for (int i = 0; line[i] != '\0'; i++, j++) {
        isQuote(&dQ, &sQ, line, i);
            if (dQ == false && sQ == false) {
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
    t_queue **p = list;

    if ((*list) == NULL) {
        *p = createList(line, start, end);
    }
    else
    {
        for (; (*p)->next; p = &(*p)->next);
        (*p)->next = createList(line, start, end);
    }
    
}

void mx_logicOp(char *line, t_queue **list) {
    char *newLine = NULL;
    bool sQ = false;
    bool dQ = false;
    int start = 0;
    int i = 0;

    if (extraSpaces(line) == true) {
        newLine = deleteExtraSpaces(line);
    }
    else
        newLine = line;

    for (; newLine[i] != '\0'; i++) {
        if (newLine[i] == 34 || newLine[i] == 39)
            isQuote(&dQ, &sQ, newLine, i);
        if (dQ == false && sQ == false && ((newLine[i] == '&' && newLine[i + 1] == '&')
            || (newLine[i] == '|' && newLine[i + 1] == '|')))
            {
                pushBack(list, newLine, start, i - 1);
                for (;(newLine[i] == ' ' || newLine[i] == '&' || newLine[i] == '|')
                    && newLine[i] != '\0'; i++);
                start = i;
            }
    }
    pushBack(list, newLine, start, i);
}

