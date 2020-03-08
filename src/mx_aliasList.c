#include "header.h"

static char *nameCut(char *command, int *start) {
    char *name = (char *)malloc(sizeof(char) * strlen(command));
    int i = 0;
    bool iSq = false;

    for ( ; command[(*start)] != '='
        && command[(*start)] != '\0'; (*start)++)
        {
            if (command[(*start)] == 34 && iSq == false)
                    iSq = true;
            else if ((command[(*start)] == ' ' && iSq == false)
                || (command[(*start)] == 34 && iSq == true))
                {
                    break;
                }
            else {
                name[i] = command[(*start)];
                i++;
            }
        }
        name[i] = '\0';
        name = realloc(name, strlen(name) + 1);
        return name;
}

static t_alias *createNode(char *command) {
    t_alias *p = NULL;
    int start = 0;

    p = (t_alias *)malloc(sizeof(t_alias) * 1);
    for (; command[start - 1] != ' '; start++);
    (*p).name = nameCut(command, &start);
    start +=1;
    (*p).meaning = nameCut(command, &(start));
    (*p).next = NULL;
    return p;
}

static void changeNode(char *command, int start, t_alias *alia) {
    t_alias *p = alia;
    char *meaning = nameCut(command, &start);

    mx_strdel(&p->meaning);
    p->meaning = meaning;
}

void mx_aliasList(char *command, t_alias **aliasList) {
    t_alias *p = (*aliasList);
    int start = 0;
    char *name = NULL;

    if (p == NULL) {
        *aliasList = createNode(command);
    }
    else {
        for (; command[start - 1] != ' '; start++);
        name = nameCut(command, &start);
        for(; p->next; p = p->next) {
            if (mx_strcmp(p->name, (unsigned char *)name) == 0)
                break;
        }
        if (!p->next)
            p->next = createNode(command);
        else
            changeNode(command, start + 1, p);
    }
}
