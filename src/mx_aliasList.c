#include "header.h"


static t_alias *createNode(char *command) {
    t_alias *p = NULL;
    int start = 0;

    p = (t_alias *)malloc(sizeof(t_alias) * 1);
    for (; command[start - 1] != ' '; start++);
    (*p).name = mx_nameCut(command, &start);
    start +=1;
    (*p).meaning = mx_nameCut(command, &(start));
    (*p).next = NULL;
    return p;
}

static void changeNode(char *command, int start, t_alias *alia, char **name) {
    t_alias *p = alia;
    char *meaning = mx_nameCut(command, &start);

    mx_strdel(name);
    mx_strdel(&p->meaning);
    p->meaning = meaning;
}

static bool exCheck(t_alias **aliasList, char *command) {
    t_alias *p = (*aliasList);
    int start = 0;
    char *name = NULL;

    for (; command[start - 1] != ' '; start++);
    name = mx_nameCut(command, &start);
    if (mx_strcmp(p->name, (unsigned char *)name) == 0) {
        changeNode(command, start + 1, p, &name);
        return true;
    }
    for (; p->next; p = p->next) {
        if (mx_strcmp(p->name, (unsigned char *)name) == 0) {
            changeNode(command, start + 1, p, &name);
            return true;
        }
    }
    mx_strdel(&name);
    return false;
}

void mx_aliasList(char *command, t_alias **aliasList) {
    t_alias *p = (*aliasList);

    if (p == NULL) {
        *aliasList = createNode(command);
    }
    else {
        if (exCheck(aliasList, command) == false) {
            for(; p->next; p = p->next);
            p->next = createNode(command);
        }
    }
}
