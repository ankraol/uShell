#include "header.h"

static bool doubleQuotes(char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == 34)
            return true;
    }
    return false;
}

static char *deleteQuotes(char *line) {
    char *newLine = (char *)malloc(sizeof(char *) * (strlen(line) - 1));
    int i = 1;
    int j = 0;

    for (; line[i + 1] != '\0'; i++) {
        newLine[j] = line[i];
        j++;
    }
    newLine[j] = '\0';
    return newLine;
}

static char *returnQuotes(char *quoteLess) {
    char *newLine = (char *)malloc(sizeof(char) * (strlen(quoteLess) + 3));
    int i = 0;
    int j = 0;

    newLine[i] = 34;
    for (i = 1; quoteLess[j] != '\0'; j++) {
        newLine[i] = quoteLess[j];
        i++;
    }
    newLine[i] = 34;
    newLine[i + 1] = '\0';
    mx_strdel(&quoteLess);
    return newLine;
}

char *mx_expandLine(char *parameterLine, t_var *varList, int status) {
    char *expand = NULL;
    char *quoteLess = NULL;

    if (doubleQuotes(parameterLine)) {
        quoteLess = deleteQuotes(parameterLine);
        expand = mx_extractExpand(quoteLess, varList, status);
        expand = returnQuotes(expand);
    }
    else {
        quoteLess = mx_strdup(parameterLine);
        expand = mx_extractExpand(quoteLess, varList, status);
    }
    mx_strdel(&quoteLess);
    return expand;
}
