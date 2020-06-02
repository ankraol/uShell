#include "header.h"

static char *varSearch(char *parameter, t_var *varList) {
    t_var *p = varList;
    char *varMeaning = NULL;

    for (; p; p = p->next) {
        if (mx_strcmp(parameter, (unsigned char *)p->name) == 0) {
            varMeaning = mx_strdup(p->meaning);
            return varMeaning;
        }
    }
    return NULL;
}

char *mx_parameter_exp(char *command, t_var *varList) {
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

    if (mx_parExt(command) == false)
        return command;
    else
    {
        newLine = (char *)malloc(sizeof(char) * strlen(command) * 50);
    while (command[start] != '\0') {
        expLine = (char *)malloc(sizeof(char) * strlen(command));
        for (i = start; command[i] != '\0'; i++) {
            if ((command[i] == 123 && command[i - 1] == 36) && sQ == false)
                exp = true;
            else if (command[i] == 36 && command[i + 1] != 40 && sQ == false)
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
                    newLine[j] = command[i];
                    j++;
            }
        }
        printf("CYCLE ENDED\n");
        start = i + 1;
        newLine[j] = '\0';
        newLine = realloc(newLine, strlen(newLine) + 1);
        if (tilda == false) {
            expLine[k] = '\0';
            expLine = realloc(expLine, strlen(expLine) + 1);
            printf("replace - %s\n", expLine);
            replace = mx_parameterSearch(expLine, command);
            if (replace == NULL)
                replace = varSearch(expLine, varList);
        }
        else {
            if (command[i] == '+')
                replace = mx_parameterSearch("PWD", command);
            else if (command[i] == '-')
                replace = mx_parameterSearch("OLDPWD", command);
            else
                replace = mx_parameterSearch("HOME", command);
        }
        printf("expand - %s\nrest command - %s\n", expLine, newLine);
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
    //printf("NEWLINE - %s\n", newLine);
    return newLine;
}
