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
    char *expLine = mx_parCycle(index, command, &(*index).tilda, newLine);

        if ((*index).tilda == false && expLine) {
            replace = mx_parameterSearch(expLine, command);
            if (replace == NULL)
                replace = varSearch(expLine, varList);
        }
        else if ((*index).tilda == true){
            if (command[(*index).start - 1] == '+')
                replace = mx_parameterSearch("PWD", command);
            else if (command[(*index).start - 1] == '-')
                replace = mx_parameterSearch("OLDPWD", command);
            else
                replace = mx_parameterSearch("HOME", command);
        }
        return replace;
}
