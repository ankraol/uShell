#include "header.h"

static bool isTilda(char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '~' && line[i - 1] != 92)
            return true;
    }
    return false;
}

static bool isExp(char *line) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '$' && (line[i + 1] == '{' || line[i + 1] != '(')
            && line[i - 1] != 92)
            {
            return true;
            }
    }
    return false;
}

char *mx_expandParameter(char *line, t_var *varList, int status) {
    char *newLine = NULL;
    char *tilda = NULL;

    if (isExp(line) == true) {
        newLine = mx_expandedLine(line, varList, status);
        mx_strdel(&line);
    }
    else {
        newLine = mx_strdup(line);
        mx_strdel(&line);
    }
    if (isTilda(newLine) == true) {
        tilda = mx_findTilda(newLine, varList, status);
        mx_strdel(&newLine);
        return tilda;
    }
    return newLine;
}
