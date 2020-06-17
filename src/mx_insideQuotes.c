#include "header.h"

static bool isExp(char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == 36)
            return true;
    }
    return false;
}

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

char *mx_insideQuotes(char *line, t_var *varList, int status) {
    char **spaceSplited = mx_customSplit(line, ' ');
    char *expand = NULL;
    char *newLine = NULL;
    int i = 0;

    for (; spaceSplited[i]; i++) {
        if (isExp(spaceSplited[i])) {
            expand = mx_expandLine(spaceSplited[i], varList, status);
            if (expand)
                newLine = joinParts(newLine, expand);
            mx_strdel(&expand);
        }
        else
            newLine = joinParts(newLine, spaceSplited[i]);
    }
    mx_del_strarr(&spaceSplited);
    mx_strdel(&line);
    return newLine;
}
