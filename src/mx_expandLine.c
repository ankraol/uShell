#include "header.h"

static bool doubleQuotes(char *line, t_muteChar *mute) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == 34) {
            (*mute).dQ = true;
            return true;
        }
        else if (line[i] == 96) {
            (*mute).sQ = true;
            return true;
        }
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

static char *returnQuotes(char *quoteLess, t_muteChar mute) {
    char *newLine = (char *)malloc(sizeof(char) * (strlen(quoteLess) + 3));
    int i = 0;
    int j = 0;

    if (mute.sQ)
        newLine[i] = 96;
    else if (mute.dQ)
        newLine[i] = 34;
    for (i = 1; quoteLess[j] != '\0'; j++) {
        newLine[i] = quoteLess[j];
        i++;
    }
    if (mute.sQ)
        newLine[i] = 96;
    else if (mute.dQ)
        newLine[i] = 34;
    newLine[i + 1] = '\0';
    mx_strdel(&quoteLess);
    return newLine;
}

char *mx_expandLine(char *parameterLine, t_var *varList, int status) {
    char *expand = NULL;
    char *quoteLess = NULL;
    t_muteChar mute;

    memset(&mute, 0, sizeof(t_muteChar));
    if (doubleQuotes(parameterLine, &mute)) {
        quoteLess = deleteQuotes(parameterLine);
        expand = mx_extractExpand(quoteLess, varList, status);
        if (expand)
            expand = returnQuotes(expand, mute);
    }
    else {
        quoteLess = mx_strdup(parameterLine);
        expand = mx_extractExpand(quoteLess, varList, status);
    }
    mx_strdel(&quoteLess);
    return expand;
}
