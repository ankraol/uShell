#include "header.h"

static bool onlySlash(char *first) {
    int i = mx_strlen(first) - 1;

    if (first[i] == 92)
        return true;
    return false;
}

static char *joinParts(char *first, char *second) {
    char *addspace = NULL;
    char *newLine = NULL;

    if (first) {
        if (onlySlash(first)) {
            newLine = mx_strjoin(first, second);
            mx_strdel(&first);
            return newLine;
        }
        addspace = mx_strjoin(first, " ");
    }
    newLine = mx_strjoin(addspace, second);
    if (first) {
        mx_strdel(&first);
        mx_strdel(&addspace);
    }
    return newLine;
}

static char *commandDup(char *command) {
    char **arr = mx_strsplit(command, ' ');
    char *newCommand = NULL;

    for (int i = 0; arr[i]; i++) {
        newCommand = joinParts(newCommand, arr[i]);
    }
    mx_del_strarr(&arr);
    return newCommand;
}

char *mx_expandedLine(char *line, t_var *varList, int status) {
    char **dollarSplit = mx_strsplit(line, '$');
    char *newLine = NULL;
    char *parameter = NULL;
    int i = 0;

    if (line[0] != '$') {
        i = 1;
        newLine = commandDup(dollarSplit[0]);
    }
    for(; dollarSplit[i]; i++) {
        parameter = mx_expand_parts(dollarSplit[i], varList, status);
        if (parameter) {
            newLine = joinParts(newLine, parameter);
            mx_strdel(&parameter);
        }
    }
    mx_del_strarr(&dollarSplit);
    return newLine;
}
