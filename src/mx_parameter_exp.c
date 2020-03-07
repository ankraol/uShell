#include "header.h"

static bool iStilda(char *command) {
    for (int i = 0; command[i] != '\0'; i++)
        if (command[i] == 126)
            return true;
    return false;
}

static bool parExt(char *command) {
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == 123 && command[i - 1] == 36)
            return true;
        else if (command[i] == 36)
            return true;
        else if (command[i] == 126)
            return true;
    }
    return false;
}

static char *checkSame(char *command, char *replace) {
    int slashCount = 0;
    char  *newReplace = NULL;
    int i = 2;
    int j = 0;
    int k = 0;

    for(; replace[i - 1] != '/'; i++);
    for(; command[j - 1] != '~'; j++);
    if (command[j] == '\0')
        return replace;
    for (; replace[i] != '\0' && command[j] != '\0'; j++, i++) {
        if (command[j] != replace[i])
            return replace;
    }
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

static char *parameterSearch(char *parameter, char *command) {
    char **envParam = NULL;
    extern char **environ;
    bool subPar = true;
    char *extend = NULL;

    for (int j = 0; environ[j]; j++) {
        subPar = true;
        for (int i = 0; environ[j][i] != 61; i++) {
            if (environ[j][i] != parameter[i])
                subPar = false;
        }
        if (subPar == true) {
            envParam = mx_strsplit(environ[j], '=');
            extend = envParam[1];
            if (iStilda(command) == true)
                extend = checkSame(command, envParam[1]);
            // printf("FOUNDED - %s\n", envParam[1]);
            return extend;
        }
    }
    return NULL;
}

char *mx_parameter_exp(char *command) {
    char *newLine = NULL;
    char *expLine = NULL;
    char *replace = NULL;
    bool exp = false;
    bool dollar = false;
    bool sQ = false;
    bool tilda = false;
    int k = 0;
    int j = 0;
    int start = 0;
    int i = 0;

    if (parExt(command) == false)
        return command;
    else
    {
        newLine = (char *)malloc(sizeof(char) * strlen(command));
    while (command[start] != '\0') {
        expLine = (char *)malloc(sizeof(char) * strlen(command));
        for (i = start; command[i] != '\0'; i++) {
            if ((command[i] == 123 && command[i - 1] == 36) && sQ == false)
                exp = true;
            else if (command[i] == 36 && sQ == false)
                dollar = true;
            else if (command[i] == 126) {
                if (command[i + 1] == '+' || command[i + 1] == '-')
                    i++;
                tilda = true;
                break;
            }
            else if (command[i] == 39 && exp == false) {
                if (sQ == false)
                    sQ = true;
                else
                    sQ = false;
            }
            else if (command[i] == 125 && exp == true) {
                exp = false;
                break;
            }
            else if (command[i] == ' ' && dollar == true) {
                dollar = false;
                i -= 1;
                break;
            }
            else if (exp == true || dollar == true) {
                expLine[k] = command[i];
                k++;
            }
            else if (exp == false && dollar == false) {
                if (command[i] != 36) {
                    newLine[j] = command[i];
                    j++;
                }
            }
        }
        start = i + 1;
        newLine[j] = '\0';
        newLine = realloc(newLine, strlen(newLine) + 1);
        if (tilda == false) {
            expLine[k] = '\0';
            expLine = realloc(expLine, strlen(expLine) + 1);
            replace = parameterSearch(expLine, command);
        }
        else {
            if (command[i] == '+')
                replace = parameterSearch("PWD", command);
            else if (command[i] == '-')
                replace = parameterSearch("OLDPWD", command);
            else
                replace = parameterSearch("HOME", command);
        }
        // printf("expand - %s\nrest command - %s\n", expLine, newLine);
        tilda = false;
        k = 0;
        if (replace) {
            newLine = realloc(newLine, strlen(command) + strlen(replace) + 1);
            for (int i = 0; replace[i] != '\0'; i++) {
                newLine[j] = replace[i];
                j++;
            }
            newLine[j] = '\0';
        }
    }
    newLine = realloc(newLine, strlen(newLine) + 1);
    }
    return newLine;
}