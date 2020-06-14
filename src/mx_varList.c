#include "header.h"

static char *nameCut(char *com, int *start) {
    char *name = (char *)malloc(sizeof(char) * strlen(com));
    int i = 0;
    bool iSq = false;

    for ( ; com[(*start)] != '=' && com[(*start)] != '\0'; (*start)++) {
        if (com[(*start)] == 34 && iSq == false)
                iSq = true;
        else if (com[(*start)] == ' ' && iSq == false)
            break;
        else if (com[(*start)] == 34 && iSq == true)
            break;
        else {
            name[i] = com[(*start)];
            i++;
        }
    }
    name[i] = '\0';
    name = realloc(name, strlen(name) + 1);
    return name;
}

static t_var *createNode(char *command) {
    t_var *p = NULL;
    int start = 0;

    p = (t_var *)malloc(sizeof(t_var) * 1);
    (*p).name = nameCut(command, &start);
    start +=1;
    (*p).meaning = nameCut(command, &(start));
    (*p).inEnv = false;
    (*p).next = NULL;
    return p;
}

static void changeNode(char *command, int start, t_var *var) {
    t_var *p = var;
    char *meaning = nameCut(command, &start);

    mx_strdel(&p->meaning);
    p->meaning = meaning;
}

static void fill_List(char *command, t_var *p, bool *change, int *start) {
    char *name = nameCut(command, start);

    if (mx_strcmp(p->name, (unsigned char *)name) == 0)
        (*change) = true;
    if ((*change) == false) {
        for(; p->next; p = p->next) {
            if (mx_strcmp(p->name, (unsigned char *)name) == 0) {
                (*change) = true;
                break;
            }
        }
    }
}

void mx_varList(char *command, t_var **varList) {
    t_var *p = (*varList);
    int start = 0;
    bool change = false;

    if (p == NULL)
        *varList = createNode(command);
    else {
        fill_List(command, p, &change, &start);
        if (change == false)
            p->next = createNode(command);
        else
            changeNode(command, start + 1, p);
    }
}
