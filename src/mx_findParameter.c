#include "header.h"

static char *varSearch(char *parameter, t_var *varList) {
    t_var *p = varList;
    char *varMeaning = NULL;

    for (; p; p = p->next) {
        if (mx_strcmp(parameter, (unsigned char *)p->name) == 0) {
            varMeaning = mx_strdup(p->meaning);
            return varMeaning;
        }
    }
    return NULL;
}

static char *parExp(char *parameter) {
    int i = 0;
    char **nameMeaning = NULL;
    char *meaning = NULL;

    for(; environ[i]; i++) {
        nameMeaning = mx_strsplit(environ[i], '=');
        if (mx_strcmp(parameter, (const unsigned char *)nameMeaning[0]) == 0)
            meaning = mx_strdup(nameMeaning[1]);
        mx_del_strarr(&nameMeaning);
    }
    return meaning;
}

char *mx_findParameter(char *parameter, t_var *varList, int status) {
    char *expansion = parExp(parameter);

    printf("PARAMETER = %s\n", parameter);

    if (parameter[0] == '?')
        expansion = mx_itoa(status);
    if (!expansion)
        expansion = varSearch(parameter, varList);
    printf("EXPANSION = %s\n", expansion);
    return expansion;
}
