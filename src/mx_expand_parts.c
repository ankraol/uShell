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

static char *deleteBrackets(char *line) {
    char *newLine = (char *)malloc(sizeof(char *) * (strlen(line) - 1));
    int i = 1;
    int j = 0;

    for (; line[i + 1] != '\0'; i++) {
        newLine[j] = line[i];
        j++;
    }
    newLine[j + 1] = '\0';
    return newLine;
}

static char *joinExpansion(char **part, char *expansion) {
    char *newLine = mx_strdup(expansion);

    for (int i = 1; part[i]; i++) {
        newLine = joinParts(newLine, part[i]);
    }
    mx_strdel(&expansion);
    mx_del_strarr(&part);
    return newLine;
}

char *mx_expand_parts(char *dollarSplit, t_var *varList, int status) {
    char **parameter = mx_strsplit(dollarSplit, ' ');
    char *bracketless = NULL;
    char *expansion = NULL;
    char *newLine = NULL;

    if (parameter[0][0] == '{') {
        bracketless = deleteBrackets(parameter[0]);
        expansion = mx_findParameter(bracketless, varList, status);
        mx_strdel(&bracketless);
    }
    else
        expansion = mx_findParameter(parameter[0], varList, status);
    newLine = joinExpansion(parameter, expansion);
    return newLine;
}
