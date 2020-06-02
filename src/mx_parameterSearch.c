#include "header.h"

static bool iStilda(char *command) {
    for (int i = 0; command[i] != '\0'; i++)
        if (command[i] == 126 && command[i - 1] != 92)
            return true;
    return false;
}

static bool noReturn(char *command, char *replace) {
    int i = 2;
    int j = 0;

    for(; replace[i - 1] != '/'; i++);
    for(; command[j - 1] != '~'; j++);
    if (command[j] == '\0')
        return true;
    for (; replace[i] != '\0' && command[j] != '\0'; j++, i++) {
        if (command[j] != replace[i])
            return true;
    }
    return false;
}

static char *checkSame(char *command, char *replace) {
    int slashCount = 0;
    char  *newReplace = NULL;
    int k = 0;

    if (noReturn(command, replace) == true)
        return replace;
    newReplace = (char *)malloc(sizeof(char) * strlen(replace));
    for (; slashCount < 2; k++) {
        newReplace[k] = replace[k];
        if (replace[k] == '/')
            slashCount++;
    }
    newReplace[k] = '\0';
    newReplace = realloc(newReplace, strlen(newReplace) + 1);
    return newReplace;
}

static bool subPar(char *parameter, int j) {
    extern char **environ;

    for (int i = 0; environ[j][i] != 61; i++) {
        if (environ[j][i] != parameter[i])
            return false;
    }
    return true;
}

char *mx_parameterSearch(char *parameter, char *command) {
    char **envParam = NULL;
    extern char **environ;
    char *extend = NULL;

    for (int j = 0; environ[j]; j++) {
        if (subPar(parameter, j) == true) {
            envParam = mx_strsplit(environ[j], '=');
            extend = envParam[1];
            if (iStilda(command) == true)
                extend = checkSame(command, envParam[1]);
            return extend;
        }
    }
    return NULL;
}