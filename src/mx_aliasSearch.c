#include "header.h"

static char *aliasSub(char *command, char *task, char *sub) {
    char *newCommand = (char *)malloc(sizeof(char) * strlen(command) + strlen(sub));
    int start = strlen(task);
    int i = 0;

    for (; sub[i] != '\0'; i++) {
        newCommand[i] = sub[i];
    }
    for (; command[start] != '\0'; start++) {
        newCommand[i] = command[start];
        i++;
    }
    newCommand[i] = '\0';
    newCommand = realloc(newCommand, strlen(newCommand) + 1);
    return newCommand;
}

static bool aliasCheck(char *task, t_alias *list) {
    t_alias *p = list;

    for(; p; p = p->next) {
        if (mx_strcmp(task, (unsigned char *)p->name) == 0)
            return true;
    }
    return false;
}

static char *taskCut(char *command) {
    char *task = (char *)malloc(sizeof(char) * strlen(command) + 1);
    int i = 0;

    for (; command[i] != '\0'; i++) {
        if (command[i] == ' ' && command[i + 1] != '-')
            break;
        task[i] = command[i];
    }
    task[i] = '\0';
    task = realloc(task, strlen(task) + 1);
    return task;
}

char *mx_aliasSearch(char *command, t_alias *list) {
    t_alias *p = list;
    char *task = taskCut(command);
    char *newCommand = command;

    if (aliasCheck(task, list) == true) {
        for (; p; p = p->next) {
            if (strcmp(task, p->name) == 0)
                newCommand = aliasSub(command, task, p->meaning);
        }
    }
    mx_strdel(&task);
    return newCommand;
}



