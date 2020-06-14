#include "header.h"

static bool isSame(char **noTilda, char **path, char *tilda) {
    int i = 0;

    for (; path[i + 1]; i++);
    if (mx_strcmp(path[i], (unsigned const char *)noTilda[0]) == 0) {
        if (tilda[1] == '/')
            return false;
        return true;
    }
    return false;
}

static char *joinParts(char *first, char *second) {
    char *addspace = NULL;
    char *newLine = NULL;

    if (first)
        addspace = mx_strjoin(first, "/");
    newLine = mx_strjoin(addspace, second);
    if (first) {
        mx_strdel(&first);
        mx_strdel(&addspace);
    }
    return newLine;
}

static char *omitSame(char **noTilda, char **path, char *meaning) {
    int i = 1;
    char *newLine = mx_strdup(meaning);

    for (; noTilda[i]; i++)
        newLine = joinParts(newLine, noTilda[i]);
    mx_strdel(&meaning);
    mx_del_strarr(&noTilda);
    mx_del_strarr(&path);
    return newLine;
}

char *mx_checkSame(char *meaning, char *tilda) {
    char **noTilda = mx_strsplit((tilda + 1), '/');
    char **path = mx_strsplit(meaning, '/');
    char *newLine = NULL;

    if (!isSame(noTilda, path, tilda)) {
        newLine = mx_strjoin(meaning, (tilda + 1));
        mx_strdel(&meaning);
        mx_del_strarr(&noTilda);
        mx_del_strarr(&path);
    }
    else
        newLine = omitSame(noTilda, path, meaning);
    return newLine;
}
