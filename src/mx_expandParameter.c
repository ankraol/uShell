#include "header.h"

static bool removal(char *str, int i) {
    int count = 0;

    for (int j = i; str[j] == 92; j--)
        count++;
    if (count % 2 == 0)
        return false;
    return true;
}

static bool isExp(char *line, char symb) {
    bool sQ = false;

    for (int i = 0; line && line[i] != '\0';) {
        if (line[i] == 39) {
            if (sQ)
                sQ = false;
            else
                sQ = true;
            i++;
        }
        else if (line[i + 1] != '\0' && line[i] == symb && (line[i + 1] == '{' || line[i + 1] != '(')
                && !sQ && i != 0)
            {
                if (line[i - 1] != 92)
                    return true;
                else {
                    if (!removal(line, i - 1))
                        return true;
                    mx_removeSlash(&line, symb);
                    return false;
                }
            }
        else
            i++;
    }
    return false;
}

// static bool doubleQoutes(char *line) {
    // for (int i = 0; line[i] != '\0'; i++) {
        // if (line[i] == 34)
            // return true;
    // }
    // return false;
// }

char *mx_expandParameter(char *line, t_var *varList, int status) {
    char *newLine = NULL;
    char *tilda = NULL;
    printf("WHAT WE  HAVE HERE - %s\n", line);

    if (isExp(line, '$') == true) {
        printf("LINE = %s\n", line);
        // if (doubleQoutes(line)) {
        newLine = mx_insideQuotes(line, varList, status);
        // mx_strdel(&line);
        if (isExp(newLine, '$') == true) {
            newLine = mx_expandParameter(newLine, varList, status);
            // mx_strdel(&line);
        }
            // printf("AFTER QOUTES = %s\n", newLine);
        // }
        // else
            // newLine = mx_expandedLine(line, varList, status);
        // mx_strdel(&line);
    }
    else {
        newLine = mx_strdup(line);
        mx_strdel(&line);
    }
    if (isExp(newLine, '~') == true) {
        tilda = mx_findTilda(newLine, varList, status);
        mx_strdel(&newLine);
        return tilda;
    }
    printf("NEW LINE AFTER PARAMETER EXPANSION = %s\n", newLine);
    return newLine;
}
