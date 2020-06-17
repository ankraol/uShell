#include "header.h"

static char *joinParts(char *first, char *second) {
    char *addspace = NULL;
    char *newLine = NULL;

    if (first)
        addspace = mx_strjoin(first, " ");
    newLine = mx_strjoin(addspace, second);
    if (first) {
        mx_strdel(&first);
        mx_strdel(&addspace);
    }
    return newLine;
}

static char *tildaMeaning(char *tilda, t_var *varList, int status) {
    char *meaning = NULL;

    if (tilda[1] == '+')
        meaning = mx_findParameter("PWD", varList, status);
    else if (tilda[1] == '-')
        meaning = mx_findParameter("OLDPWD", varList, status);
    else if (tilda[0] == '~') {
        meaning = mx_findParameter("HOME", varList, status);
        if (tilda[1] != '\0')
            meaning = mx_checkSame(meaning, tilda);
    }
    return meaning;
}

char *mx_findTilda(char *line, t_var *varList, int status) {
    char **arr = mx_strsplit(line, ' ');
    char *part = NULL;
    char *newLine = NULL;

    for (int i = 0; arr[i]; i++) {
        part = tildaMeaning(arr[i], varList, status);
        if (!part)
            newLine = joinParts(newLine, arr[i]);
        else {
            newLine = joinParts(newLine, part);
            mx_strdel(&part);
        }
    }
    mx_del_strarr(&arr);
    return newLine;
}
