#include "header.h"

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

char *mx_expandParameter(char *line, t_var *varList) {
    char *newLine = NULL;

    if (isExp(line) == true) {
        newLine = mx_expandedLine(line, varList);
        mx_strdel(&line);
    }
    else {
        newLine = mx_strdup(line);
        mx_strdel(&line);
    }
    return newLine;
}
