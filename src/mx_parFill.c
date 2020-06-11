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

char *mx_parFill(char *command, char **newLine, t_expIndex *index,
                    t_var *varList) {
    char *replace = NULL;
    fprintf(stdout, "COMMAND(pre) = %s\n", command);
    fprintf(stdout, "index of command(start) = %d\n", (*index).start);
    char *expLine = mx_parCycle(index, command, &(*index).tilda, newLine);

    fprintf(stdout, "COMMAND = %s\n", command);
    fprintf(stdout, "index of command(start) = %d\n", (*index).start);
        if ((*index).tilda == false && strlen(expLine) > 1) {
            fprintf(stdout, "EXPLINE = %s\n", expLine);
            replace = mx_parameterSearch(expLine, command);
            if (replace == NULL)
                replace = varSearch(expLine, varList);
            // mx_strdel(&expLine);
        }
        else if ((*index).tilda == true) {
            fprintf(stdout, "EXPLINE = %s\n", expLine);
            fprintf(stdout, "index of command(start) = %d\n", (*index).start);
            if (command[(*index).start - 1] == '+')
                replace = mx_parameterSearch("PWD", command);
            else if (command[(*index).start - 1] == '-')
                replace = mx_parameterSearch("OLDPWD", command);
            else
                replace = mx_parameterSearch("HOME", command);
            // mx_strdel(&expLine);
        }
        mx_strdel(&expLine);
        fprintf(stdout, "index of command(start) = %d\n", (*index).start);
        return replace;
}
