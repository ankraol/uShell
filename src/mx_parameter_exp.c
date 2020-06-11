#include "header.h"

static bool exp(char *command, int start) {
    for (int i = start; command[i] != '\0'; i++) {
        if (command[i] == '$')
            return true;
    }
    return false;
}

static void addEnding(char **newLine, t_expIndex index, char *command) {
    for (int i = index.start; command[i] != '\0'; i++) {
        (*newLine)[index.j] = command[i];
        index.j++;
    }
    (*newLine)[index.j] = '\0';
}

static char *create_newLine(t_expIndex index, char *command, t_var *varList) {
    char *replace = NULL;
    char *newLine = (char *)malloc(sizeof(char) * (strlen(command) * 50));

    while (command[index.start] != '\0') {
        // while (index.start < (int)strlen(command)) {
        if (exp(command, index.start) == false)
            break;
        fprintf(stdout, "command(create newLine prepre) = %s\n", command);
        replace = mx_parFill(command, &newLine, &index, varList);
        index.tilda = false;
        index.k = 0;
        fprintf(stdout, "command(create newLine pre) = %s\n", command);
        if (replace) {
            printf("replace = %s\n", replace);
            for (int i = 0; replace[i] != '\0'; i++) {
                // printf("e\n");
                newLine[index.j] = replace[i];
                index.j++;
            }
            fprintf(stdout, "command(create newLine after1) = %s\n", command);
            // newLine[index.j] = '\0';
            fprintf(stdout, "start with %d\n", index.start);
            fprintf(stdout, "command(create newLine after2) = %s\n", command);
            // mx_strdel(&replace);
        }
        mx_strdel(&replace);
        fprintf(stdout, "command(create newLine after3) = %s\n", command);
    }
    if (command[index.start] != '\0')
        addEnding(&newLine, index, command);
    else
        newLine[index.j] = '\0';
    newLine = realloc(newLine, strlen(newLine) + 1);

    fprintf(stdout, "replace 2 = %s\n", replace);
    return newLine;
}

char *mx_parameter_exp(char *command, t_var *varList) {
    char *newLine = NULL;
    t_expIndex index;

    memset(&index, 0, sizeof(t_expIndex));
    if (mx_parExt(command) == false) {
        newLine = strdup(command);
        mx_strdel(&command);
        return newLine;

    }
    else {
        newLine = create_newLine(index, command, varList);
        mx_strdel(&command);
    }
    fprintf(stdout, "%s\n", newLine);
    return newLine;
}
