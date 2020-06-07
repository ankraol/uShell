#include "header.h"

char *mx_parameter_exp(char *command, t_var *varList) {
    char *newLine = NULL;
    char *replace = NULL;
    t_expIndex index;

    memset(&index, 0, sizeof(t_expIndex));
    if (mx_parExt(command) == false)
        return command;
    else
    {
        newLine = (char *)malloc(sizeof(char) * (strlen(command) * 50));
    while (command[index.start] != '\0') {
        replace = mx_parFill(command, &newLine, &index, varList);
        index.tilda = false;
        index.k = 0;
        if (replace) {
            // newLine = realloc(newLine, strlen(command) + strlen(replace) + 1);
            for (int i = 0; replace[i] != '\0'; i++) {
                newLine[index.j] = replace[i];
                index.j++;
            }
            newLine[index.j] = '\0';
        }
    }
    newLine = realloc(newLine, strlen(newLine) + 1);
    }
    return newLine;
}
